# Experiment 14  
## TurtleBot3 Simulation using ROS 2 Jazzy and Gazebo Harmonic

### Aim

To set up and simulate a **TurtleBot3 Waffle Pi** robot using **ROS 2 Jazzy**, **Gazebo Harmonic**, and **RViz2**, and to perform basic robot teleoperation and ROS 2 system inspection.

### Requirements

#### Software

- Ubuntu 24.04 LTS
- ROS 2 Jazzy Jalisco
- Gazebo Harmonic
- RViz2
- Git
- Python 3
- TurtleBot3 packages

### Learning Outcomes

After completing this experiment, students will be able to:

- Create and build a TurtleBot3 ROS 2 workspace.
- Launch TurtleBot3 simulation in Gazebo.
- Visualize robot data using RViz2.
- Inspect ROS 2 nodes and topics.
- Generate and inspect the TF tree.
- Teleoperate the TurtleBot3 using the keyboard.
- Monitor velocity commands and simulation time.

---

## 1. Verify ROS 2 Installation

Open a terminal and check the installed ROS 2 distribution:

```bash
echo $ROS_DISTRO
```

Expected output:

```text
jazzy
```

---

## 2. Install Required Packages

Update the package list:

```bash
sudo apt update
```

Install the required development tools and ROS 2 packages:

```bash
sudo apt install -y \
git \
python3-vcstool \
python3-colcon-common-extensions \
python3-rosdep \
ros-jazzy-ros-gz \
ros-jazzy-tf2-tools \
ros-jazzy-teleop-twist-keyboard
```

Initialize `rosdep` if it has not already been initialized:

```bash
sudo rosdep init
rosdep update
```

---

## 3. Create the TurtleBot3 Workspace

Create the workspace:

```bash
mkdir -p ~/turtlebot3_ws/src
```

Move into the workspace:

```bash
cd ~/turtlebot3_ws
```

---

## 4. Create the Repository File

Create the repository file:

```bash
nano turtlebot3.repos
```

Add the following content:

```yaml
repositories:
  turtlebot3/turtlebot3:
    type: git
    url: https://github.com/ROBOTIS-GIT/turtlebot3.git
    version: jazzy

  turtlebot3/turtlebot3_msgs:
    type: git
    url: https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git
    version: jazzy

  turtlebot3/turtlebot3_simulations:
    type: git
    url: https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
    version: jazzy

  utils/DynamixelSDK:
    type: git
    url: https://github.com/ROBOTIS-GIT/DynamixelSDK.git
    version: jazzy

  utils/hls_lfcd_lds_driver:
    type: git
    url: https://github.com/ROBOTIS-GIT/hls_lfcd_lds_driver.git
    version: jazzy
```

Save and exit.

Import the repositories:

```bash
vcs import src < turtlebot3.repos
```

---

## 5. Install Package Dependencies

Source ROS 2 Jazzy:

```bash
source /opt/ros/jazzy/setup.bash
```

Install the dependencies:

```bash
rosdep install \
  --from-paths src \
  --ignore-src \
  -r -y
```

---

## 6. Build the Workspace

Move to the workspace:

```bash
cd ~/turtlebot3_ws
```

Build the packages:

```bash
colcon build --symlink-install
```

Source the workspace:

```bash
source install/setup.bash
```

---

## 7. Configure the Environment

Add ROS 2 and TurtleBot3 configuration to `.bashrc`:

```bash
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
echo "source ~/turtlebot3_ws/install/setup.bash" >> ~/.bashrc
echo "export TURTLEBOT3_MODEL=waffle_pi" >> ~/.bashrc
```

Reload the terminal environment:

```bash
source ~/.bashrc
```

Verify the TurtleBot3 model:

```bash
echo $TURTLEBOT3_MODEL
```

Expected output:

```text
waffle_pi
```

---

## 8. Launch TurtleBot3 Simulation

Start the TurtleBot3 simulation:

```bash
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py
```

Gazebo Harmonic should open with the **TurtleBot3 Waffle Pi** inside the house world.

Make sure the Gazebo physics simulation is running.

---

## 9. Visualize the Robot in RViz2

Open another terminal:

```bash
source ~/.bashrc
rviz2
```

In RViz2, set:

```text
Fixed Frame: odom
```

Add the following displays:

- TF
- LaserScan
- Image

### LaserScan Configuration

Set:

```text
Topic: /scan
QoS Reliability: Best Effort
```

### Camera Configuration

Set:

```text
Topic: /camera/image_raw
QoS Reliability: Best Effort
```

The RViz2 window should display:

- Robot TF frames
- Laser scan data
- Camera feed

---

## 10. Inspect ROS 2 Nodes and Topics

List all active ROS 2 nodes:

```bash
ros2 node list
```

Inspect a particular node:

```bash
ros2 node info <node_name>
```

List all available topics:

```bash
ros2 topic list
```

Inspect a topic:

