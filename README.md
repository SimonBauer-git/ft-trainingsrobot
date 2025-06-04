# ft-trainingsrobot
code for my recreation of the 1985 fischertechnik trainingsrobot
![alt text](https://raw.githubusercontent.com/SimonBauer-git/ft-trainingsrobot/refs/heads/main/images/PXL_20250417_173815408.jpg
)

![alt text](https://raw.githubusercontent.com/SimonBauer-git/ft-trainingsrobot/refs/heads/main/images/PXL_20250417_173737212.jpg)
this is version 1, using ldr encoders.
Version 2 uses potentiometers for position feedback, along with dual rotation axis motors, allowing much greater speeds, with less wiring involved and simpler code.
![alt text](https://raw.githubusercontent.com/SimonBauer-git/ft-trainingsrobot/refs/heads/main/images/PXL_20250511_191727388.jpg)

![alt text](https://github.com/SimonBauer-git/ft-trainingsrobot/blob/main/images/PXL_20250511_191804605.jpg)

the code is kind of modular, the basisprogramm controls the position controls, while the other programm actually contains the instructions on where to move the robot to.
you can also manually control the robot, by sending "s" or "k" through the serial port (115200 8N1), to go back into automatic operation, either reset the arduino, or send "p".
there is no pid or similar control loop, it just runs the motors at full speed until the desired encodervalue is reached, then stops them. If the position you want the robot to
move to and the last position is identical that motor wont move.
