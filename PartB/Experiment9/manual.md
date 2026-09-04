# Experiment 9: Localization of a Mobile Robot Using LiDAR

## Aim

To simulate a custom mobile robot equipped with a 2D LiDAR sensor in ROS 2 Jazzy and perform robot localization using LiDAR data, odometry, a known map, and the AMCL localization algorithm.

---

# Theory

## Robot Localization

Robot localization is the process of determining the position and orientation of a robot within an environment.

In simple terms, localization answers the question:

> **Where is the robot?**

The pose of a mobile robot in a two-dimensional environment is represented as:

```text
(x, y, θ)
```

Where:

- `x` is the position along the X-axis.
- `y` is the position along the Y-axis.
- `θ` is the orientation of the robot.

---

# LiDAR

LiDAR stands for **Light Detection and Ranging**.

A LiDAR sensor measures the distance between the robot and surrounding objects.

In this experiment, the custom robot uses a simulated 2D LiDAR sensor.

The sensor publishes data through:

```text
/scan
```

The ROS 2 message type is:

```text
sensor_msgs/msg/LaserScan
```

The robot uses the laser scan data to detect surrounding walls and obstacles.

```text
              Wall
    ──────────────────────

         *   *   *
       *           *
     *    ROBOT      *
       *           *
         *   *   *
```

---

# AMCL

AMCL stands for:

**Adaptive Monte Carlo Localization**

AMCL is a probabilistic localization algorithm based on a particle filter.

It uses:

- A known map
- LiDAR sensor data
- Robot odometry

to estimate the robot's pose.

```text
                 Known Map
                     │
                     ▼
LiDAR Data ───────► AMCL ◄────── Odometry
  (/scan)             │             (/odom)
                      │
                      ▼
             Estimated Robot Pose
                 (/amcl_pose)
```

---

# ROS 2 Localization Workflow

The complete workflow of this experiment is:

```text
             Custom Mobile Robot
                      │
          ┌───────────┴───────────┐
          │                       │
          ▼                       ▼
      Odometry                  LiDAR
      /odom                     /scan
          │                       │
          └───────────┬───────────┘
                      ▼
                 SLAM Toolbox
                      │
                      ▼
                    /map
                      │
                      ▼
                  Save Map
                      │
                      ▼
                  Known Map
                      │
                      ▼
                     AMCL
                      │
                      ▼
                 /amcl_pose
                      │
                      ▼
                     RViz2
```

---

# Important ROS 2 Topics

| Topic | Description |
|---|---|
| `/scan` | LiDAR sensor data |
| `/odom` | Robot odometry |
| `/map` | Occupancy grid map |
| `/tf` | Coordinate transformations |
| `/tf_static` | Static transformations |
| `/cmd_vel` | Velocity command |
| `/amcl_pose` | Estimated robot pose |
| `/initialpose` | Initial pose for AMCL |

---

# Coordinate Frames

The robot coordinate frames used in this experiment are:

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
laser_link
```

Where:

- `map` represents the global environment.
- `odom` represents the odometry reference frame.
- `base_link` represents the main body of the robot.
- `laser_link` represents the LiDAR sensor frame.

---

# Requirements

- Ubuntu 24.04 LTS
- ROS 2 Jazzy Jalisco
- Gazebo Harmonic
- RViz2
- ROS-Gazebo Bridge
- SLAM Toolbox
- Navigation2
- AMCL
- Python 3

---

# Part A – Create the Workspace

## Step 1: Open Terminal

Open a terminal using:

```text
Ctrl + Alt + T
```

---

## Step 2: Source ROS 2 Jazzy

```bash
source /opt/ros/jazzy/setup.bash
```

To automatically source ROS 2:

```bash
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

---

## Step 3: Create a Workspace

```bash
mkdir -p ~/lidar_bot_ws/src
cd ~/lidar_bot_ws
```

---

## Step 4: Create the Robot Description Package

```bash
cd ~/lidar_bot_ws/src

ros2 pkg create my_robot_description \
--build-type ament_python
```

Create the required directories:

```bash
cd ~/lidar_bot_ws/src/my_robot_description

mkdir launch
mkdir urdf
mkdir worlds
mkdir rviz
mkdir config
mkdir maps
```

The package structure should be:

