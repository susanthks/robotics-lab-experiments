# Experiment 10: Line Following Robot Using IR Sensors

## 1. Aim

To design and implement an autonomous **line-following robot using IR sensors** and a motor driver, capable of detecting and following a predefined path.

---

## 2. Objectives

After completing this experiment, students will be able to:

1. Understand the working principle of an **IR sensor**.
2. Interface IR sensors with an Arduino.
3. Control DC motors using a motor driver.
4. Implement a simple decision-making algorithm for line following.
5. Understand the relationship between sensor input and robot movement.
6. Develop a basic autonomous mobile robot.

---

## 3. Components Required

| Sl. No. | Component | Quantity |
|---|---|---:|
| 1 | Arduino UNO | 1 |
| 2 | IR Line Sensor Module | 2 |
| 3 | DC Geared Motors | 2 |
| 4 | Motor Driver Module (L298N / TB6612FNG) | 1 |
| 5 | Robot Chassis | 1 |
| 6 | Wheels | 2 |
| 7 | Caster Wheel | 1 |
| 8 | Battery Pack | 1 |
| 9 | Jumper Wires | As required |
| 10 | Black Line / White Surface | 1 |

---

## 4. Theory

### 4.1 Line Following Robot

A line-following robot is an autonomous mobile robot that follows a predefined path, usually a **black line on a white surface** or a **white line on a black surface**.

The robot uses sensors to detect the position of the line.

### Basic Operation

```text
IR Sensor → Arduino → Motor Driver → DC Motors → Robot Movement
```

---

### 4.2 Working Principle of IR Sensor

An IR sensor consists mainly of:

- IR LED
- Photodiode / Phototransistor
- Comparator
- Digital output

The IR LED emits infrared radiation toward the surface. The amount of IR radiation reflected back depends on the surface.

### White Surface

White surfaces reflect more IR radiation.

### Black Surface

Black surfaces absorb more IR radiation and reflect less IR radiation.

Therefore, the sensor can distinguish between the black line and the white background.

> **Note:** The actual digital output logic depends on the IR sensor module. Some modules produce `LOW` for black and `HIGH` for white, while others may behave differently. Always verify the sensor output before running the robot.

---

## 5. Two-Sensor Line Following

For a basic line-following robot, two IR sensors are positioned at the front.

```text
                 FRONT
                   ↑

          ┌─────────────────┐
          │                 │
          │  IR-L     IR-R  │
          │    ↓        ↓   │
          │                 │
          │  Left     Right │
          │  Motor    Motor │
          └─────────────────┘
```

The sensors are:

- **Left IR Sensor (L)**
- **Right IR Sensor (R)**

The Arduino reads the output of both sensors and decides how the motors should rotate.

---

## 6. Sensor Decision Logic

The following table assumes:

- `0` / `LOW` = black line detected
- `1` / `HIGH` = white surface detected

| Left Sensor | Right Sensor | Robot Action |
|---:|---:|---|
| 0 | 0 | Move Forward |
| 0 | 1 | Turn Left |
| 1 | 0 | Turn Right |
| 1 | 1 | Stop / Line Lost |

> **Important:** If your IR module gives the opposite logic, invert the conditions in the program.

---

## 7. Motor Control

A motor driver is required because an Arduino cannot directly supply the current required by most DC motors.

For an L298N-type motor driver:

```text
                         Arduino
                            │
             ┌──────────────┼──────────────┐
             │              │              │
            IN1            IN2            IN3/IN4
             │              │              │
             └──────────────┴──────────────┘
                            │
                     Motor Driver
                       ┌────┴────┐
                       ↓         ↓
                  Left Motor  Right Motor
```

The motor driver controls:

- Motor direction
- Motor ON/OFF
- Motor speed when PWM control is used

---

## 8. Circuit Connections

### 8.1 IR Sensors

| IR Sensor | Arduino |
|---|---|
| Left OUT | D2 |
| Right OUT | D3 |
| VCC | 5V |
| GND | GND |

### 8.2 L298N Motor Driver

