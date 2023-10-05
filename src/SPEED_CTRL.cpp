#include "SPEED_CTRL.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define left_pin    A1
#define right_pin   A2

int speed = 90;//80
int max_speed = 150;//130

volatile float kP;
volatile float kI;
volatile float kD;
volatile float LastError;
volatile float Error;
volatile float ALLError;
volatile float P;
volatile float I;
volatile float D;
volatile float PID;


void Motor_Init()
{ 
   for(int i=2;i<10;i++){pinMode(i, OUTPUT);}
   pwm.begin();
   pwm.setOscillatorFrequency(27000000);
   pwm.setPWMFreq(400); 
   Wire.setClock(400000);
}


void Motor(int ID,int SPEED){  //电机端口 1-4  速度可调  -255-0-255
    if(SPEED>0){pwm.setPin(ID*2, 0 );pwm.setPin(ID*2+1, (SPEED+1)*16-1);}
    else if(SPEED==0){pwm.setPin(ID*2, 4095 );pwm.setPin(ID*2+1, 4095);}
    else if(SPEED<0){pwm.setPin(ID*2, 1-(SPEED+1)*16);pwm.setPin(ID*2+1, 0);}
}


int SPEED_CTRL::motor_ctrl(int ID1,int SPEED1) {
  if(ID1==0 || ID1==3){
    SPEED1=-SPEED1;
  }
  Motor(ID1,SPEED1);
  return 1;
}

int SPEED_CTRL::start() {
// Serial.begin(9600);
  kP = 0.35;
  kI = 0;
  kD = 0;
  LastError = 0;
  Error = 0;
  ALLError = 0;
  Motor_Init();//初始化电机相关IO
  return 1;
}
int SPEED_CTRL::line() {
  int A1_D = analogRead(left_pin);
  int A2_D = analogRead(right_pin);
  Error = A2_D - A1_D;
  //Serial.println(Error);
  P = Error * kP;
  I = ALLError * kI;
  D = (Error - LastError) * kD;
  PID = (P + I) + D;
  int l_speed = speed-int(PID);
  int r_speed = speed+int(PID);
  if (l_speed > max_speed) {l_speed = max_speed;}else if (l_speed < 0) {l_speed = 0;}
  if (r_speed > max_speed) {r_speed = max_speed;}else if (r_speed < 0) {r_speed = 0;}
  /*Serial.print("l_speedV2::::");
  Serial.println(l_speed);
  Serial.print("r_speedV2::::");
  Serial.println(r_speed);*/
  Motor(0, -r_speed); // 设置左电机速度为200
  Motor(1, l_speed); // 设置左电机速度为200
  Motor(2, l_speed); // 设置左电机速度为200
  Motor(3, -r_speed); // 设置左电机速度为200
  return l_speed;
  }
  