```text
my_robot_description/
├── config/
├── launch/
├── maps/
├── my_robot_description/
│   └── __init__.py
├── resource/
│   └── my_robot_description
├── rviz/
├── urdf/
├── worlds/
├── package.xml
├── setup.cfg
└── setup.py
```

---

# Part B – Configure the Package

## Step 5: Update `package.xml`

Open:

```bash
nano package.xml
```

Add the following dependencies before the closing `</package>` tag:

```xml
<exec_depend>robot_state_publisher</exec_depend>
<exec_depend>rviz2</exec_depend>
<exec_depend>ros_gz_sim</exec_depend>
<exec_depend>ros_gz_bridge</exec_depend>
<exec_depend>tf2_ros</exec_depend>
```

Save using:

```text
Ctrl + O
```

Press:

```text
Enter
```

Exit using:

```text
Ctrl + X
```

---

## Step 6: Configure `setup.py`

Replace the contents of `setup.py` with:

```python
from setuptools import find_packages, setup
from glob import glob
import os

package_name = 'my_robot_description'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        (
            'share/ament_index/resource_index/packages',
            ['resource/' + package_name]
        ),
        (
            'share/' + package_name,
            ['package.xml']
        ),
        (
            os.path.join('share', package_name, 'launch'),
            glob('launch/*.py')
        ),
        (
            os.path.join('share', package_name, 'urdf'),
            glob('urdf/*')
        ),
        (
            os.path.join('share', package_name, 'worlds'),
            glob('worlds/*')
        ),
        (
            os.path.join('share', package_name, 'rviz'),
            glob('rviz/*')
        ),
        (
            os.path.join('share', package_name, 'maps'),
            glob('maps/*')
        ),
        (
            os.path.join('share', package_name, 'config'),
            glob('config/*')
        ),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='student',
    maintainer_email='student@example.com',
    description='Custom mobile robot with LiDAR for ROS 2 localization',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [],
    },
)
```

---

## Step 7: Verify `setup.cfg`

Ensure that `setup.cfg` contains:

```ini
[develop]
script_dir=$base/lib/my_robot_description

[install]
install_scripts=$base/lib/my_robot_description
```

---

# Part C – Create the Custom Robot

## Step 8: Create the Robot URDF

Create:

```bash
nano urdf/robot.urdf
```

Add the following robot description:

```xml
<?xml version="1.0"?>

<robot name="mini_rover">

  <!-- Robot Base -->

  <link name="base_link">

    <visual>
      <geometry>
        <box size="0.3 0.2 0.1"/>
      </geometry>

      <material name="blue">
        <color rgba="0.2 0.4 0.8 1.0"/>
      </material>
    </visual>

    <collision>
      <geometry>
        <box size="0.3 0.2 0.1"/>
      </geometry>
    </collision>

    <inertial>
      <mass value="2.0"/>

      <origin xyz="0 0 0"/>

      <inertia
        ixx="0.02"
        ixy="0.0"
        ixz="0.0"
        iyy="0.02"
        iyz="0.0"
        izz="0.02"/>
    </inertial>

  </link>

  <!-- LiDAR Sensor -->

  <link name="laser_link">

    <visual>
      <geometry>
        <cylinder radius="0.03" length="0.05"/>
      </geometry>

      <material name="black">
        <color rgba="0.1 0.1 0.1 1.0"/>
      </material>

    </visual>

  </link>

  <!-- LiDAR Joint -->

  <joint name="laser_joint" type="fixed">

    <parent link="base_link"/>

    <child link="laser_link"/>

    <origin xyz="0.1 0 0.08" rpy="0 0 0"/>

  </joint>

  <!-- Gazebo LiDAR -->

  <gazebo reference="laser_link">

    <sensor name="lidar" type="gpu_lidar">

      <update_rate>10</update_rate>

      <topic>scan</topic>

      <gz_frame_id>laser_link</gz_frame_id>

      <ray>

        <scan>

          <horizontal>

            <samples>360</samples>

            <resolution>1</resolution>

            <min_angle>-3.14159</min_angle>

            <max_angle>3.14159</max_angle>

          </horizontal>

        </scan>

        <range>

          <min>0.12</min>

          <max>8.0</max>

        </range>

      </ray>

    </sensor>

  </gazebo>

</robot>
```

The custom robot model contains a `base_link`, fixed `laser_link`, and a Gazebo GPU LiDAR sensor configured with 360 samples and a scan range of 0.12 m to 8.0 m. :contentReference[oaicite:1]{index=1}

