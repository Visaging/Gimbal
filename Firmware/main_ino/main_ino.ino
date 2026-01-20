#include <SimpleFOC.h>
#include <SimpleFOCDrivers.h>
#include <Wire.h>
#include "SparkFun_BMI270_Arduino_Library.h"

// PIN DEFINITIONS
#define I2C_SDA_PIN 8  
#define I2C_SCL_PIN 9  

// Motors
#define PITCH_IN1 40
#define PITCH_IN2 41
#define PITCH_IN3 42

#define ROLL_IN1  38
#define ROLL_IN2  39
#define ROLL_IN3  45 

#define YAW_IN1   18
#define YAW_IN2   19
#define YAW_IN3   20

#define MOTOR_EN  14 

// Buttons
#define MODE_BTN_PIN  1
#define BOOT_BTN_PIN  0

// VARIABLES

BMI270 imu; 

BLDCMotor pitch_motor = BLDCMotor(7);
BLDCDriver3PWM pitch_driver = BLDCDriver3PWM(PITCH_IN1, PITCH_IN2, PITCH_IN3, MOTOR_EN);

BLDCMotor roll_motor = BLDCMotor(7);
BLDCDriver3PWM roll_driver = BLDCDriver3PWM(ROLL_IN1, ROLL_IN2, ROLL_IN3, MOTOR_EN);

BLDCMotor yaw_motor = BLDCMotor(7);
BLDCDriver3PWM yaw_driver = BLDCDriver3PWM(YAW_IN1, YAW_IN2, YAW_IN3, MOTOR_EN);

// Targets
float target_pitch = 0;
float target_roll = 0;
float target_yaw = 0;

// Sensor Data
float sensor_pitch = 0;
float sensor_roll = 0;
float estimated_yaw = 0;

// Logic Variables
unsigned long last_time = 0;
int current_mode = 1; 

// State Flags
unsigned long mode_timer_start = 0;
bool mode3_locked = false; 

bool last_mode_btn_state = HIGH; 
bool last_boot_btn_state = HIGH;

// SETUP

