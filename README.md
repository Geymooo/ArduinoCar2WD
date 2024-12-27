# MBIM 1.0 - Arduino Car Project

This is a simple robot car project called "MBIM 1.0" using Arduino Uno, ultrasonic sensors, and a motor driver. The car can avoid obstacles by moving backward, turning left, or right based on the distance measured by ultrasonic sensors.

## Components

1. **Servo Motor**
2. **2 Ultrasonic Sensors**
3. **Motor Driver (L298N)**
4. **DC Motor (1:48)**
5. **2x 18650 Battery (3.7V)**
6. **DC Step-down Converter**
7. **Arduino Uno**

## Wiring

### Ultrasonic Sensor 1 (Bottom)
- **TRIG_PIN_BAWAH** (Pin 7)
- **ECHO_PIN_BAWAH** (Pin 8)

### Ultrasonic Sensor 2 (Top)
- **TRIG_PIN_ATAS** (Pin A0)
- **ECHO_PIN_ATAS** (Pin A1)

### Motor Driver (L298N)
- **IN1** (Pin 3)
- **IN2** (Pin 4)
- **IN3** (Pin 5)
- **IN4** (Pin 6)

### Servo Motor
- **SERVO_PIN** (Pin 9)

## Code Overview

The robot uses ultrasonic sensors to measure distances in front and below the robot. Based on these measurements, the robot moves accordingly to avoid obstacles:

- **When the bottom ultrasonic sensor detects an object** less than 10 cm away, the robot will move backward for 2 seconds.
- **When the top ultrasonic sensor detects an object** less than 15 cm away, the servo motor rotates to measure the distance to the left and right, and the robot turns in the direction with more space.

### Servo Motor Logic
The servo is positioned at:
- **90 degrees** (default position)
- **45 degrees** (to check the left distance)
- **135 degrees** (to check the right distance)

### Motor Control Logic
- **Move Forward**: When there is no obstacle in front of the robot.
- **Move Backward**: When the bottom ultrasonic sensor detects an obstacle.
- **Turn Left / Turn Right**: Based on the comparison of distances measured by the top ultrasonic sensor.

## Circuit Diagram

The circuit can be made using the above components. You can wire the motors, ultrasonic sensors, and servo as described in the wiring section.

## Libraries

This project uses the following libraries:
- `Servo.h`: For controlling the servo motor.

```cpp
#include <Servo.h>