```bash
ros2 topic info <topic_name>
```

For example:

```bash
ros2 topic info /scan
```

---

## 11. Generate the TF Tree

Generate the TF frame diagram:

```bash
ros2 run tf2_tools view_frames
```

This generates:

```text
frames.pdf
```

Open the generated TF diagram:

```bash
xdg-open frames.pdf
```

---

## 12. Teleoperate the TurtleBot3

In ROS 2 Jazzy with Gazebo Harmonic, TurtleBot3 uses:

```text
geometry_msgs/msg/TwistStamped
```

Run the keyboard teleoperation node with stamped messages enabled:

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard \
  --ros-args \
  -p stamped:=true \
  -p frame_id:=base_link
```

Click inside the teleoperation terminal and use:

```text
u   i   o
j   k   l
m   ,   .
```

The TurtleBot3 should move inside Gazebo.

---

## 13. Verify Velocity Commands

Check the available command topics:

```bash
ros2 topic list | grep cmd
```

Inspect `/cmd_vel`:

```bash
ros2 topic info /cmd_vel --verbose
```

The expected message type is:

```text
geometry_msgs/msg/TwistStamped
```

Monitor the velocity commands:

```bash
ros2 topic echo /cmd_vel geometry_msgs/msg/TwistStamped
```

---

## 14. Verify Simulation Time

Check whether Gazebo is publishing simulation time:

```bash
ros2 topic hz /clock
```

A non-zero frequency should be displayed.

If no data appears:

- Ensure Gazebo is running.
- Ensure Gazebo physics is not paused.

---

# Troubleshooting

## Problem 1: Robot Does Not Move

Check the `/cmd_vel` topic:

```bash
ros2 topic info /cmd_vel --verbose
```

Make sure both publisher and subscriber use:

```text
geometry_msgs/msg/TwistStamped
```

Run teleoperation with:

```bash
-p stamped:=true
```

---

## Problem 2: No Laser or Camera Data in RViz2

Set QoS Reliability to:

```text
Best Effort
```

for:

```text
/scan
/camera/image_raw
```

---

## Problem 3: TF Errors in RViz2

Set:

```text
Fixed Frame = odom
```

and add the:

```text
TF
```

display.

---

## Problem 4: Changes Are Lost After Opening a New Terminal

Reload the environment:

```bash
source ~/.bashrc
```

Verify:

```bash
echo $ROS_DISTRO
echo $TURTLEBOT3_MODEL
```

Expected:

```text
jazzy
waffle_pi
```

---

# Important ROS 2 Commands

### Launch Simulation

```bash
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py
```

### Launch RViz2

```bash
rviz2
```

### Run Teleoperation

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard \
  --ros-args \
  -p stamped:=true \
  -p frame_id:=base_link
```

### List Nodes

```bash
ros2 node list
```

### List Topics

```bash
ros2 topic list
```

### Inspect `/cmd_vel`

```bash
ros2 topic info /cmd_vel --verbose
```

### Generate TF Tree

```bash
ros2 run tf2_tools view_frames
```

### Monitor Simulation Time

```bash
ros2 topic hz /clock
```

### Monitor Velocity Commands

```bash
ros2 topic echo /cmd_vel geometry_msgs/msg/TwistStamped
```

---

# Expected Result

The TurtleBot3 Waffle Pi simulation is successfully launched in **Gazebo Harmonic** using **ROS 2 Jazzy**. The robot is visualized in **RViz2**, its TF frames, laser scan and camera data are observed, and the robot is successfully teleoperated using the keyboard.

---

# Result

Thus, the **TurtleBot3 simulation environment was successfully configured and operated using ROS 2 Jazzy, Gazebo Harmonic, and RViz2**.

---

# Viva Questions

1. What is TurtleBot3?
2. What is ROS 2?
3. What is the purpose of Gazebo in robotics?
4. What is RViz2?
5. What is the purpose of `colcon build`?
6. What is the purpose of `rosdep`?
7. What is a ROS 2 node?
8. What is a ROS 2 topic?
9. What is the purpose of `/cmd_vel`?
10. What is the difference between `Twist` and `TwistStamped`?
11. Why is `TwistStamped` required for this TurtleBot3 simulation?
12. What is the purpose of the TF tree?
13. What is the `odom` frame?
14. Why is QoS Reliability set to **Best Effort** for `/scan`?
15. What is the purpose of the `/clock` topic?
16. What is the purpose of `TURTLEBOT3_MODEL`?
17. What is the purpose of `vcs import`?
18. How can you inspect the information of a ROS 2 topic?
19. How can you generate a TF tree?
20. What is teleoperation?

---

## Conclusion

A complete TurtleBot3 simulation environment was configured using **Ubuntu 24.04, ROS 2 Jazzy, Gazebo Harmonic, and RViz2**. The robot was successfully simulated, visualized, inspected using ROS 2 tools, and controlled through keyboard teleoperation.