| L298N Pin | Arduino |
|---|---|
| IN1 | D8 |
| IN2 | D9 |
| IN3 | D10 |
| IN4 | D11 |
| GND | Arduino GND |

### 8.3 Motors

```text
L298N OUT1 ── Left Motor ── OUT2

L298N OUT3 ── Right Motor ── OUT4
```

### 8.4 Power

```text
Battery
   │
   ├── Motor Driver
   │
   └── Arduino / regulated supply
```

**Important:** Arduino GND and motor-driver GND must have a **common ground**.

> **Power Safety:** Do not power the motors directly from the Arduino 5V pin. Use a suitable external motor supply.

---

## 9. Algorithm

1. Start the robot.
2. Initialize the IR sensor pins.
3. Initialize the motor-driver pins.
4. Read the left and right IR sensors.
5. Compare the sensor values.
6. Control the motors according to the sensor condition:
   - Both sensors detect the line → Move forward.
   - Left sensor detects the line → Turn left.
   - Right sensor detects the line → Turn right.
   - Both sensors lose the line → Stop.
7. Repeat the process continuously.

---

## 10. Arduino Program

The following program assumes:

**LOW = Black line detected**

```cpp
// Experiment 10
// Line Following Robot Using IR Sensors

// IR Sensor Pins
const int LEFT_IR  = 2;
const int RIGHT_IR = 3;

// Motor Driver Pins
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

void setup()
{
  // IR sensor pins
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  // Motor driver pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);

  stopRobot();
}

void loop()
{
  int leftSensor  = digitalRead(LEFT_IR);
  int rightSensor = digitalRead(RIGHT_IR);

  Serial.print("Left: ");
  Serial.print(leftSensor);

  Serial.print("  Right: ");
  Serial.println(rightSensor);

  // Both sensors detect black line
  if (leftSensor == LOW && rightSensor == LOW)
  {
    moveForward();
  }

  // Left sensor detects black line
  else if (leftSensor == LOW && rightSensor == HIGH)
  {
    turnLeft();
  }

  // Right sensor detects black line
  else if (leftSensor == HIGH && rightSensor == LOW)
  {
    turnRight();
  }

  // Both sensors detect white surface
  else
  {
    stopRobot();
  }
}


// ---------------- MOTOR FUNCTIONS ----------------

void moveForward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopRobot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
```

---

## 11. Program Explanation

### Sensor Reading

```cpp
int leftSensor = digitalRead(LEFT_IR);
int rightSensor = digitalRead(RIGHT_IR);
```

These statements read the digital outputs of the two IR sensors.

### Forward Motion

```cpp
if (leftSensor == LOW && rightSensor == LOW)
{
    moveForward();
}
```

When both sensors detect the line according to the assumed sensor logic, both motors are commanded to move forward.

### Left Turn

```cpp
else if (leftSensor == LOW && rightSensor == HIGH)
{
    turnLeft();
}
```

The robot changes its direction toward the left.

### Right Turn

```cpp
else if (leftSensor == HIGH && rightSensor == LOW)
{
    turnRight();
}
```

The robot changes its direction toward the right.

### Stop

```cpp
else
{
    stopRobot();
}
```

When both sensors indicate that the line is not detected, the robot stops.

---

## 12. Flowchart

```text
                 START
                   │
                   ↓
          Initialize Arduino
                   │
                   ↓
           Read IR Sensors
                   │
                   ↓
        ┌─────────────────────┐
        │ Check Sensor Values  │
        └──────────┬──────────┘
                   │
       ┌───────────┼───────────┐
       ↓           ↓           ↓
    Forward       Left        Right
       │           │           │
       └───────────┼───────────┘
                   ↓
             Motor Control
                   │
                   ↓
          Read Sensors Again
                   │
                   └──────→ LOOP
```

---

## 13. Procedure