---

## Step 9: Verify the URDF

Run:

```bash
check_urdf urdf/robot.urdf
```

Expected output:

```text
Successfully Parsed XML
```

---

# Part D – Create the Gazebo World

## Step 10: Create the World File

Create:

```bash
nano worlds/localization_world.sdf
```

Add:

```xml

<?xml version="1.0"?>

<robot name="mini_rover">

  <!-- ============================================================ -->
  <!-- BASE LINK -->
  <!-- ============================================================ -->

  <link name="base_link">

    <visual>
      <geometry>
        <box size="0.40 0.30 0.10"/>
      </geometry>

      <material name="blue">
        <color rgba="0.2 0.4 0.8 1.0"/>
      </material>
    </visual>

    <collision>
      <geometry>
        <box size="0.40 0.30 0.10"/>
      </geometry>
    </collision>

    <inertial>
      <origin xyz="0 0 0"/>
      <mass value="5.0"/>

      <inertia
        ixx="0.05"
        ixy="0.0"
        ixz="0.0"
        iyy="0.05"
        iyz="0.0"
        izz="0.10"/>
    </inertial>

  </link>


  <!-- ============================================================ -->
  <!-- FRONT LEFT WHEEL -->
  <!-- ============================================================ -->

  <link name="front_left_wheel">

    <visual>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>

      <material name="black">
        <color rgba="0.1 0.1 0.1 1.0"/>
      </material>
    </visual>

    <collision>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>
    </collision>

    <inertial>
      <mass value="0.2"/>

      <inertia
        ixx="0.0002"
        ixy="0.0"
        ixz="0.0"
        iyy="0.0002"
        iyz="0.0"
        izz="0.0002"/>
    </inertial>

  </link>


  <!-- ============================================================ -->
  <!-- FRONT RIGHT WHEEL -->
  <!-- ============================================================ -->

  <link name="front_right_wheel">

    <visual>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>

      <material name="black">
        <color rgba="0.1 0.1 0.1 1.0"/>
      </material>
    </visual>

    <collision>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>
    </collision>

    <inertial>
      <mass value="0.2"/>

      <inertia
        ixx="0.0002"
        ixy="0.0"
        ixz="0.0"
        iyy="0.0002"
        iyz="0.0"
        izz="0.0002"/>
    </inertial>

  </link>


  <!-- ============================================================ -->
  <!-- REAR LEFT WHEEL -->
  <!-- ============================================================ -->

  <link name="rear_left_wheel">

    <visual>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>

      <material name="black">
        <color rgba="0.1 0.1 0.1 1.0"/>
      </material>
    </visual>

    <collision>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>
    </collision>

    <inertial>
      <mass value="0.2"/>

      <inertia
        ixx="0.0002"
        ixy="0.0"
        ixz="0.0"
        iyy="0.0002"
        iyz="0.0"
        izz="0.0002"/>
    </inertial>

  </link>


  <!-- ============================================================ -->
  <!-- REAR RIGHT WHEEL -->
  <!-- ============================================================ -->

  <link name="rear_right_wheel">

    <visual>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>

      <material name="black">
        <color rgba="0.1 0.1 0.1 1.0"/>
      </material>
    </visual>

    <collision>
      <origin xyz="0 0 0" rpy="1.5708 0 0"/>

      <geometry>
        <cylinder radius="0.05" length="0.03"/>
      </geometry>
    </collision>

    <inertial>
      <mass value="0.2"/>

      <inertia
        ixx="0.0002"
        ixy="0.0"
        ixz="0.0"
        iyy="0.0002"
        iyz="0.0"
        izz="0.0002"/>
    </inertial>

  </link>


  <!-- ============================================================ -->
  <!-- LiDAR -->
  <!-- ============================================================ -->

  <link name="laser_link">

    <visual>
      <geometry>
        <cylinder radius="0.04" length="0.05"/>
      </geometry>

      <material name="lidar_black">
        <color rgba="0.05 0.05 0.05 1.0"/>
      </material>
    </visual>

    <collision>
      <geometry>
        <cylinder radius="0.04" length="0.05"/>
      </geometry>
    </collision>

    <inertial>
      <mass value="0.10"/>

      <inertia
        ixx="0.0001"
        ixy="0.0"
        ixz="0.0"
        iyy="0.0001"
        iyz="0.0"
        izz="0.0001"/>
    </inertial>

  </link>


  <!-- ============================================================ -->
  <!-- WHEEL JOINTS -->
  <!-- ============================================================ -->

  <joint name="front_left_joint" type="continuous">

    <parent link="base_link"/>
    <child link="front_left_wheel"/>

    <origin xyz="0.12 0.16 -0.05"/>

    <axis xyz="0 1 0"/>

  </joint>


  <joint name="front_right_joint" type="continuous">

    <parent link="base_link"/>
    <child link="front_right_wheel"/>

    <origin xyz="0.12 -0.16 -0.05"/>

    <axis xyz="0 1 0"/>

  </joint>


  <joint name="rear_left_joint" type="continuous">

    <parent link="base_link"/>
    <child link="rear_left_wheel"/>

    <origin xyz="-0.12 0.16 -0.05"/>

    <axis xyz="0 1 0"/>

  </joint>


  <joint name="rear_right_joint" type="continuous">

    <parent link="base_link"/>
    <child link="rear_right_wheel"/>

    <origin xyz="-0.12 -0.16 -0.05"/>

    <axis xyz="0 1 0"/>

  </joint>


  <!-- ============================================================ -->
  <!-- LiDAR JOINT -->
  <!-- ============================================================ -->

  <joint name="laser_joint" type="fixed">

    <parent link="base_link"/>

    <child link="laser_link"/>

    <!-- LiDAR mounted on top of robot -->

    <origin xyz="0 0 0.10" rpy="0 0 0"/>

  </joint>


  <!-- ============================================================ -->
  <!-- GAZEBO DIFFERENTIAL DRIVE -->
  <!-- ============================================================ -->

  <gazebo>

    <plugin
      filename="gz-sim-diff-drive-system"
      name="gz::sim::systems::DiffDrive">

      <left_joint>front_left_joint</left_joint>
      <left_joint>rear_left_joint</left_joint>

      <right_joint>front_right_joint</right_joint>
      <right_joint>rear_right_joint</right_joint>

      <wheel_separation>0.32</wheel_separation>

      <wheel_radius>0.05</wheel_radius>

      <topic>cmd_vel</topic>

      <odom_topic>odom</odom_topic>

      <frame_id>odom</frame_id>

      <child_frame_id>base_link</child_frame_id>

    </plugin>

  </gazebo>


  <!-- ============================================================ -->
  <!-- GAZEBO 2D LiDAR SENSOR -->
  <!-- ============================================================ -->

  <gazebo reference="laser_link">

    <sensor name="lidar" type="gpu_lidar">

      <always_on>true</always_on>

      <update_rate>10</update_rate>

      <topic>scan</topic>

      <gz_frame_id>laser_link</gz_frame_id>

      <ray>

        <scan>

          <horizontal>

            <samples>360</samples>

            <resolution>1</resolution>

            <min_angle>-3.14159</min_angle>

            <max_angle>3.14159</max_angle>

          </horizontal>

        </scan>

        <range>

          <min>0.12</min>

          <max>8.0</max>

          <resolution>0.01</resolution>

        </range>

      </ray>

    </sensor>

  </gazebo>


</robot>

</sdf>
```

