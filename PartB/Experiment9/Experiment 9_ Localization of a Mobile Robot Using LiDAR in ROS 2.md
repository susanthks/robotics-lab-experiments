# Experiment 9: Localization of a Mobile Robot Using LiDAR in ROS 2

## Aim

To perform localization of a mobile robot using **LiDAR sensor data** in ROS 2 Jazzy Jalisco and estimate the position and orientation of the robot in a known environment using the **AMCL (Adaptive Monte Carlo Localization)** algorithm.

---

# Objectives

After completing this experiment, students will be able to:

- Understand the concept of robot localization.
- Understand the role of LiDAR in mobile robot localization.
- Create a map of an environment using SLAM.
- Save and load an occupancy grid map.
- Visualize LiDAR data using RViz2.
- Use AMCL for robot localization.
- Estimate the position and orientation of a mobile robot.
- Understand the relationship between the `map`, `odom`, `base_link`, and LiDAR coordinate frames.

---

# Theory

## What is Robot Localization?

Localization is the process of determining the position and orientation of a robot within its environment.

In simple terms, localization answers the question:

> **Where is the robot?**

The pose of a mobile robot in a two-dimensional environment can be represented as:

```text
(x, y, θ)
```

Where:

- `x` represents the position along the X-axis.
- `y` represents the position along the Y-axis.
- `θ` represents the orientation of the robot.

---

# Role of LiDAR

LiDAR stands for **Light Detection and Ranging**.

A LiDAR sensor measures the distance between the robot and surrounding objects.

In ROS 2, LiDAR data is commonly published through the following topic:

```text
/scan
```

The message type is generally:

```text
sensor_msgs/msg/LaserScan
```

The robot uses LiDAR measurements to detect walls and obstacles around it.

```text
              Wall
   ─────────────────────────

          ●  ●  ●
       ●           ●
     ●     ROBOT     ●
       ●           ●
          ●  ●  ●
```

The measured distances can be compared with a previously created map to estimate the position of the robot.

---

# AMCL

**AMCL** stands for **Adaptive Monte Carlo Localization**.

AMCL is a probabilistic localization algorithm based on a particle filter.

It uses:

- A known map
- LiDAR sensor data
- Robot odometry

to estimate the position and orientation of the robot.

```text
                    Known Map
                        │
                        ▼
LiDAR Data ───────► AMCL ◄─────── Odometry
   (/scan)              │             (/odom)
                        │
                        ▼
              Estimated Robot Pose
                  (/amcl_pose)
```

AMCL in Nav2 is designed for 2D localization using a known map and laser scan data.

---

# ROS 2 Localization Workflow

The complete workflow used in this experiment is:

```text
                 ┌──────────────────┐
                 │   Mobile Robot   │
                 └────────┬─────────┘
                          │
                 LiDAR + Odometry
                          │
                          ▼
                    SLAM Toolbox
                          │
                          ▼
                    Create Map
                          │
                          ▼
                     Save Map
                          │
                          ▼
                  Known Environment
                          │
                          ▼
                       AMCL
                          │
              ┌───────────┴───────────┐
              ▼                       ▼
        Robot Pose                  RViz2
       (/amcl_pose)
```

---

# Important ROS 2 Topics

| Topic | Description |
|---|---|
| `/scan` | LiDAR sensor data |
| `/map` | Occupancy grid map |
| `/odom` | Robot odometry |
| `/tf` | Coordinate transformations |
| `/tf_static` | Static coordinate transformations |
| `/amcl_pose` | Estimated robot pose |
| `/cmd_vel` | Robot velocity commands |

---

# Coordinate Frames

A typical mobile robot localization system contains the following coordinate frames:

```text
map
 │
 ▼
odom
 │
 ▼
base_link
 │
 ▼
base_scan
```

Where:

- `map` represents the global environment.
- `odom` represents the robot odometry frame.
- `base_link` represents the robot body.
- `base_scan` represents the LiDAR sensor.

The exact LiDAR frame name may vary depending on the robot model.

---

# Requirements

- Ubuntu 24.04 LTS
- ROS 2 Jazzy Jalisco
- Gazebo
- RViz2
- TurtleBot3 simulation
- Navigation2 (Nav2)
- SLAM Toolbox
- Teleoperation package

