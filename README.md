# Over-Engineered Stick (ESP32-S3 Gimbal)
Because apparently holding a phone parallel to the ground requires too much caloric burn for the modern human, I spent some time engineering a robot to do it for me. This is a custom 3-axis gimbal powered by an ESP32-S3, designed to compensate for your lack of wrist stability and general unwillingness to hold a steady shot.

## The "Why Did I Build This" Stack:
- **MCU:** ESP32-S3-WROOM-1-N8R2 _(Because a simple Arduino wasn't overkill enough)_
- **Sensors:** BMI270 6-Axis IMU _(To feel every single one of your hand tremors)_
- **Drivers:** 3x DRV8313 Three-Phase Drivers _(So the phone floats magically while you do nothing)_
- **Motors:** 2805 140KV Gimbal BLDC Motors _(To turn in exactly the opposite direction like she did)_
- **Power:** Custom 3S Li-Ion BMS with CN3303 Charging & TPS563200 Regulation _(Because USB 5V is for the weak)_

## Key Features
- **Active Stabilization:** Uses high-frequency FOC math to micro-manage gravity so you don't have to use "muscles".
- **Native USB-C:** One cable to code it and charge it, because looking for two different cables is just too much work.
- **3 Operation Modes:**
   * Stabilize: Standard horizon leveling and pan following.
   * Teaching Mode: Disables the motors so you can twist the camera to any weird angle by hand. After 5 seconds of holding it there, the gimbal accepts its new reality and locks that position.
   * Selfie/Statue Mode: A dedicated mode that gives you 6 seconds to pose the camera, then freezes it in place indefinitely because apparently holding a selfie angle is considered cardio now.
<hr></hr>
<details>
  <summary><h2>External Wiring Diagrams</h2></summary>
  
### Battery:
![](https://mermaid.ink/img/pako:eNp1UU1PgzAY_ivNe2IZXUpZB_RgIsOPGL3ozXBp1g7IoF0qOHXbf7eAW5aot_f5Prx7WBmpgAPGONcIrYxeVwXvT4RqYzYclULLzIqdzvVgWtdmtyqFbdHj8-i79paqrlEwwfjqMH1Xh3Qk6JlYjkQ4-Sdw66U9wNkfOnb6jZfiQffSp5efkl8jd15KL0rOmyf93kunF3rm-IeAgA-FrSTwtajflA-Nso3oMex7Xw5tqRqVA3enFHaTQ66PLrQV-tWYBnhrOxezpivKE-i2UrQqq0RhRXNutkpLZZem0y1wFgwVwPfwATyIwtmCkGQxp4tgHjLCfPh0NItnYZwklM3jiAYhYUcfvoZVMmNxGNGIEOoCMUsSH5SsWmOfxocOfz1-AyY-iIE?type=png)
<!--
https://mermaid.live/edit#pako:eNp1UU1PgzAY_ivNe2IZXUpZB_RgIsOPGL3ozXBp1g7IoF0qOHXbf7eAW5aot_f5Prx7WBmpgAPGONcIrYxeVwXvT4RqYzYclULLzIqdzvVgWtdmtyqFbdHj8-i79paqrlEwwfjqMH1Xh3Qk6JlYjkQ4-Sdw66U9wNkfOnb6jZfiQffSp5efkl8jd15KL0rOmyf93kunF3rm-IeAgA-FrSTwtajflA-Nso3oMex7Xw5tqRqVA3enFHaTQ66PLrQV-tWYBnhrOxezpivKE-i2UrQqq0RhRXNutkpLZZem0y1wFgwVwPfwATyIwtmCkGQxp4tgHjLCfPh0NItnYZwklM3jiAYhYUcfvoZVMmNxGNGIEOoCMUsSH5SsWmOfxocOfz1-AyY-iIE
-->
<hr></hr>

### Handle wiring:
![](https://mermaid.ink/img/pako:eNqVkj1vgzAQhv_K6WaI-HIAD1WbkqVqlrZT5cXBDqCAHTlGaYr474Wkzhgpm8_3Ps_dcAOWWkik6Ps-UwClVrumovMToNV6T6HmShSGnxRT_6Fdq09lzY2Fr-KaBHh5HuBY84OkILatXzam9KDlW9lSYPihy7008HlqbFkzhNH3n97CxMGru_BGd1JZbs5zfNVbqxWETpI6R_GwI3KO2x7rhx2xc0TO8b6-v8nUd0yMHlamEUh3vD1KDztpOj7XOMw6hraWnWQ4c4KbPUOmxgk6cPWtdYfUmn7CjO6r2hX9QXAri4ZXhnc3s5FKSPOqe2WREnJRIB3wB2mYxotlEOTLJFqGSUyCqXuevkm2iLM8j0iSpVEYB2T08PcyNViQLE6jNAiiCchInnsoRWO12VyP6XJT4x85e7cJ?type=png)
<!--
https://mermaid.live/edit#pako:eNqVkj1vgzAQhv_K6WaI-HIAD1WbkqVqlrZT5cXBDqCAHTlGaYr474Wkzhgpm8_3Ps_dcAOWWkik6Ps-UwClVrumovMToNV6T6HmShSGnxRT_6Fdq09lzY2Fr-KaBHh5HuBY84OkILatXzam9KDlW9lSYPihy7008HlqbFkzhNH3n97CxMGru_BGd1JZbs5zfNVbqxWETpI6R_GwI3KO2x7rhx2xc0TO8b6-v8nUd0yMHlamEUh3vD1KDztpOj7XOMw6hraWnWQ4c4KbPUOmxgk6cPWtdYfUmn7CjO6r2hX9QXAri4ZXhnc3s5FKSPOqe2WREnJRIB3wB2mYxotlEOTLJFqGSUyCqXuevkm2iLM8j0iSpVEYB2T08PcyNViQLE6jNAiiCchInnsoRWO12VyP6XJT4x85e7cJ
-->
<hr></hr>

### BMI270 Breakout Board:
![](https://mermaid.ink/img/pako:eNqNkctuwjAQRX_FmhVICTIxzsOLSoBR1fRBBbSLKhsLmySC2MhNRFvCv9cJatfs5lrnXGs0Z9gaqYCB7_uZRmhr9K7MWTcidDBmz1AhtORWnHSme2h3MKdtIWyNNvzKITQfzJ4fggij2WoxfVy-bdBsOV3xoe_ftfcvvE1jp_LBYv1KguEtEnknbZp00i30mk_bNLyZnj-1Ke1o8CC3pQS2E4dP5UGlbCW6DOeuKIO6UJXKgLlRCrvPINMXJx2F_jCmAlbbxmnWNHnxF5qjFLXipcitqP6brdJS2blpdA1sjKO-A9gZvlyMyCjEOAknQTieEIqpB9_umcYjEidJQCdxFIwJphcPfvpv8YjGJHLr4cAJMU0SD5Qsa2Ofr9fsj3r5BQMWhVA?type=png)
<!--
https://mermaid.live/edit#pako:eNqNkctuwjAQRX_FmhVICTIxzsOLSoBR1fRBBbSLKhsLmySC2MhNRFvCv9cJatfs5lrnXGs0Z9gaqYCB7_uZRmhr9K7MWTcidDBmz1AhtORWnHSme2h3MKdtIWyNNvzKITQfzJ4fggij2WoxfVy-bdBsOV3xoe_ftfcvvE1jp_LBYv1KguEtEnknbZp00i30mk_bNLyZnj-1Ke1o8CC3pQS2E4dP5UGlbCW6DOeuKIO6UJXKgLlRCrvPINMXJx2F_jCmAlbbxmnWNHnxF5qjFLXipcitqP6brdJS2blpdA1sjKO-A9gZvlyMyCjEOAknQTieEIqpB9_umcYjEidJQCdxFIwJphcPfvpv8YjGJHLr4cAJMU0SD5Qsa2Ofr9fsj3r5BQMWhVA
-->
<hr></hr>

### Motors:
![](https://mermaid.ink/img/pako:eNp9kstqwzAQRX9FzKoGO1iSH7EW3dTtohC6STfFGxHJDxJLQZVJW8f_XsVJkxKDF4I7c-7cQTA9bLSQwCAIgkIhtNGqbCp2kgjttN4yVHMlcsMPqlCjqdzpw6bmxqJ1fvYh9IpxEDwe397X-Jg_rLTVBmFvSskspXf05iDX9OeLg3hTSmYpvaM3B72mv1wc1JtSMkvpPwo-VKYRwEq--5Q-tNK0_FRDPy4GW8tWFsCcFNxsCyjU4Ib2XH1o3QKzpnNjRndV_Vd0e8GtzBteGd5ek41UQpon3SkLDNN4zADWw5crE7LIsoyE0TKOQ0LSpQ_frh0lC_dwlCURzghOBx9-xq3hIqYhjtIwjROn0oT4IEXj_rQ638h4KsMv4dSfuQ?type=png)
<!--
https://mermaid.live/edit#pako:eNp9kstqwzAQRX9FzKoGO1iSH7EW3dTtohC6STfFGxHJDxJLQZVJW8f_XsVJkxKDF4I7c-7cQTA9bLSQwCAIgkIhtNGqbCp2kgjttN4yVHMlcsMPqlCjqdzpw6bmxqJ1fvYh9IpxEDwe397X-Jg_rLTVBmFvSskspXf05iDX9OeLg3hTSmYpvaM3B72mv1wc1JtSMkvpPwo-VKYRwEq--5Q-tNK0_FRDPy4GW8tWFsCcFNxsCyjU4Ib2XH1o3QKzpnNjRndV_Vd0e8GtzBteGd5ek41UQpon3SkLDNN4zADWw5crE7LIsoyE0TKOQ0LSpQ_frh0lC_dwlCURzghOBx9-xq3hIqYhjtIwjROn0oT4IEXj_rQ638h4KsMv4dSfuQ
-->

</details>
<hr></hr>
<details>
  <summary><h2>PCB Schematics</h2></summary>
<img width="3507" height="2480" alt="image" src="https://github.com/user-attachments/assets/a1597c18-d900-4c81-82a0-5f736e6f7ad0" />
<img width="2480" height="1748" alt="image" src="https://github.com/user-attachments/assets/38abb279-5b1a-4a33-9dc9-f7baf6ae8d7d" />
</details>
<hr></hr>
<details>
  <summary><h2>PCB Layout and Render</h2></summary>
<img width="390" height="796" alt="image" src="https://github.com/user-attachments/assets/c2b58327-9d58-4509-aeff-ed65026efaee" />
<img width="1723" height="892" alt="image" src="https://github.com/user-attachments/assets/99fe7bb0-3be4-4f23-83fb-32194be451fe" />
</details>
<hr></hr>
<details>
  <summary><h2>Custom Body (3D Model)</h2></summary>

### Handle:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/650f554e-ba6d-45af-9a29-d58d53ea8497" />
<hr></hr>

### Handle Top:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/ee4c926d-a6d6-46b7-b7d4-50014af6e49f" />
<hr></hr>

### Handle Enclosure:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/3eeef3ba-9de5-4065-9652-657d04925625" />
<hr></hr>

### PAN Arm :

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/79b7180d-907e-4f8b-8edd-c03a1c6794eb" />
<hr></hr>

### ROLL Arm:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/5496a1f9-f378-4879-823d-922085583b02" />
<hr></hr>

### PITCH Arm:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/74c19702-0ae5-4985-b9bd-6ccde3e4f926" />
<hr></hr>

### PITCH Arm Cover:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/e2b517d8-71ad-4b1e-b1e2-8fc4af56bd96" />
<hr></hr>

### Tripod Enclosure:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/1118a418-237e-43d8-91b8-98ebd8a89578" />
<hr></hr>

### Tripod Hub:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/4b234cf9-a086-4670-8141-d2928e885b8f" />
<hr></hr>

### Tripod Legs:

<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/0f592f39-0591-43be-84a4-34583b489e46" />
</details>
<hr></hr>

## Financial Damage Report (Bill of Material)
BOM can be found in the  root older as a .csv, and is also viewable here: [Custom Gimble BOM](https://docs.google.com/spreadsheets/d/1aBBvSRlrgi5838ZnFZRnFuO4f2IFtYvHOy1n1r-4Mq0/edit?usp=sharing)

## Future Bugs... I Mean Features (Roadmap)
Things I might add if I ever get bored of it working perfectly

- [ ] Bluetooth App: Control the gimbal with a phone _(because looking at two screens is better than one)._
- [ ] Face Tracking: If I can figure out how to run AI on this chip without it catching fire.

## Liability Waiver (License)
**License:** MIT

Feel free to steal this code, modify it, or sell it. However, if your phone falls out and breaks because you set the PID values wrong, I legally never met you.
