# Experiment 8: Writing a Simple Publisher and Subscriber, Simple Service and Client, Recording and Playing Back Data, Reading Messages from a Bag File (Python)

---

## Aim

To learn the basic communication mechanisms in **ROS 2 Jazzy Jalisco** by creating a simple Publisher and Subscriber, implementing a Service and Client, recording topic data into a bag file, and replaying the recorded data.

---


# Theory

## Introduction

In a robot, different software modules must continuously exchange information. ROS 2 provides a standard communication framework that makes this process simple and efficient.

The most common communication methods in ROS 2 are:

- Publisher–Subscriber
- Service–Client
- Actions
- Parameters

This experiment focuses on Publisher–Subscriber communication, Service–Client communication, and recording data using ROS bags.

---

## Publisher and Subscriber

A **Publisher** continuously sends messages to a **Topic**, while a **Subscriber** receives those messages.

Communication is asynchronous, meaning both nodes work independently.

### Communication Flow

```text
Publisher Node
      │
      │  "Hello ROS 2"
      ▼
   /chatter Topic
      ▲
      │
Subscriber Node
```

### Applications

- Camera image streaming
- Lidar data
- Robot position
- Sensor readings
- Temperature monitoring

---

## Service and Client

A Service follows a **Request–Response** communication model.

The Client sends a request, and the Service processes the request before sending back a response.

```text
Client
   │
Request
   │
Service
   │
Response
```

### Applications

- Turning LEDs ON/OFF
- Resetting sensors
- Robot diagnostics
- Mathematical calculations

---

## ROS Bag

ROS Bag is used to record published topic messages into a file.

The recorded data can later be replayed exactly as it was recorded.

### Recording

```text
Publisher
     │
     ▼
 Topic (/chatter)
     │
     ▼
ros2 bag record
     │
     ▼
 Bag File
```

### Playback

```text
Bag File
    │
    ▼
ros2 bag play
    │
    ▼
Subscriber receives recorded messages
```

---

# Requirements

- Ubuntu 24.04 LTS
- ROS 2 Jazzy Jalisco
- Python 3
- Colcon Build Tool
- Terminal

---

# Procedure

## Part A – Create a ROS 2 Workspace

### Step 1: Open Terminal

Press

```text
Ctrl + Alt + T
```

---

### Step 2: Source ROS 2

```bash
source /opt/ros/jazzy/setup.bash
```

To source ROS automatically every time the terminal opens:

```bash
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

---

### Step 3: Create a Workspace

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws
```

---

### Step 4: Build the Workspace

```bash
colcon build
```

---

### Step 5: Source the Workspace

```bash
source install/setup.bash
```

---

# Part B – Publisher and Subscriber

### Step 6: Create a Python Package

```bash
cd ~/ros2_ws/src

ros2 pkg create --build-type ament_python pub_sub_py --dependencies rclpy std_msgs
```

---

### Step 7: Create Publisher Node

Create a Python file named

```text
publisher.py
```

The Publisher should

- Publish String messages
- Publish every second
- Publish to `/chatter`

Example message

```text
Hello ROS 2
```

---

### Step 8: Create Subscriber Node

Create

```text
subscriber.py
```

The Subscriber should

- Subscribe to `/chatter`
- Print incoming messages

Example Output

```text
I heard: Hello ROS 2
```

---

### Step 9: Build the Package

```bash
cd ~/ros2_ws

colcon build
```

---

### Step 10: Source the Workspace

```bash
source install/setup.bash
```

---

### Step 11: Run Publisher

Open **Terminal 1**

```bash
ros2 run pub_sub_py publisher
```

---

### Step 12: Run Subscriber

Open **Terminal 2**

```bash
source ~/ros2_ws/install/setup.bash

ros2 run pub_sub_py subscriber
```

Expected Output

```text
I heard: Hello ROS 2
```

---

# Part C – Service and Client

### Step 13: Create Service Node

Create

```text
service.py
```

Use

```text
example_interfaces/srv/AddTwoInts
```

The Service receives

```text
10
20
```

Returns

```text
30
```

---

### Step 14: Create Client Node

Create

```text
client.py
```

Example Output

```text
Request : 10 + 20

Response : 30
```

---

### Step 15: Build the Workspace

```bash
cd ~/ros2_ws

colcon build
```

---

### Step 16: Run Service

Terminal 1

```bash
ros2 run pub_sub_py service
```

---

### Step 17: Run Client

Terminal 2

```bash
ros2 run pub_sub_py client
```

Expected Output

```text
Result = 30
```

---

# Part D – Recording ROS Data

### Step 18: Start Publisher

```bash
ros2 run pub_sub_py publisher
```

---

### Step 19: Record Topic Data

Open another terminal.

```bash
ros2 bag record /chatter
```

Press

```text
Ctrl + C
```

after a few seconds.

A folder similar to the following will be created.

```text
rosbag2_YYYY_MM_DD
```

---

# Part E – Playing Back Recorded Data

### Step 20: Play the Recorded Bag

```bash
ros2 bag play rosbag2_YYYY_MM_DD
```

The Subscriber will receive the recorded messages again.

---

# Part F – Reading Bag Information

### Step 21: View Bag Information

```bash
ros2 bag info rosbag2_YYYY_MM_DD
```

Example

```text
Topics:

/chatter

Message Count : 45

Duration : 10 seconds
```

---

# Useful ROS 2 Commands

| Command | Description |
|----------|-------------|
| `ros2 node list` | Display running nodes |
| `ros2 topic list` | Display available topics |
| `ros2 topic echo /chatter` | Display topic messages |
| `ros2 topic info /chatter` | Display topic information |
| `ros2 service list` | List available services |
| `ros2 service call` | Call a service manually |
| `ros2 bag record` | Record topic messages |
| `ros2 bag play` | Replay recorded messages |
| `ros2 bag info` | Display bag file information |

---

# Expected Output

Students should observe the following:

- Publisher successfully sending messages.
- Subscriber receiving messages.
- Service responding to client requests.
- Client displaying the returned result.
- Successful recording of topic messages.
- Playback of recorded messages.
- Display of bag file information.

---

# Applications

The concepts learned in this experiment are widely used in:

- Autonomous Mobile Robots
- Industrial Robots
- Service Robots
- Drone Systems
- Warehouse Automation
- Medical Robotics
- Smart Agriculture
- Research and Education

---

# Result

The Publisher and Subscriber nodes were successfully created and executed. A Service and Client communicated correctly using the request–response model. Topic messages were recorded into a ROS bag file, replayed successfully, and the recorded data was inspected using ROS 2 command-line tools.

---

# Conclusion

This experiment introduced the fundamental communication mechanisms in ROS 2. Students learned how to exchange information between nodes using Publisher–Subscriber and Service–Client communication. They also learned how to record, replay, and inspect robot data using ROS bags, providing a strong foundation for developing advanced robotic applications using ROS 2.

---

# Viva Questions

1. What is the purpose of a Publisher in ROS 2?
2. What is the difference between a Publisher and a Service?
3. What is a Topic?
4. Why are Services used in ROS 2?
5. What is a ROS Bag?
6. Which command is used to record topic data?
7. Which command is used to replay recorded data?
8. How can you display information about a bag file?
9. What is the purpose of `colcon build`?
10. What is the difference between synchronous and asynchronous communication in ROS 2?

---

# References

1. ROS 2 Jazzy Documentation: https://docs.ros.org/en/jazzy/
2. ROS 2 Tutorials: https://docs.ros.org/en/jazzy/Tutorials.html
3. ROS Index: https://index.ros.org/