---

# Part A – Install Required Packages

## Step 1: Update the System

Open a terminal and execute:

```bash
sudo apt update
sudo apt upgrade
```

---

## Step 2: Source ROS 2 Jazzy

```bash
source /opt/ros/jazzy/setup.bash
```

To automatically source ROS 2 when opening a new terminal:

```bash
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

---

## Step 3: Verify ROS 2 Installation

```bash
ros2 --version
```

Check the available ROS distribution:

```bash
echo $ROS_DISTRO
```

Expected output:

```text
jazzy
```

---

## Step 4: Install Navigation and Localization Packages

Install Nav2:

```bash
sudo apt install ros-jazzy-navigation2 ros-jazzy-nav2-bringup
```

Install AMCL:

```bash
sudo apt install ros-jazzy-nav2-amcl
```

Install SLAM Toolbox:

```bash
sudo apt install ros-jazzy-slam-toolbox
```

Install keyboard teleoperation:

```bash
sudo apt install ros-jazzy-teleop-twist-keyboard
```

SLAM Toolbox is the supported ROS 2 SLAM package used in the Nav2 workflow, and Nav2 documentation describes using it to generate occupancy-grid maps that can later be saved.

---

# Part B – Install TurtleBot3

## Step 5: Install TurtleBot3 Packages

For a Jazzy-based setup, first install the available TurtleBot3 dependencies and packages appropriate to your installation.

```bash
sudo apt update

sudo apt install ros-jazzy-turtlebot3 \
                 ros-jazzy-turtlebot3-msgs \
                 ros-jazzy-turtlebot3-bringup
```

If these packages are unavailable in your configured repository, TurtleBot3 can be built from its Jazzy branch in a workspace. The ROBOTIS TurtleBot3 documentation confirms testing with Ubuntu 24.04 and ROS 2 Jazzy.

---

## Step 6: Set the TurtleBot3 Model

For this experiment, use the TurtleBot3 Burger model.

```bash
echo 'export TURTLEBOT3_MODEL=burger' >> ~/.bashrc
source ~/.bashrc
```

Verify:

```bash
echo $TURTLEBOT3_MODEL
```

Expected output:

```text
burger
```

---

# Part C – Launch the Robot Simulation

## Step 7: Launch TurtleBot3 Simulation

Open a terminal:

```bash
source /opt/ros/jazzy/setup.bash
```

Launch the robot simulation:

```bash
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
```

Gazebo should open with the TurtleBot3 robot.

---

## Step 8: Check Available ROS Topics

Open another terminal:

```bash
source /opt/ros/jazzy/setup.bash
```

Run:

```bash
ros2 topic list
```

You should observe topics similar to:

```text
/cmd_vel
/odom
/scan
/tf
/tf_static
```

---

# Part D – Visualize LiDAR Data

## Step 9: Start RViz2

Open another terminal:

```bash
source /opt/ros/jazzy/setup.bash
rviz2
```

---

## Step 10: Add LiDAR Visualization

In RViz2:

1. Click **Add**.
2. Select **By Topic**.
3. Select the `/scan` topic.
4. Add **LaserScan**.

The LiDAR scan points should appear around the robot.

---

## Step 11: Check LiDAR Data

Run:

```bash
ros2 topic echo /scan
```

You should see LaserScan data.

Example:

```text
header:
  frame_id: base_scan

angle_min: ...
angle_max: ...

ranges:
- 1.25
- 1.30
- 1.28
```

Check topic information:

```bash
ros2 topic info /scan
```

---

# Part E – Create a Map Using SLAM

Localization requires a previously created map.

In this section, the robot will first create a map using LiDAR.

---

## Step 12: Launch SLAM Toolbox

Open a new terminal:

```bash
source /opt/ros/jazzy/setup.bash
```

Run:

```bash
ros2 launch slam_toolbox online_async_launch.py use_sim_time:=true
```

SLAM Toolbox processes `/scan` data and publishes an occupancy grid map. It also uses the robot's transform information to construct the map.

---

## Step 13: Visualize the Map

In RViz2:

1. Set the **Fixed Frame** to:

```text
map
```

2. Click **Add**.
3. Select **By Topic**.
4. Add the `/map` topic.

The occupancy grid map should appear.

---

# Part F – Move the Robot and Create the Map

## Step 14: Start Keyboard Teleoperation

Open a new terminal:

```bash
source /opt/ros/jazzy/setup.bash
```

Run:

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```

