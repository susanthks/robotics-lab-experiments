# Experiment 9: Interfacing RPLiDAR with ROS 2 and RViz2

**Topics:** RPLiDAR • ROS 2 • LaserScan • `/scan` Topic • TF Frame • RViz2 • 2D LiDAR Visualization

---

## 1. Aim

To interface an RPLiDAR sensor with ROS 2 and visualize the real-time 2D laser scan data using RViz2.

---

## 2. Objectives

After completing this experiment, students should be able to:

1. Explain the basic working principle of 2D LiDAR.
2. Identify the major components and interfaces of an RPLiDAR.
3. Connect an RPLiDAR to a computer through USB.
4. Install and configure the RPLiDAR ROS 2 driver.
5. Run the RPLiDAR node in ROS 2.
6. Understand the `/scan` topic and `sensor_msgs/msg/LaserScan` message.
7. Configure RViz2 to display LiDAR data.
8. Observe the surrounding environment using a 2D laser scan.
9. Identify common RPLiDAR and ROS 2 connection problems.

---

## 3. Introduction

### 3.1 What is LiDAR?

**LiDAR** stands for **Light Detection and Ranging**.

A LiDAR sensor measures the distance between the sensor and surrounding objects using laser light.

The basic principle is:

```text
Laser Pulse
     |
     v
Object / Obstacle
     |
     v
Reflected Laser
     |
     v
LiDAR Receiver
     |
     v
Distance Measurement
```

A 2D LiDAR rotates its laser beam around the sensor and measures distances at different angles.

The resulting measurements can be represented as:

```text
             0°
              |
              |
       90° ---+--- -90°
              |
              |
             180°
```

The collection of distance measurements forms a **2D laser scan**.

---

## 4. RPLiDAR

RPLiDAR is a family of 2D/3D LiDAR sensors developed by **SLAMTEC**.

Common models include:

- RPLiDAR A1
- RPLiDAR A2
- RPLiDAR A3
- RPLiDAR C1
- RPLiDAR S1
- RPLiDAR S2
- RPLiDAR S3

For this experiment, an **RPLiDAR A1/A2-type serial model** can be used.

> **Note:** Different RPLiDAR models may require different serial baud rates and launch files. Always use the launch file and parameters appropriate for the installed model.

---

## 5. ROS 2 and RPLiDAR

ROS 2 provides the software communication framework between the RPLiDAR and visualization tools.

The basic data flow is:

```text
             RPLiDAR
                |
                | USB / Serial
                v
        +----------------+
        | RPLiDAR Driver |
        +----------------+
                |
                | /scan
                v
        +----------------+
        |     ROS 2      |
        |     Topic      |
        +----------------+
                |
                v
              RViz2
                |
                v
       2D Laser Visualization
```

The RPLiDAR ROS 2 driver publishes scan data on the `/scan` topic using the standard ROS 2 `sensor_msgs/msg/LaserScan` message type.

---

## 6. Requirements

### Hardware

- Computer/Laptop
- Ubuntu Linux
- RPLiDAR sensor
- USB cable / USB-to-serial interface
- Suitable RPLiDAR power supply/interface
- Test objects or obstacles

### Software

- ROS 2 Jazzy
- RViz2
- Git
- `colcon`
- RPLiDAR ROS 2 driver

---

## 7. Prerequisites

Before starting this experiment, make sure ROS 2 Jazzy is installed.

Test ROS 2:

```bash
source /opt/ros/jazzy/setup.bash
ros2 --version
```

Check RViz2:

```bash
rviz2
```

Close RViz2 after confirming that it starts successfully.

---

## 8. RPLiDAR Hardware Connection

Connect the RPLiDAR to the computer using the supplied USB interface.

Typical connection:

```text
RPLiDAR
   |
   | USB
   v
Computer
```

After connecting the device, check the available serial devices:

```bash
ls /dev/ttyUSB*
```

or:

```bash
ls /dev/ttyACM*
```

A typical RPLiDAR connection may appear as:

```text
/dev/ttyUSB0
```

