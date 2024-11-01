//md.parves sultan//
//iub eee//
//code for qt8rc,lfr\\



#include <QTRSensors.h>

QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2, A3, A4, A5, A6, A7}, 8); // Initialize QTR-8RC sensor
const int rightMotorPin1 = 3;  // Motor A
const int rightMotorPin2 = 4;
const int leftMotorPin1 = 5;   // Motor B
const int leftMotorPin2 = 6;
const int motorSpeed = 150;    // Base speed of the motors
unsigned int sensorValues[8];

void setup() {
  Serial.begin(9600);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  // Calibrate for initial readings
  for (int i = 0; i < 400; i++) {
    qtrrc.calibrate();
    delay(20);
  }
}

void loop() {
  int position = qtrrc.readLine(sensorValues);  // Get line position

  // Adjust motor speed dynamically based on the detected position
  int leftMotorSpeed = motorSpeed;
  int rightMotorSpeed = motorSpeed;

  // Turning logic based on sensor position
  if (position < 1500) {
    // Sharp left turn
    leftMotorSpeed = motorSpeed / 2;
    rightMotorSpeed = motorSpeed;
  }
  else if (position < 2500) {
    // Slight left turn
    leftMotorSpeed = motorSpeed * 0.75;
    rightMotorSpeed = motorSpeed;
  }
  else if (position > 3500 && position < 4500) {
    // Slight right turn
    leftMotorSpeed = motorSpeed;
    rightMotorSpeed = motorSpeed * 0.75;
  }
  else if (position > 4500) {
    // Sharp right turn
    leftMotorSpeed = motorSpeed;
    rightMotorSpeed = motorSpeed / 2;
  }

  // Set motor directions based on computed speeds
  analogWrite(leftMotorPin1, leftMotorSpeed);
  analogWrite(rightMotorPin1, rightMotorSpeed);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin2, LOW);

  delay(10);  // Small delay for stability
}