Use the keyboard to move the robot.

Common controls:

```text
        u    i    o
        j    k    l
        m    ,    .
```

Move the robot around the environment slowly so that the LiDAR sensor can scan walls and obstacles.

The map will gradually be generated.

---

## Step 15: Verify the Map

Check whether the `/map` topic is active:

```bash
ros2 topic list | grep map
```

You can also inspect the map:

```bash
ros2 topic echo /map --once
```

---

# Part G – Save the Map

## Step 16: Create a Maps Directory

```bash
mkdir -p ~/ros2_ws/maps
```

---

## Step 17: Save the Generated Map

Run:

```bash
ros2 run nav2_map_server map_saver_cli -f ~/ros2_ws/maps/lab_map
```

This command saves the map as:

```text
lab_map.pgm
lab_map.yaml
```

The Nav2 map saver creates an occupancy-grid map that can be used later for localization.

Check the files:

```bash
ls ~/ros2_ws/maps
```

Expected output:

```text
lab_map.pgm
lab_map.yaml
```

---

# Part H – Stop the Mapping System

After saving the map, stop:

- SLAM Toolbox
- Teleoperation

Press:

```text
Ctrl + C
```

The Gazebo simulation may remain running.

For a clean localization test, stop all ROS processes and restart the simulation.

---

# Part I – Localization Using AMCL

## Step 18: Restart TurtleBot3 Simulation

Open a new terminal:

```bash
source /opt/ros/jazzy/setup.bash
```

Run:

```bash
ros2 launch turtlebot3_gazebo turtlebot3_world.launch.py
```

---

## Step 19: Launch Nav2 Localization

Open another terminal:

```bash
source /opt/ros/jazzy/setup.bash
```

Run:

```bash
ros2 launch nav2_bringup localization_launch.py \
use_sim_time:=true \
map:=$HOME/ros2_ws/maps/lab_map.yaml
```

This starts the map server and AMCL localization system.

---

## Step 20: Start RViz2

Open another terminal:

```bash
source /opt/ros/jazzy/setup.bash
rviz2
```

Set:

```text
Fixed Frame = map
```

Add the following displays:

- Map
- RobotModel
- LaserScan
- TF
- PoseWithCovarianceStamped

Use:

```text
/map
/scan
/amcl_pose
```

as appropriate.

---

# Part J – Set the Initial Robot Position

## Step 21: Provide Initial Pose

In RViz2:

1. Click **2D Pose Estimate**.
2. Click on the approximate robot location on the map.
3. Drag the arrow in the direction that the robot is facing.

The initial pose is published to:

```text
/initialpose
```

AMCL will use this information to begin localization.

---

# Part K – Test Localization

## Step 22: Move the Robot

Open another terminal:

```bash
source /opt/ros/jazzy/setup.bash
```

Run:

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```

Move the robot around the environment.

Observe RViz2.

The estimated robot pose should update continuously.

---

## Step 23: View the Estimated Pose

Run:

```bash
ros2 topic echo /amcl_pose
```

Example output:

```text
pose:
  pose:
    position:
      x: 1.25
      y: 0.80
      z: 0.0

orientation:
  z: 0.32
  w: 0.94
```

The values of `x`, `y`, and orientation represent the estimated pose of the robot.

---

# Part L – Verify Coordinate Frames

## Step 24: Generate the TF Tree

Run:

```bash
ros2 run tf2_tools view_frames
```

A file named:

```text
frames.pdf
```

will be generated.

The coordinate frame relationship should be similar to:

```text
map
 │
 ▼
odom
 │
 ▼
base_link
 │
 ▼