> **Note:** The device name may be different on your computer. Do not assume that it is always `/dev/ttyUSB0`.

---

## 9. Check USB Device

Use:

```bash
lsusb
```

You can also check recent kernel messages:

```bash
dmesg | tail
```

If the RPLiDAR USB interface is detected, a serial device should normally appear.

Check:

```bash
ls -l /dev/ttyUSB0
```

If your system uses another device name, replace `/dev/ttyUSB0` in all commands with the actual device path.

---

## 10. Install Required ROS 2 Packages

Make sure the ROS 2 environment is sourced:

```bash
source /opt/ros/jazzy/setup.bash
```

Install common ROS 2 tools:

```bash
sudo apt update
sudo apt install git python3-colcon-common-extensions ros-jazzy-rviz2
```

---

## 11. Create a ROS 2 Workspace

Create a workspace for the RPLiDAR driver:

```bash
mkdir -p ~/rplidar_ws/src
cd ~/rplidar_ws/src
```

Clone the official SLAMTEC ROS 2 driver:

```bash
git clone https://github.com/Slamtec/sllidar_ros2.git
```

Return to the workspace:

```bash
cd ~/rplidar_ws
```

Source ROS 2:

```bash
source /opt/ros/jazzy/setup.bash
```

Build the package:

```bash
colcon build --symlink-install
```

After a successful build:

```bash
source ~/rplidar_ws/install/setup.bash
```

Verify that the package is available:

```bash
ros2 pkg list | grep sllidar
```

Expected output should include:

```text
sllidar_ros2
```

---

## 12. Set Serial Port Permissions

The RPLiDAR driver needs permission to access the serial device.

First identify the device:

```bash
ls /dev/ttyUSB*
```

For a temporary permission test:

```bash
sudo chmod 777 /dev/ttyUSB0
```

> **Note:** This is suitable for testing but is not the preferred permanent solution. A udev rule is recommended for a permanent setup.

If your device is `/dev/ttyUSB1`, use:

```bash
sudo chmod 777 /dev/ttyUSB1
```

---

## 13. Permanent Environment Setup

To automatically source ROS 2:

```bash
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
```

To automatically source the RPLiDAR workspace:

```bash
echo "source ~/rplidar_ws/install/setup.bash" >> ~/.bashrc
```

Reload the terminal configuration:

```bash
source ~/.bashrc
```

Verify:

```bash
ros2 pkg list | grep sllidar
```

---

## 14. RPLiDAR Launch

For an RPLiDAR A1, the official `sllidar_ros2` package provides:

```bash
ros2 launch sllidar_ros2 view_sllidar_a1_launch.py
```

This launch file starts the RPLiDAR driver and RViz visualization.

For other models, use the corresponding launch file provided by the package.

Examples:

```bash
ros2 launch sllidar_ros2 view_sllidar_a2m7_launch.py
```

```bash
ros2 launch sllidar_ros2 view_sllidar_a3_launch.py
```

```bash
ros2 launch sllidar_ros2 view_sllidar_c1_launch.py
```

```bash
ros2 launch sllidar_ros2 view_sllidar_s1_launch.py
```

> **Important:** Use the launch file corresponding to your actual RPLiDAR model.

---

## 15. Launch RPLiDAR with Custom Serial Port

If the RPLiDAR is connected to `/dev/ttyUSB0`, the A1 launch can be started using:

```bash
ros2 launch sllidar_ros2 sllidar_a1_launch.py \
serial_port:=/dev/ttyUSB0
```

The A1 driver commonly uses:

```text
Serial Port   : /dev/ttyUSB0
Baud Rate     : 115200
Frame ID      : laser
```

If your RPLiDAR model requires different parameters, use the model-specific launch file.

---

## 16. Check ROS 2 Nodes

Open a new terminal.

Source the environments:

```bash
source /opt/ros/jazzy/setup.bash
source ~/rplidar_ws/install/setup.bash
```

Check active nodes:

```bash
ros2 node list
```

You should see a node similar to:

```text
/sllidar_node
```

