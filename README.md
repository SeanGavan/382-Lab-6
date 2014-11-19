# 382-Lab-6
## Prelab
I plan on using pins 1.4 and 1.5 in order to send my signals. These signals will tell the left and right motors, respectively, whether the voltage should be positive or negative for forward or backward movement of the respective wheel. Timers can be used to determine how much of a turn the robot will make by ending the signal (0 volts) after a certain amount of time. They can also be used to avoid sudden changes and keep the motors from burning out. To setup this control I'll need to use registers R12 and R13 in the PWM subsystem since these are what will be used in the C code. I'll also have to initialize the two pins in C, and also initialize the MSP430 for interaction with the robot. Additional hardware will be wired similarly to the image provided in the lab. I'll use two different interfaces for the wheels because it will avoid sending signals to both motors at once (and causing a short). This also allows for more delay to keep the circuit from shorting as well.
![alt text](https://raw.githubusercontent.com/SeanGavan/382-Lab-6/master/Images/Hardware.png "Prelab Schematic")