base_scan
```

The `map → odom → base_link` transform chain is important for localization and navigation.

---

# Part M – Monitor Important Topics

## Check LiDAR Data

```bash
ros2 topic echo /scan
```

---

## Check Robot Odometry

```bash
ros2 topic echo /odom
```

---

## Check Map

```bash
ros2 topic echo /map --once
```

---

## Check AMCL Pose

```bash
ros2 topic echo /amcl_pose
```

---

# Useful ROS 2 Commands

| Command | Description |
|---|---|
| `ros2 topic list` | List available topics |
| `ros2 node list` | List running nodes |
| `ros2 service list` | List available services |
| `ros2 topic echo /scan` | Display LiDAR data |
| `ros2 topic echo /odom` | Display odometry data |
| `ros2 topic echo /amcl_pose` | Display estimated pose |
| `ros2 run tf2_tools view_frames` | Generate TF tree |
| `ros2 run teleop_twist_keyboard teleop_twist_keyboard` | Control robot using keyboard |
| `ros2 run nav2_map_server map_saver_cli -f <filename>` | Save occupancy grid map |

---

# Expected Output

After completing the experiment, students should observe:

1. TurtleBot3 successfully launched in the simulation environment.
2. LiDAR data available on the `/scan` topic.
3. LiDAR scans visualized in RViz2.
4. A map generated using SLAM Toolbox.
5. The map saved as `.pgm` and `.yaml` files.
6. The saved map loaded successfully.
7. AMCL localization started.
8. The initial pose set using RViz2.
9. The estimated robot pose updated while the robot moved.
10. The `/amcl_pose` topic published localization information.

---

# Troubleshooting

## ROS 2 Command Not Found

Check:

```bash
source /opt/ros/jazzy/setup.bash
```

---

## TurtleBot3 Model Not Set

Run:

```bash
export TURTLEBOT3_MODEL=burger
```

To make this permanent:

```bash
echo 'export TURTLEBOT3_MODEL=burger' >> ~/.bashrc
source ~/.bashrc
```

---

## No LiDAR Data

Check:

```bash
ros2 topic list
```

Verify that:

```text
/scan
```

is available.

Then check:

```bash
ros2 topic echo /scan
```

---

## AMCL Pose Not Available

Check:

```bash
ros2 node list
```

Verify that the AMCL node is running.

Also check:

```bash
ros2 topic list | grep amcl
```

Expected:

```text
/amcl_pose
```

---

## Map Not Loading

Check whether the map files exist:

```bash
ls ~/ros2_ws/maps
```

Verify that:

```text
lab_map.yaml
lab_map.pgm
```

are present.

Check the YAML file:

```bash
cat ~/ros2_ws/maps/lab_map.yaml
```

Ensure that the image path points to the correct `.pgm` file.

---

# Applications

LiDAR-based localization is widely used in:

- Autonomous Mobile Robots
- Warehouse Robots
- Industrial Robots
- Delivery Robots
- Service Robots
- Autonomous Vehicles
- Agricultural Robots
- Hospital Robots
- Search and Rescue Robots

---

# Result

The mobile robot was successfully localized in a known environment using LiDAR sensor data and the AMCL algorithm. A map of the environment was created using SLAM Toolbox, saved as an occupancy grid map, and later loaded for localization. The robot's estimated position and orientation were visualized in RViz2 and published through the `/amcl_pose` topic.

---

# Conclusion

This experiment demonstrated the complete workflow of LiDAR-based mobile robot localization in ROS 2 Jazzy. The robot first generated a map of its environment using SLAM Toolbox. The generated map was saved and later used as a known map for localization. AMCL combined LiDAR sensor measurements with odometry information to estimate the position and orientation of the robot. This process forms an important foundation for autonomous mobile robot navigation.

---

# Viva Questions

1. What is robot localization?
2. What is the difference between localization and mapping?
3. What does LiDAR stand for?
4. Which ROS 2 topic commonly publishes LiDAR data?
5. What is AMCL?
6. Why is a known map required for AMCL localization?
7. What is the purpose of the `/odom` topic?
8. What information is published on `/amcl_pose`?
9. What is the purpose of the `map` coordinate frame?
10. What is the relationship between `map`, `odom`, and `base_link`?
11. What is an occupancy grid map?
12. Why is an initial pose required in AMCL?
13. What is the role of RViz2 in robot localization?
14. How does LiDAR help a robot determine its position?
15. What is the difference between SLAM and AMCL?

---

# References

- ROS 2 Jazzy Documentation
- Nav2 Documentation
- Nav2 AMCL Documentation
- SLAM Toolbox Documentation
- TurtleBot3 Documentation