---

## 17. Check ROS 2 Topics

List the available topics:

```bash
ros2 topic list
```

The important topic for this experiment is:

```text
/scan
```

The `/scan` topic contains the laser scan measurements.

---

## 18. Check the LaserScan Message

Check the topic type:

```bash
ros2 topic type /scan
```

Expected output:

```text
sensor_msgs/msg/LaserScan
```

Display the scan data:

```bash
ros2 topic echo /scan
```

You should see values similar to:

```text
header:
  frame_id: laser
angle_min: ...
angle_max: ...
angle_increment: ...
range_min: ...
range_max: ...
ranges:
- ...
- ...
- ...
```

Press:

```text
Ctrl + C
```

to stop the command.

---

## 19. Important LaserScan Parameters

The `sensor_msgs/msg/LaserScan` message contains important parameters.

| Parameter | Description |
|---|---|
| `header` | Message timestamp and frame |
| `frame_id` | Coordinate frame of the LiDAR |
| `angle_min` | Minimum scanning angle |
| `angle_max` | Maximum scanning angle |
| `angle_increment` | Angular separation between measurements |
| `time_increment` | Time between individual measurements |
| `scan_time` | Time required for one complete scan |
| `range_min` | Minimum valid measurement range |
| `range_max` | Maximum valid measurement range |
| `ranges` | Measured distances |
| `intensities` | Laser return intensity information, when available |

---

## 20. RViz2 Visualization

Open RViz2:

```bash
rviz2
```

### Step 1: Set Fixed Frame

In RViz2:

```text
Global Options
      |
      +-- Fixed Frame
```

Set the Fixed Frame to:

```text
laser
```

If your driver uses another frame, use the frame shown by:

```bash
ros2 topic echo /scan --once
```

and check:

```text
header:
  frame_id: ...
```

---

### Step 2: Add LaserScan Display

In RViz2:

1. Click **Add**.
2. Select **By topic**.
3. Select:

```text
/scan
```

4. Select:

```text
LaserScan
```

Alternatively:

```text
Add → LaserScan
```

Then set:

```text
Topic: /scan
```

---

## 21. RViz2 Configuration

Recommended settings:

```text
Global Options
    Fixed Frame: laser

LaserScan
    Topic: /scan
```

The scan should now appear as a collection of points around the LiDAR.

Example:

```text
                  *
             *         *
          *               *
        *        RPLiDAR     *
          *               *
             *         *
                  *
```

The exact shape depends on the surrounding environment.

---

## 22. Observe the Environment

Place different objects around the RPLiDAR.

For example:

```text
             Wall
     ####################

             * * * *
          *           *
        *      LIDAR     *
          *           *
             * * * *

       Chair          Box
         []             []
```

Observe the changes in RViz2 when:

- An object is moved closer.
- An object is moved farther away.
- A person walks around the sensor.
- A wall is placed in front of the sensor.
- The LiDAR is rotated or repositioned.

---

## 23. ROS 2 Data Flow

The complete experimental workflow is:

```text
+----------------+
|    RPLiDAR     |
+-------+--------+
        |
        | Laser Measurements
        v
+----------------+
| sllidar_node   |
+-------+--------+
        |
        | /scan
        | sensor_msgs/msg/LaserScan
        v
+----------------+
|     ROS 2      |
|     Topic      |
+-------+--------+
        |
        v
+----------------+
|     RViz2      |
+-------+--------+
        |
        v
2D Environment Visualization
```

---

## 24. Algorithm

1. Start the computer.
2. Connect the RPLiDAR to the USB port.
3. Identify the serial device.
4. Source ROS 2 Jazzy.
5. Source the RPLiDAR workspace.
6. Start the RPLiDAR ROS 2 driver.
7. Verify that the `/scan` topic is available.
8. Check the `LaserScan` message type.
9. Start RViz2.
10. Set the correct Fixed Frame.
11. Add a LaserScan display.
12. Select `/scan`.
13. Observe the 2D laser scan.
14. Place different objects around the RPLiDAR.
15. Observe the corresponding changes in RViz2.
16. Record the observations.

