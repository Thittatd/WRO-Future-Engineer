#include <AFMotor.h>
#include <Servo.h>

#define maxdegree 60
#define Kp 1
#define Ki 0.0
#define Kd 1.0
#define dis 20

const int trigPinr = A0;
const int echoPinr = A1;
const int trigPinl = A2;
const int echoPinl = A3;
const int trigPinf = A4;
const int echoPinf = A5;

long durationr;
long durationl;
long durationf;
float distancer;
float distancel;
float distancef;

float error, I, D, PrevError, deg;

Servo myservo;

AF_DCMotor motor(1);
void setup() {
  myservo.attach(10);
  myservo.write(90);
  pinMode(trigPinr, OUTPUT); 
  pinMode(echoPinr, INPUT); 
  pinMode(trigPinl, OUTPUT); 
  pinMode(echoPinl, INPUT); 
  pinMode(trigPinf, OUTPUT); 
  pinMode(echoPinf, INPUT); 
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  fd(100);
  ultrasonicf();
  ultrasonicr();
  // put your main code here, to run repeatedly:
  int x = distancer;
  error = dis - x;
  I = I + error;
  I = constrain(I , -maxdegree, maxdegree);
  D = error - PrevError;
  deg = (Kp * error) + (Ki * I) + (Kd * D);
  int degree = constrain(deg, -maxdegree, maxdegree);
  if (distancef < 40){
    myservo.write(150);
  }
  else{
    myservo.write(90+degree);
  }
  Serial.print("Distance: ");
  Serial.print(distancer);
  Serial.print("  ");
  Serial.print(distancel);
  Serial.print("  ");
  Serial.println(distancef);
  PrevError = error;
  
}
void fd(int spd) {
  int speedd = map(spd, -100, 100, -255, 255);
  if (speedd < 0) {
    motor.setSpeed(speedd);
    motor.run(BACKWARD);
  }
  if (speedd > 0) {
    motor.setSpeed(speedd);
    motor.run(FORWARD);
  }
  if (speedd == 0) {
    motor.run(RELEASE);
  }
}
void ultrasonicr() {
  // Clears the trigPin
  digitalWrite(trigPinr, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinr, LOW);
  durationr = pulseIn(echoPinr, HIGH);
  distancer = durationr * 0.034 / 2;
  if (distancer > dis*2){
    distancer = dis*2;
  }
  return distancer;
}
void ultrasonicl(){
  digitalWrite(trigPinl, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinl, LOW);
  durationl = pulseIn(echoPinl, HIGH);
  distancel = durationl * 0.034 / 2;
  if (distancel > dis*2){
    distancel = dis*2;
  }
  return distancel;
}
void ultrasonicf(){
  digitalWrite(trigPinf, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinf, LOW);
  durationf = pulseIn(echoPinf, HIGH);
  distancef = durationf * 0.034 / 2;
  if (distancef > dis*2){
    distancef = dis*2;
  }
  return distancef;
}
