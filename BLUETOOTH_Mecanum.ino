//first , you need to insstall the motor driver for L293D motor driver
// Go to Sketch-> Include Librabry-> Manage Library-> Search for Adafruit Motor Shield V1
#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial HC05(10, 9); // RX, TX

//initial motors pin
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char command;
boolean state = 0;
void setup()
{
  HC05.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop() {
  if (HC05.available() > 0) {
    command = HC05.read();
 Serial.println(command);
    Stop(); //initialize with motors stoped
    if (command == 'X') {
      state = 1;
    } else if (command == 'x') {
      state = 0;
    }
    if (command == 'F') {
      forward();
    } else if (command == 'B') {
      back();
    } else if (command == 'R' && state == 1) {
      Rotateright();
    } else if (command == 'L' && state == 1) {
      Rotateleft();
    } else if (command == 'R' && state == 0) {
      right();
    } else if (command == 'L' && state == 0) {
      left();
    } else if (command == 'G' && state == 0) {
     Forwardleft();
    } else if (command == 'I' && state == 0) {
     Forwardright();
    } 
      else if (command == 'H' && state == 0) {
     Backwardleft();
    } else if (command == 'J' && state == 0) {
     Backwardright();
    } else {
      Stop();
    }
  }
} 
    
 
void forward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void right()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); // Define maximum velocity
  motor4.run(BACKWARD);  //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD);  //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
void Forwardleft()
{
  motor1.setSpeed(0); //Set the speed to 0
  motor1.run(RELEASE);  
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(0); //Set the speed to 0
  motor3.run(RELEASE); 
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
void Forwardright()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(0); //Set the speed to 0
  motor2.run(RELEASE);  
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(0); //Set the speed to 0
  motor4.run(RELEASE); 
}
void Backwardleft()
{
  motor1.setSpeed(255); //Define lower velocity
  motor1.run(BACKWARD);  //rotate the motor clockwise
  motor2.setSpeed(0); //Set the speed to 0
  motor2.run(RELEASE);  
  motor3.setSpeed(255); //Define lower velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(0); //Set the speed to 0
  motor4.run(RELEASE); 
}
void Backwardright()
{
  motor1.setSpeed(0); //Set the speed to 0
  motor1.run(RELEASE);  
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD);  //rotate the motor clockwise
  motor3.setSpeed(0); //Set the speed to 0
  motor3.run(RELEASE); 
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
void Rotateleft()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD);  //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD);  //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
void Rotateright()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD);  //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD);  //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor clockwise
}

void Stop()
{
  motor1.setSpeed(0);  //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0);  //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0);  //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0);  //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}