---

## 25. Observation Table

Students should record the observed LiDAR behavior.

| Trial | Object | Approx. Distance | Detected in RViz2 | Observation |
|---:|---|---:|---|---|
| 1 | Wall | 1.0 m | Yes | Continuous scan |
| 2 | Box | 0.5 m | Yes | Clear object boundary |
| 3 | Chair | 1.5 m | Yes | Multiple scan points |
| 4 | Person | 2.0 m | Yes | Scan changes with movement |
| 5 | No obstacle | — | — | Open scan area |

> Replace the sample values with actual experimental observations.

---

## 26. Useful ROS 2 Commands

### Source ROS 2

```bash
source /opt/ros/jazzy/setup.bash
```

### Source workspace

```bash
source ~/rplidar_ws/install/setup.bash
```

### Check package

```bash
ros2 pkg list | grep sllidar
```

### List nodes

```bash
ros2 node list
```

### List topics

```bash
ros2 topic list
```

### Check `/scan` type

```bash
ros2 topic type /scan
```

### Check publishing rate

```bash
ros2 topic hz /scan
```

### Display scan data

```bash
ros2 topic echo /scan
```

### Start RViz2

```bash
rviz2
```

---

## 27. Troubleshooting

### Problem 1: `/dev/ttyUSB0` does not exist

Check:

```bash
ls /dev/ttyUSB*
```

and:

```bash
ls /dev/ttyACM*
```

Also check:

```bash
lsusb
```

Try disconnecting and reconnecting the USB cable.

---

### Problem 2: Permission denied

Check:

```bash
ls -l /dev/ttyUSB0
```

For temporary testing:

```bash
sudo chmod 777 /dev/ttyUSB0
```

Then restart the RPLiDAR launch command.

---

### Problem 3: `/scan` topic is not available

Check:

```bash
ros2 node list
```

Then:

```bash
ros2 topic list
```

If `/scan` is missing, check whether the RPLiDAR driver is running.

---

### Problem 4: RViz2 shows "No transform"

Check the frame used by the scan:

```bash
ros2 topic echo /scan --once
```

Look for:

```text
header:
  frame_id: laser
```

Set RViz2:

```text
Global Options → Fixed Frame → laser
```

---

### Problem 5: RViz2 is empty

Check the LaserScan display:

```text
Topic: /scan
```

Also verify that `/scan` is publishing:

```bash
ros2 topic hz /scan
```

---

### Problem 6: Wrong RPLiDAR model

Do not use an A1 launch file for another model without checking the required parameters.

Check the available launch files:

```bash
ros2 pkg prefix sllidar_ros2
```

You can also inspect the package launch directory:

```bash
ls ~/rplidar_ws/src/sllidar_ros2/launch
```

Select the launch file corresponding to the installed RPLiDAR model.

---

### Problem 7: Scan appears distorted or inverted

Check the RPLiDAR driver parameters:

```text
inverted
angle_compensate
scan_mode
```

Use the parameters appropriate for your RPLiDAR model and mounting orientation.

---

## 28. Result

**The RPLiDAR sensor was successfully interfaced with ROS 2 and the real-time 2D laser scan data was visualized in RViz2. The `/scan` topic containing `sensor_msgs/msg/LaserScan` data was examined, and surrounding objects were detected and represented as a 2D laser scan.**

---

## 29. Precautions

1. Handle the RPLiDAR carefully.
2. Use the correct USB interface and power supply.
3. Do not force the USB connector.
4. Verify the correct serial device before launching the driver.
5. Use the correct launch file for the RPLiDAR model.
6. Do not assume that every RPLiDAR model uses the same baud rate.
7. Ensure the RPLiDAR has sufficient power.
8. Keep rotating parts free from obstruction.
9. Do not touch the rotating LiDAR mechanism while it is operating.
10. Keep the LiDAR mounting stable during testing.
11. Use the correct `frame_id` in RViz2.
12. Do not modify ROS 2 system files unnecessarily.
13. Stop the driver before disconnecting the sensor if possible.
14. Use appropriate serial permissions rather than permanently relying on insecure device permissions.
15. Keep the test environment free of unnecessary moving objects during initial testing.

