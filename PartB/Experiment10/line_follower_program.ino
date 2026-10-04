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
