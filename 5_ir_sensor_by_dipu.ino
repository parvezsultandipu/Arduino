//These pins must be PWM pins of arduino
#define inA 10
#define inB 9
#define inC 6
#define inD 5

const int irPins[5] = {A4, A3, A2, A1, A0};

void wheel(int lm, int rm);
int s[5] = {0, 0, 0, 0, 0};
int i, lastSensor, lastError;
int spee = 80;

int uturn = 120;
int base_L = spee;
int base_R = spee;
float kp = 8;
float kd = 15;

void setup()
{
  mot_init();
  other_init();

}
void loop()
{
  if (Serial.available() > 0) {
    kp = Serial.parseFloat();
    kd = Serial.parseFloat();
    spee = Serial.parseInt();
    uturn = Serial.parseInt();
  }
  line_follow();
  //wheel(255,-255);


}


void other_init()
{
  lastSensor = 0;
  lastError = 0;
  Serial.begin(9600);
}

void mot_init()
{
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);


}

void wheel(int lm, int rm)
{
  if (lm == 0)
  {
    analogWrite(inC, 0);
    analogWrite(inD, 0);
  }
  if (lm > 0)
  {
    analogWrite(inC, abs(lm));
    analogWrite(inD, 0);
  }
  else if (lm < 0)
  {
    analogWrite(inC, 0);
    analogWrite(inD, abs(lm));
  }
  if (rm == 0)
  {

    analogWrite(inA, 0);
    analogWrite(inB, 0);
  }
  if (rm > 0)
  {

    analogWrite(inA, abs(rm));
    analogWrite(inB, 0);
  }
  else if (rm < 0)
  {

    analogWrite(inA, 0);
    analogWrite(inB, abs(rm));
  }
  if (lm > 254) lm = 254;
  if (lm < -254) lm = -254;
  if (rm > 254) rm = 254;
  if (rm < -254) rm = -254;
}

int readSensor()
{

  s[0] = digitalRead(irPins[0]);
  s[1] = digitalRead(irPins[1]);
  s[2] = digitalRead(irPins[2]);
  s[3] = digitalRead(irPins[3]);
  s[4] = digitalRead(irPins[4]);
  s[0] = 1 - s[0];
  s[1] = 1 - s[1];
  s[2] = 1 - s[2];
  s[3] = 1 - s[3];
  s[4] = 1 - s[4];

  int error, sum;
  sum = s[0] + s[1] + s[2] + s[3] + s[4];
  //--------

  if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1) {
    wheel(-uturn, uturn);
  }


  //----
  if (sum != 0)
  {
    error = (s[0] * 10 + s[1] * 20 + s[2] * 30 + s[3] * 40 + s[4] * 50) / sum - 30;
  }
  else
  {
    error = 420;
  }

  if (s[0] == 1) lastSensor = 1;
  else if (s[4] == 1) lastSensor = 2;
  Serial.print(30);
  Serial.print(" ");

  Serial.println(error);
  //Serial.print(" ");
  return error;
}


void line_follow()
{
  int error, corr;
  float p, d;
  error = readSensor();
  if (error == 420)
  {

    if (lastSensor == 1) wheel(-uturn, uturn);
    else if (lastSensor == 2) wheel(uturn, -uturn);
  }
  else
  {
    p = kp * error;
    d = kd * (error - lastError);
    corr = p + d;
    //Serial.println(corr);
    wheel(base_L + corr, base_R - corr);
    if ((error - lastError) != 0) delay(5);
    lastError = error;
  }
}