The obstacles provide surfaces that generate LiDAR returns. The provided robot simulation material uses a static box obstacle specifically for this purpose. :contentReference[oaicite:2]{index=2}

---

# Part E – Create the Simulation Launch File

## Step 11: Create `sim.launch.py`

Create:

```bash
nano launch/sim.launch.py
```

Add:

```python
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

import os


def generate_launch_description():

    pkg_path = get_package_share_directory(
        'my_robot_description'
    )

    urdf_file = os.path.join(
        pkg_path,
        'urdf',
        'robot.urdf'
    )

    world_file = os.path.join(
        pkg_path,
        'worlds',
        'localization_world.sdf'
    )

    with open(urdf_file, 'r') as file:
        robot_description = file.read()

    return LaunchDescription([

        ExecuteProcess(
            cmd=[
                'gz',
                'sim',
                '-r',
                world_file
            ],
            output='screen'
        ),

        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[{
                'robot_description': robot_description,
                'use_sim_time': True
            }],
            output='screen'
        ),

        Node(
            package='ros_gz_sim',
            executable='create',
            arguments=[
                '-string',
                robot_description,
                '-name',
                'mini_rover'
            ],
            output='screen'
        ),

        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            arguments=[
                '/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock',
                '/scan@sensor_msgs/msg/LaserScan@gz.msgs.LaserScan'
            ],
            output='screen'
        )

    ])
```