1. Assemble the robot chassis with two DC motors and wheels.
2. Mount the two IR sensors at the front of the robot.
3. Connect the IR sensors to the Arduino digital pins.
4. Connect the motors to the motor driver.
5. Connect the motor-driver control pins to Arduino.
6. Connect the battery supply.
7. Upload the Arduino program.
8. Open the Serial Monitor and observe the IR sensor values.
9. Place the robot on a black line drawn on a white surface.
10. Observe the robot movement.
11. Adjust the IR sensor positions and sensitivity potentiometers if required.
12. Test the robot on straight and curved paths.

---

## 14. Observation

Record the sensor values and corresponding robot action.

| Left IR | Right IR | Detected Condition | Robot Movement |
|---:|---:|---|---|
| 0 | 0 | Both detect line | Forward |
| 0 | 1 | Line toward left | Left |
| 1 | 0 | Line toward right | Right |
| 1 | 1 | Line not detected | Stop |

---

## 15. Result

**The line-following robot was successfully designed and implemented using IR sensors. The robot was able to detect the line and automatically control the direction of the DC motors to follow the predefined path.**

---

## 16. Precautions

1. Check the polarity of the motor connections before powering the circuit.
2. Ensure that Arduino and motor-driver grounds are common.
3. Do not power the motors directly from the Arduino 5V pin.
4. Keep the IR sensors at an appropriate height from the floor.
5. Adjust the IR sensor potentiometers before testing.
6. Ensure that the line has sufficient contrast with the background.
7. Avoid loose jumper-wire connections.
8. Use a suitable battery for the motors.
9. Check the IR sensor output logic before testing the complete robot.
10. Disconnect the battery before modifying the motor-driver wiring.

---

## 17. Viva Questions

### Basic Questions

1. What is a line-following robot?
2. What is the purpose of an IR sensor?
3. What is the working principle of an IR sensor?
4. Why can an IR sensor distinguish between black and white surfaces?
5. Why can't an Arduino directly drive a DC motor?

### Intermediate Questions

6. What is the function of a motor driver?
7. What is the purpose of the L298N motor driver?
8. Why are two IR sensors used?
9. What happens when the left sensor detects the black line?
10. What happens when the right sensor detects the black line?
11. What is PWM?
12. How can the speed of the robot be controlled?

### Advanced Questions

13. What is the difference between a two-sensor and three-sensor line follower?
14. What happens when the robot encounters a sharp curve?
15. How can PID control improve line following?
16. What is the difference between digital and analog IR sensors?
17. How can the robot detect intersections?
18. How can wheel encoders be incorporated into the line-following robot?
19. How can the robot be made faster?
20. How can this system be extended using ESP32?

---

## 18. Optional Extensions

Students can extend the experiment by implementing:

### Extension 1: Three-Sensor Line Following

Add a center IR sensor:

```text
       LEFT     CENTER     RIGHT
        ↓         ↓          ↓
       [IR]      [IR]       [IR]
```

This allows the robot to make more precise decisions.

### Extension 2: PWM Speed Control

Use PWM to control motor speed instead of only using ON/OFF control.

### Extension 3: PID Line Following

Implement a PID controller to achieve smoother and faster line following.

```text
Sensor Error
     ↓
   PID Controller
     ↓
Motor Speed Correction
     ↓
Left Motor + Right Motor
```

### Extension 4: Intersection Detection

Modify the algorithm to detect:

- T-junctions
- Cross junctions
- Dead ends
- Multiple paths

---

## 19. Suggested Repository Structure

```text
PartB/
└── Experiment10_Line_Following_Robot_IR/
    ├── README.md
    ├── Arduino_Code/
    │   └── line_following_robot.ino
    ├── Circuit_Diagram/
    │   └── circuit.png
    ├── Images/
    │   └── line_following_robot.jpg
    └── Manual/
        └── Experiment_10_Line_Following_Robot.pdf
```

---

## 20. Learning Outcome

After completing this experiment, students should be able to:

- Explain the working principle of IR sensors.
- Interface IR sensors with Arduino.
- Control DC motors using a motor driver.
- Develop a basic autonomous line-following robot.
- Implement sensor-based decision making.
- Identify practical problems in mobile robot navigation.
- Extend a basic line follower toward PID-based autonomous navigation.