void setup() {
  Serial.begin(115200);
  delay(2000);

  Wire.setPins(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.begin();
  delay(500);

  // --- Drivers ---
  pitch_driver.voltage_power_supply = 12.6;
  pitch_driver.init();
  pitch_motor.linkDriver(&pitch_driver);
  
  roll_driver.voltage_power_supply = 12.6;
  roll_driver.init();
  roll_motor.linkDriver(&roll_driver);
  
  yaw_driver.voltage_power_supply = 12.6;
  yaw_driver.init();
  yaw_motor.linkDriver(&yaw_driver);

  // --- Sensor ---
  if(imu.beginI2C() != BMI2_OK){
    Serial.println("IMU Not Found!");
  }

  // --- Motors ---
  pitch_motor.voltage_limit = 4.0; 
  roll_motor.voltage_limit = 4.0;
  yaw_motor.voltage_limit = 4.0;

  pitch_motor.controller = MotionControlType::angle_openloop;
  roll_motor.controller = MotionControlType::angle_openloop;
  yaw_motor.controller = MotionControlType::angle_openloop;

  pitch_motor.init();
  roll_motor.init();
  yaw_motor.init();

  pinMode(MODE_BTN_PIN, INPUT_PULLUP);
  pinMode(BOOT_BTN_PIN, INPUT_PULLUP);

  Serial.println("Gimbal Ready.");
}


// MAIN LOOP

void loop() {
  // Read Sensor
  imu.getSensorData(); 
  unsigned long now = micros();
  float dt = (now - last_time) * 1e-6; 
  last_time = now;

  // Calculate Angles
  sensor_pitch = atan2(imu.data.accelY, imu.data.accelZ);
  sensor_roll  = -atan2(imu.data.accelX, imu.data.accelZ);

  float gyro_z = imu.data.gyroZ * 0.0174533;
  if (abs(gyro_z) < 0.03) gyro_z = 0;        // Deadband
  estimated_yaw += gyro_z * dt;

  // SMART DRIFT FIX
  if (current_mode == 1 && target_yaw == 0) {
      estimated_yaw *= 0.9995; 
  }

  // Handle Inputs
  handleModeButton(); 
  handleBootButton(); 

  // MODE LOGIC
  if (current_mode == 1) {
    // MODE 1
    pitch_motor.move(target_pitch - sensor_pitch);
    roll_motor.move(target_roll - sensor_roll);
    yaw_motor.move(target_yaw - estimated_yaw);
    
  } 
  else if (current_mode == 2) {
    // MODE 2
    pitch_motor.move(0); roll_motor.move(0); yaw_motor.move(0);

    if (millis() - mode_timer_start > 5000) {
      // Lock targets to current position
      target_pitch = sensor_pitch;
      target_roll = sensor_roll;
      target_yaw = estimated_yaw;
      
      // Restore Power
      pitch_motor.voltage_limit = 4.0;
      roll_motor.voltage_limit = 4.0;
      yaw_motor.voltage_limit = 4.0;
      
      // Go to Mode 1 again
      current_mode = 1; 
      Serial.println("Mode 2 Locked.");
    }
  }
  else if (current_mode == 3) {
    // MODE 3
    
    // Setup Phase
    if (millis() - mode_timer_start < 6000) {
       pitch_motor.move(0); roll_motor.move(0); yaw_motor.move(0);
       mode3_locked = false;
    } 
    // Locked Phase
    else {
       if (!mode3_locked) {
         // Capture targets
         target_pitch = sensor_pitch;
         target_roll = sensor_roll;
         target_yaw = estimated_yaw;
         
         // Restore Power
         pitch_motor.voltage_limit = 4.0;
         roll_motor.voltage_limit = 4.0;
         yaw_motor.voltage_limit = 4.0;
         
         mode3_locked = true;
         Serial.println("Mode 3 Locked.");
       }
       
       // Stabilize
       pitch_motor.move(target_pitch - sensor_pitch);
       roll_motor.move(target_roll - sensor_roll);
       yaw_motor.move(target_yaw - estimated_yaw);
    }
  }

  // FOC Loop
  pitch_motor.loopFOC();
  roll_motor.loopFOC();
  yaw_motor.loopFOC();
}

// FUNCTIONS

void handleModeButton() {
  bool btn = digitalRead(MODE_BTN_PIN);
  if (last_mode_btn_state == HIGH && btn == LOW) {
    delay(50);
    if (digitalRead(MODE_BTN_PIN) == LOW) {

      current_mode = 2;
      mode_timer_start = millis();
      pitch_motor.voltage_limit = 0; 
      roll_motor.voltage_limit = 0;
      yaw_motor.voltage_limit = 0;
      Serial.println("Mode 2: 5s Setup...");
    }
  }
  last_mode_btn_state = btn;
}

void handleBootButton() {
  bool btn = digitalRead(BOOT_BTN_PIN);
  if (last_boot_btn_state == HIGH && btn == LOW) {
    delay(50);
    if (digitalRead(BOOT_BTN_PIN) == LOW) {
      
      if (current_mode != 3) {

        current_mode = 3;
        mode_timer_start = millis();
        mode3_locked = false;
        
        pitch_motor.voltage_limit = 0; 
        roll_motor.voltage_limit = 0;
        yaw_motor.voltage_limit = 0;
        Serial.println("Mode 3: 6s Setup...");
        
      } else {
        // Exit Mode 3 -> Reset to Flat
        current_mode = 1;
        target_pitch = 0;
        target_roll = 0;
        target_yaw = 0;
        estimated_yaw = 0; // Reset Yaw drift
        
        pitch_motor.voltage_limit = 4.0;
        roll_motor.voltage_limit = 4.0;
        yaw_motor.voltage_limit = 4.0;
        Serial.println("Mode 3 Exit: Reset.");
      }
    }
  }
  last_boot_btn_state = btn;
}