The supplied launch-file structure starts Gazebo, publishes the robot state, spawns the `mini_rover`, and bridges the clock and LiDAR scan data between Gazebo and ROS 2. :contentReference[oaicite:3]{index=3}

---

# Part F – Build and Run the Simulation

## Step 12: Build the Workspace

```bash
cd ~/lidar_bot_ws

colcon build --symlink-install
```

---

## Step 13: Source the Workspace

```bash
source install/setup.bash
```

---

## Step 14: Launch the Custom Robot

```bash
ros2 launch my_robot_description sim.launch.py
```

Gazebo Harmonic should open and display the custom `mini_rover`.

---

# Part G – Verify LiDAR Data

## Step 15: Check Available Topics

Open another terminal:

```bash
cd ~/lidar_bot_ws

source /opt/ros/jazzy/setup.bash
source install/setup.bash
```

Run:

```bash
ros2 topic list
```

Check for:

```text
/scan
```

---

## Step 16: Display LiDAR Messages

```bash
ros2 topic echo /scan
```

You should observe messages of type:

```text
sensor_msgs/msg/LaserScan
```

The `ranges` array contains distance measurements from the LiDAR sensor.

---

## Step 17: Check LiDAR Topic Information

```bash
ros2 topic info /scan
```

---

# Part H – Visualize LiDAR Data in RViz2

## Step 18: Start RViz2

```bash
rviz2
```

---

## Step 19: Configure RViz2

1. Set **Fixed Frame** to:

```text
base_link
```

2. Click **Add**.

3. Select:

```text
By Topic
```

4. Select:

```text
/scan
```

5. Add:

```text
LaserScan
```

The LiDAR scan should now be visible.

---

# Part I – Install Mapping and Localization Packages

## Step 20: Install Required Packages

```bash
sudo apt update

sudo apt install ros-jazzy-slam-toolbox

sudo apt install ros-jazzy-navigation2

sudo apt install ros-jazzy-nav2-bringup

sudo apt install ros-jazzy-teleop-twist-keyboard
```

---

# Part J – Mapping Using SLAM Toolbox

> **Note:** Mapping requires the robot to move through the environment and provide appropriate odometry and TF information.

## Step 21: Start SLAM Toolbox

Open another terminal:

```bash
source /opt/ros/jazzy/setup.bash
source ~/lidar_bot_ws/install/setup.bash
```

Run:

```bash
ros2 launch slam_toolbox online_async_launch.py use_sim_time:=true
```

---

## Step 22: Visualize the Map

Open RViz2:

```bash
rviz2
```

Set:

```text
Fixed Frame = map
```

Add:

```text
/map
```

Move the robot through the environment.

The map should gradually be generated.

---

# Part K – Save the Map

## Step 23: Create the Map Directory

```bash
mkdir -p ~/lidar_bot_ws/src/my_robot_description/maps
```

---

## Step 24: Save the Map

```bash
ros2 run nav2_map_server map_saver_cli \
-f ~/lidar_bot_ws/src/my_robot_description/maps/lab_map
```

The following files will be generated:

```text
lab_map.yaml
lab_map.pgm
```

---

# Part L – Localization Using AMCL

> **Important:** AMCL requires:
>
> - A known map
> - LiDAR data
> - Robot odometry
> - A valid TF relationship between `odom` and `base_link`

## Step 25: Stop SLAM

Press:

```text
Ctrl + C
```

Stop the mapping process after the map has been saved.

---

## Step 26: Restart the Simulation

```bash
ros2 launch my_robot_description sim.launch.py
```

---

## Step 27: Start AMCL and Map Server

```bash
ros2 launch nav2_bringup localization_launch.py \
use_sim_time:=true \
map:=$HOME/lidar_bot_ws/src/my_robot_description/maps/lab_map.yaml
```

This starts:

- Map Server
- AMCL Localization

---

# Part M – Set the Initial Pose

## Step 28: Start RViz2

```bash
rviz2
```

Set:

```text
Fixed Frame = map
```

Add:

```text
/map
/scan
/amcl_pose
```

---

