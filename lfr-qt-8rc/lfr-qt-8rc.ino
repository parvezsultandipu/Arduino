//md.parves sultan//
//iub eee//
//code for qt8rc,lfr\\



#include <QTRSensors.h>

QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2, A3, A4, A5, A6, A7}, 8);     // Initialize QTR-8RC sensor
const int rightMotorPin1 = 3;  // Motor A
const int rightMotorPin2 = 4;
const int leftMotorPin1 = 5;   // Motor B
const int leftMotorPin2 = 6;
const int motorSpeed = 150;    // Speed of the motors
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

  // Basic thresholding for turning decisions
  if (position < 2000) {
    // Turn left
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else if (position > 3000) {
    // Turn right
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else {
    // Move forward
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }

  delay(10);  // Small delay for stability
}