---

## 30. Learning Outcomes

After completing this experiment, students should be able to:

- Explain the basic principle of LiDAR.
- Identify the purpose of an RPLiDAR sensor.
- Connect an RPLiDAR to a computer.
- Configure a ROS 2 LiDAR driver.
- Identify the `/scan` ROS 2 topic.
- Explain the `sensor_msgs/msg/LaserScan` message.
- Configure RViz2 for LiDAR visualization.
- Understand the importance of coordinate frames.
- Interpret a 2D laser scan.
- Troubleshoot basic RPLiDAR and ROS 2 communication problems.

---

## 31. Viva Questions

### Basic Questions

1. What is LiDAR?
2. What is the full form of LiDAR?
3. What is RPLiDAR?
4. What is the purpose of an RPLiDAR in robotics?
5. What is ROS 2?
6. What is RViz2?
7. What is the `/scan` topic?
8. What is the message type of `/scan`?

### Intermediate Questions

9. What is `sensor_msgs/msg/LaserScan`?
10. What is `frame_id`?
11. What is a TF frame?
12. What is the purpose of the Fixed Frame in RViz2?
13. What is `angle_min`?
14. What is `angle_max`?
15. What is `angle_increment`?
16. What is `range_min`?
17. What is `range_max`?
18. How does a 2D LiDAR detect an obstacle?
19. Why does an RPLiDAR rotate?
20. Why is the `/scan` topic important?

### Advanced Questions

21. What is the difference between LiDAR and ultrasonic sensing?
22. What is the difference between LiDAR and camera-based perception?
23. Why is TF important in ROS 2?
24. What happens if the RViz2 Fixed Frame is incorrect?
25. Why can different RPLiDAR models require different baud rates?
26. What is the purpose of `angle_compensate`?
27. What is the purpose of the `inverted` parameter?
28. How can `/scan` data be used for obstacle avoidance?
29. How can LiDAR data be used for SLAM?
30. What additional components are required to perform full mobile robot localization using LiDAR?

---

## 32. Optional Extension: Save and Analyze LaserScan Data

Students can inspect the scan topic:

```bash
ros2 topic echo /scan
```

They can also investigate:

```bash
ros2 topic hz /scan
```

and:

```bash
ros2 topic info /scan
```

This helps students understand ROS 2 topic communication.

---

## 33. Optional Extension: LiDAR-Based Obstacle Detection

The `/scan` data can be used for simple obstacle detection.

Conceptually:

```text
             RPLiDAR
                |
                v
          /scan data
                |
                v
       Distance Processing
                |
                v
       Obstacle Detection
                |
        +-------+-------+
        |               |
    Obstacle         No obstacle
        |               |
        v               v
   Stop/Turn         Continue
```

This experiment can later be extended into:

- Reactive obstacle avoidance
- Robot localization
- SLAM
- Nav2 navigation
- Autonomous mobile robot navigation

---

## 34. Experiment Summary

```text
                    RPLiDAR
                       |
                       | USB
                       v
               +---------------+
               | ROS 2 Driver  |
               | sllidar_node  |
               +-------+-------+
                       |
                       | /scan
                       v
             LaserScan Message
                       |
                       v
                  +---------+
                  |  RViz2  |
                  +----+----+
                       |
                       v
             2D Environment Scan
```

### Core Concept

**RPLiDAR → ROS 2 Driver → `/scan` → LaserScan → RViz2 → Environment Visualization**

---

## 35. References

1. SLAMTEC `sllidar_ros2` package: https://github.com/Slamtec/sllidar_ros2
2. ROS 2 Documentation: https://docs.ros.org/
3. RViz2 documentation: https://docs.ros.org/en/jazzy/p/rviz2/
4. SLAMTEC RPLiDAR: https://www.slamtec.com/en/Lidar

---

**Experiment 9 Complete**
