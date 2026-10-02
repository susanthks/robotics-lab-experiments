# Experiment 11: Obstacle Avoidance of a Mobile Robot While Moving to a Point

## 1. Aim

To design and implement an Arduino Uno based mobile robot that moves toward a target point while detecting and avoiding obstacles.

## 2. Hardware Required

| Sl. No. | Component | Quantity |
|---|---|---:|
| 1 | Arduino Uno | 1 |
| 2 | 2WD Robot Chassis | 1 |
| 3 | DC Geared Motors | 2 |
| 4 | L298N Motor Driver | 1 |
| 5 | HC-SR04 Ultrasonic Sensor | 1 |
| 6 | Battery | 1 |
| 7 | Jumper Wires | As required |

## 3. Theory

Obstacle avoidance is the ability of a mobile robot to detect obstacles and change its motion to avoid collision.

In this experiment, the **Arduino Uno** reads the distance from an HC-SR04 ultrasonic sensor and controls two DC motors through the L298N motor driver.

### Basic Logic

```text
             Target
               ●
               ↑
               │
          ┌────┴────┐
          │  Robot  │
          └─────────┘
               ↑
            Obstacle
```

- If the path is clear → move forward.
- If an obstacle is detected → stop and turn.
- After avoiding the obstacle → continue moving.

For an ultrasonic sensor:

\[
d = rac{v 	imes t}{2}
\]

For practical Arduino calculations:

\[
d(cm) pprox rac{t(\mu s)}{58}
\]

## 4. Block Diagram

```text
       HC-SR04
           │
           ▼
    ┌─────────────┐
    │ Arduino Uno │
    └──────┬──────┘
           │
           ▼
    ┌─────────────┐
    │    L298N    │
    │Motor Driver │
    └──────┬──────┘
           │
       ┌───┴───┐
       ▼       ▼
   Left Motor  Right Motor
```

## 5. Algorithm

1. Initialize the ultrasonic sensor and motor pins.
2. Read the distance to the obstacle.
3. If the distance is greater than the threshold, move forward.
4. If an obstacle is detected, stop and turn.
5. Continue moving after avoiding the obstacle.
6. Stop when the target point is reached.

## 6. Arduino Program

```cpp
obstacle_avoidance.ino
// Obstacle Avoidance Robot
// Controller: Arduino Uno
```

> **Note:** If the robot moves in the wrong direction, interchange the motor wires or reverse the corresponding `HIGH/LOW` motor commands.

## 7. Procedure

1. Assemble the 2WD robot and connect the motors to the L298N driver.
2. Connect the L298N control pins and HC-SR04 sensor to the Arduino Uno.
3. Upload the program and open the Serial Monitor.
4. Place the robot at the starting point and place an obstacle in its path.
5. Observe the robot moving forward and turning when the obstacle is detected.
6. Verify that the robot continues moving after avoiding the obstacle.

## 8. Observation

| Trial | Obstacle Distance (cm) | Robot Action |
|---:|---:|---|
| 1 | | Forward / Turn |
| 2 | | Forward / Turn |
| 3 | | Forward / Turn |

## 9. Result

The Arduino Uno based mobile robot successfully detected obstacles using the ultrasonic sensor and avoided them while moving toward the target point.

## 10. Precautions

- Check motor-driver wiring before powering the robot.
- Do not connect motors directly to the Arduino Uno.
- Maintain a suitable obstacle-detection threshold.
- Keep the robot speed low during testing.
- Ensure a common ground between Arduino and motor driver.

## 11. Viva Questions

1. What is obstacle avoidance?
2. Why is a motor driver required?
3. How does the HC-SR04 measure distance?
4. Why is the measured time divided by two?
5. What is a differential-drive robot?
6. What happens when the measured distance is below the threshold?
7. What is reactive navigation?
8. How can this robot be improved using multiple sensors?
