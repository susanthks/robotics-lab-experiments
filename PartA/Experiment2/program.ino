const int irPin = 2;
const int trigPin = 9;
const int echoPin = 10;

const int irLED = 12;
const int usLED = 13;

long duration;
float distance;

void setup()
{
  pinMode(irPin, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(irLED, OUTPUT);
  pinMode(usLED, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // ---------- IR SENSOR ----------
  if (digitalRead(irPin) == LOW)
  {
    digitalWrite(irLED, HIGH);
    Serial.println("IR Sensor : Obstacle Detected");
  }
  else
  {
    digitalWrite(irLED, LOW);
    Serial.println("IR Sensor : No Obstacle");
  }

  // ---------- ULTRASONIC SENSOR ----------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.0343 / 2;

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 15)
      digitalWrite(usLED, HIGH);
  else
      digitalWrite(usLED, LOW);

  Serial.println("---------------------------");

  delay(1000);
}
