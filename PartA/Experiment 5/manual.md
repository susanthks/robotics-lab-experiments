# Experiment5: Mobile Robot Assembly

## Aim

To assemble a two-wheel differential drive mobile robot using an Arduino Uno, DC geared motors, L298N motor driver, battery pack, and robot chassis, and to verify its basic movements.

---

## Apparatus Required

| Sl. No | Component          | Quantity    |
| ------ | ------------------ | ----------- |
| 1      | Arduino Uno        | 1           |
| 2      | Robot Chassis      | 1           |
| 3      | DC Geared Motor    | 2           |
| 4      | Robot Wheels       | 2           |
| 5      | Caster Wheel       | 1           |
| 6      | L298N Motor Driver | 1           |
| 7      | 12V Battery Pack   | 1           |
| 8      | Battery Holder     | Optional    |
| 9      | Jumper Wires       | As Required |
| 10     | USB Cable          | 1           |
| 11     | Screwdriver Set    | 1           |
| 12     | Nuts and Bolts     | As Required |


---

## Theory

A **mobile robot** is an autonomous or manually controlled robotic system capable of moving from one location to another. Unlike fixed industrial robots, mobile robots are designed for navigation and transportation tasks.

This experiment uses a **two-wheel differential drive robot**, where two independently controlled DC geared motors provide locomotion, while a caster wheel provides balance.

The robot consists of:

- Robot chassis
- Two DC geared motors
- Two wheels
- One caster wheel
- Arduino Uno
- L298N motor driver
- Battery pack

The Arduino generates control signals for the motor driver. The L298N supplies sufficient current to drive the motors while allowing the Arduino to control their direction and speed using PWM.

By varying the rotation of the left and right motors independently, the robot can perform various movements such as:

- Forward
- Backward
- Left Turn
- Right Turn
- Stop


---


## Components

| Component | Description |
|-----------|-------------|
| Arduino Uno | Main controller |
| L298N Motor Driver | Controls both DC motors |
| DC Geared Motors | Provide robot movement |
| Wheels | Robot locomotion |
| Caster Wheel | Supports the front of the robot |
| Battery Pack | Power source |
| Chassis | Base structure |

---

### Figure 1
<img width="1920" height="1644" alt="image" src="https://github.com/user-attachments/assets/cd15e150-af10-43a6-9409-34f5e2459bd2" />


---

## Robot Assembly

### Step 1

Fix both DC motors onto the chassis using the motor brackets.

---

### Step 2

Attach the two wheels to the motor shafts.

---

### Step 3

Fix the caster wheel at the front of the chassis.

---

### Step 4

Mount the Arduino Uno using spacers.

---

### Step 5

Mount the L298N Motor Driver on the chassis.

---

### Step 6

Fix the battery Pack securely.

---

### Step 7

Complete all wiring connections.

---

## Circuit Connections

---

### figure 2

<img width="1535" height="1833" alt="image" src="https://github.com/user-attachments/assets/94c7a9be-8f2d-4eac-b6e5-60460d147bc2" />


---

### Arduino ↔ L298N

| Arduino | L298N |
|----------|--------|
| D5 | ENA |
| D8 | IN1 |
| D9 | IN2 |
| D10 | IN3 |
| D11 | IN4 |
| D6 | ENB |
| GND | GND |

---

### Motor Connections

| L298N | Motor |
|--------|-------|
| OUT1 | Left Motor |
| OUT2 | Left Motor |
| OUT3 | Right Motor |
| OUT4 | Right Motor |

---

### Power Connections

Battery (+) → 12V (VIN)

Battery (-) → GND

Arduino GND → L298N GND

---

## Working Principle

The Arduino sends HIGH/LOW digital signals to the L298N motor driver.

The L298N changes the polarity supplied to the DC motors according to these signals.

Different combinations of motor rotations produce different robot movements.

| Left Motor | Right Motor | Movement   |
| ---------- | ----------- | ---------- |
| Forward    | Forward     | Forward    |
| Reverse    | Reverse     | Backward   |
| Reverse    | Forward     | Left Turn  |
| Forward    | Reverse     | Right Turn |
| Stop       | Stop        | Stop       |


---

### Figure 3

<img width="960" height="720" alt="image" src="https://github.com/user-attachments/assets/48f882c3-b864-4397-bcb0-5362c2417bb5" />



---

## Arduino Program

```cpp
// L298N Motor Driver Connections
#define ENA 5
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENB 6

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void loop() {

  // Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(3000);

  // Stop
  stopRobot();
  delay(1000);

  // Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(3000);

  stopRobot();
  delay(1000);

  // Left Turn
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(2000);

  stopRobot();
  delay(1000);

  // Right Turn
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);

  stopRobot();
  delay(1000);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

```

---

## Procedure

1. Assemble the robot chassis.
2. Mount both DC motors.
3. Attach the wheels.
4. Fix the caster wheel.
5. Install the Arduino Uno.
6. Mount the L298N motor driver.
7. Connect both motors to the motor driver.
8. Connect the Arduino to the motor driver.
9. Connect the battery pack.
10. Verify all wiring connections.
11. Upload the motor testing program.
12. Observe the robot movement.

---

## Observation

| Test       | Expected Result      | Observed |
| ---------- | -------------------- | -------- |
| Forward    | Robot moves forward  | ✔        |
| Backward   | Robot moves backward | ✔        |
| Left Turn  | Robot turns left     | ✔        |
| Right Turn | Robot turns right    | ✔        |
| Stop       | Robot stops          | ✔        |


---

## Result

The mobile robot was successfully assembled and tested. The robot performed forward, backward, left, right, and stop movements correctly, demonstrating successful integration of the mechanical, electrical, and programming components.

---

## Conclusion

In this experiment, a two-wheel differential drive mobile robot was successfully assembled using an Arduino Uno, L298N motor driver, DC geared motors, and a robot chassis. The experiment provided hands-on experience in mechanical assembly, electrical interfacing, motor control, and basic robot programming. The completed robot forms the basis for implementing advanced robotic applications such as line following, obstacle avoidance, wireless control, and autonomous navigation.

---

## Precautions

- Switch OFF power before wiring.
- Check battery polarity.
- Tighten all screws properly.
- Ensure all GND connections are common.
- Keep wires away from the wheels.

---

## Viva Questions

1. What is a mobile robot?
2. What is a differential drive robot?
3. Why is an L298N motor driver used?
4. What is the function of the caster wheel?
5. Why is Arduino used in the robot?
6. What happens if the motor terminals are interchanged?
7. Why should all grounds be connected together?
8. What is the purpose of the chassis?
9. What are the applications of mobile robots?
10. Name two sensors that can be added to this robot.

---