## Step 29: Set Initial Pose

In RViz2:

1. Select **2D Pose Estimate**.
2. Click on the approximate location of the robot.
3. Drag the arrow in the direction in which the robot is facing.

This publishes an initial pose to:

```text
/initialpose
```

---

# Part N – Monitor Localization

## Step 30: Check the Estimated Pose

Run:

```bash
ros2 topic echo /amcl_pose
```

Example:

```text
pose:
  pose:

    position:

      x: 1.25
      y: 0.80

    orientation:

      z: 0.32
      w: 0.94
```

The values represent the estimated position and orientation of the robot.

---

# Part O – Verify the TF Tree

## Step 31: Generate the TF Frame Diagram

Run:

```bash
ros2 run tf2_tools view_frames
```

A file named:

```text
frames.pdf
```

will be generated.

The expected frame relationship is:

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
laser_link
```

---

# Important Note About the Current Robot Model

The basic custom robot model used in this experiment provides:

- `base_link`
- `laser_link`
- Simulated LiDAR
- `/scan` topic

For complete SLAM and AMCL localization, the robot must additionally provide:

```text
Differential Drive
        │
        ▼
Wheel Motion
        │
        ▼
Odometry
       /odom
        │
        ▼
TF Transform
odom → base_link
```

Therefore, before performing full autonomous mapping and localization, the custom robot must be extended with wheels, a differential-drive controller or simulation plugin, and odometry generation.

The supplied material also identifies differential drive, wheel encoders, SLAM Toolbox, AMCL, and Nav2 as the next extensions of the current LiDAR robot simulation. 

---

# Expected Output

After completing the experiment, students should observe:

1. Successful creation of a custom ROS 2 robot package.
2. Successful creation of the `mini_rover` URDF.
3. Successful simulation of the robot in Gazebo Harmonic.
4. LiDAR data published through `/scan`.
5. LiDAR data visualized in RViz2.
6. Generation of an occupancy grid map after odometry support is available.
7. Map saved as `.yaml` and `.pgm` files.
8. AMCL localization using the saved map.
9. Estimated robot pose published through `/amcl_pose`.
10. Robot pose updated as the robot moves.

---

# Applications

LiDAR-based localization is used in:

- Autonomous Mobile Robots
- Warehouse Robots
- Delivery Robots
- Industrial Robots
- Service Robots
- Agricultural Robots
- Hospital Robots
- Search and Rescue Robots
- Autonomous Navigation Systems

---

# Result

The custom mobile robot equipped with a simulated 2D LiDAR sensor was successfully created and simulated using ROS 2 Jazzy and Gazebo Harmonic. LiDAR data was bridged to ROS 2 and visualized using RViz2. The system architecture required for mapping and localization using SLAM Toolbox and AMCL was studied and configured.

After adding robot motion, odometry, and the required TF transformations, the robot can generate a map of the environment and localize itself using LiDAR measurements and the AMCL algorithm.

---

# Conclusion

This experiment demonstrated the basic architecture of a LiDAR-based mobile robot localization system using a custom robot model in ROS 2 Jazzy.

The custom `mini_rover` was equipped with a simulated 2D LiDAR sensor and launched in Gazebo Harmonic. The sensor data was bridged to ROS 2 through the `/scan` topic and visualized in RViz2.

The experiment also introduced the workflow required for robot mapping and localization using SLAM Toolbox and AMCL. Complete localization requires additional support for robot motion, odometry, and the `odom → base_link` transform.

---

# Viva Questions

1. What is robot localization?
2. What is LiDAR?
3. What does the `/scan` topic contain?
4. What is the ROS 2 message type used for LiDAR data?
5. What is the purpose of `laser_link`?
6. What is the purpose of `base_link`?
7. What is Gazebo Harmonic?
8. What is RViz2 used for?
9. What is AMCL?
10. What is SLAM?
11. What is the difference between SLAM and localization?
12. Why is odometry required for AMCL?
13. What is the purpose of the `/odom` topic?
14. What is a TF transform?
15. Explain the relationship between `map`, `odom`, and `base_link`.
16. What is an occupancy grid map?
17. Why is an initial pose required for AMCL?
18. What is the role of the ROS-Gazebo bridge?
19. What is the purpose of the `/amcl_pose` topic?
20. What additional components are required to convert the current LiDAR robot into a fully localizable mobile robot?

---
