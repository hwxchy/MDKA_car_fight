#include <Arduino.h>
#include <MsTimer2.h>
#include <SPEED_CTRL.h>
#include "RL_PCF8574T.h"
#include <Servo.h>
int flag_auto = 0;

Servo servo;
int servoPin = 2;
PCF8574 pcf8574_E(0x20);//2.4G接收管脚  I2C地址为0X20

#define Robot_stop  0
#define Robot_go_forward  2
#define Robot_go_backward  1
#define Robot_go_leftward  4
#define Robot_go_rightward  3
#define Robot_go_cw  6
#define Robot_go_ccw  5
#define servo_right  8
#define servo_left  7
int servo_COUNT = 90;



int speed_run = 80; 
SPEED_CTRL speedCtrl;
volatile int time_100ms;

void msTimer2_func() {
  time_100ms = time_100ms + 1;
  //Serial.println(time_100ms);
  
}

void Robot_run(int go,int speed=0){
  
  switch(go){

   case 0: speedCtrl.motor_ctrl(0,speed);speedCtrl.motor_ctrl(1,speed);speedCtrl.motor_ctrl(2,speed);speedCtrl.motor_ctrl(3,speed);break;
   case 1: speedCtrl.motor_ctrl(0,speed);speedCtrl.motor_ctrl(1,speed);speedCtrl.motor_ctrl(2,speed);speedCtrl.motor_ctrl(3,speed);break;
   case 2: speedCtrl.motor_ctrl(0,-speed);speedCtrl.motor_ctrl(1,-speed);speedCtrl.motor_ctrl(2,-speed);speedCtrl.motor_ctrl(3,-speed);break;
   case 4: speedCtrl.motor_ctrl(0,-speed);speedCtrl.motor_ctrl(1,speed);speedCtrl.motor_ctrl(2,speed);speedCtrl.motor_ctrl(3,-speed);break;
   case 3: speedCtrl.motor_ctrl(0,speed);speedCtrl.motor_ctrl(1,-speed);speedCtrl.motor_ctrl(2,-speed);speedCtrl.motor_ctrl(3,speed);break;
   case 6: speedCtrl.motor_ctrl(0,-speed);speedCtrl.motor_ctrl(1,speed);speedCtrl.motor_ctrl(2,-speed);speedCtrl.motor_ctrl(3,speed);break; 
   case 5: speedCtrl.motor_ctrl(0,speed);speedCtrl.motor_ctrl(1,-speed);speedCtrl.motor_ctrl(2,speed);speedCtrl.motor_ctrl(3,-speed);break;
   case 7: if (servo_COUNT < 177){servo_COUNT = servo_COUNT + 3;};servo.write(servo_COUNT);Serial.println(servo_COUNT);delay(30);break;
   case 8: if (servo_COUNT >3){servo_COUNT = servo_COUNT - 3;};servo.write(servo_COUNT);Serial.println(servo_COUNT);delay(30);break;
    
    }
  }
void setup() {
  Serial.begin(9600);
  time_100ms = 0;
  speedCtrl.start();
  MsTimer2::set(100, msTimer2_func);
  MsTimer2::start();
  servo.attach(servoPin);
  servo.write(servo_COUNT);
  pinMode(13, OUTPUT);//设置输出
  pcf8574_E.begin();
  for(int i=0;i<8;i++)
  pcf8574_E.pinMode(i, INPUT);
  Robot_run(Robot_stop,0);
  
}

void run_t(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, 0); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, 0); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, 0); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, 0); // 设置左电机速度为200
  if (time_ != 0){
  delay(time_);
  }
}

void run_q(int speed_=speed_run,int time_=500){ 
  time_100ms = 0; 
  do{
    speedCtrl.line();
  }while(time_100ms <= time_/100);
  //  if (time_ != 0){
  //  delay(time_);
  //  run_t();
  }

void run_h(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, -speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_z(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, speed_); // 设置左电机速度为200
  if (time_ != 0){
    delay(time_);
    run_t();
  }
}
 
void run_y(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, -speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_y_p(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, -speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}

void run_z_p(int speed_=speed_run,int time_=0){
  speedCtrl.motor_ctrl(0, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, -speed_); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, speed_); // 设置左电机速度为200
    if (time_ != 0){
    delay(time_);
    run_t();
  }
}



void turn_right(int rq = 300){
  while (analogRead(A1)<500){
  run_y();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_y();
  }
  run_q();
}

void turn_left(int rq = 300){
  while (analogRead(A2)<500){
  run_z();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_z();
  }
  run_q();
}

void turn_around(int rq = 300){
 while (analogRead(A2)<500){
  run_y();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_y();
  }
  run_y(70,300);
   while (analogRead(A2)<500){
  run_y();
  }
  while (analogRead(A1)-analogRead(A2)>150){
    run_y();
  }
  run_q();
}

void auto_run(){
    do{
  run_z_p();
  }while(analogRead(A2) <= 400);
  
  do{
  speedCtrl.line();
  }while(analogRead(A3) <= 400);
  turn_left();

  do{
  speedCtrl.line();
  }while(analogRead(A3) <= 400);
  turn_left();
  
  do{
  speedCtrl.line();
  }while(analogRead(A3) <= 400);

  speedCtrl.motor_ctrl(0, 80); // 设置左电机速度为200
  speedCtrl.motor_ctrl(1, 80); // 设置左电机速度为200
  speedCtrl.motor_ctrl(2, 80); // 设置左电机速度为200
  speedCtrl.motor_ctrl(3, 80); // 设置左电机速度为200
  delay(500);
  run_t(0,100);
  flag_auto = 1;

}




void Romote_ctrl() {
     PCF8574::DigitalInput di = pcf8574_E.digitalReadAll();//获取全部端口数值
     if(di.p0){digitalWrite(13, HIGH);Robot_run(Robot_go_forward,100);} //前进
     else if(di.p1){digitalWrite(13, HIGH); Robot_run(Robot_go_backward,100);} //后退
     else if(di.p2){digitalWrite(13, HIGH); Robot_run(Robot_go_leftward,100);} //左平移
     else if(di.p3){digitalWrite(13, HIGH); Robot_run(Robot_go_rightward,100);} //右平移
     else if(di.p6){digitalWrite(13, HIGH); Robot_run(Robot_go_ccw,100);} //顺时针旋转
     else if(di.p7){digitalWrite(13, HIGH); Robot_run(Robot_go_cw,100);} //逆时针旋转
     else if(di.p4){digitalWrite(13, HIGH); Robot_run(servo_left,10);} //顺时针旋转
     else if(di.p5){digitalWrite(13, HIGH); Robot_run(servo_right,10);} //逆时针旋转
     else{digitalWrite(13, LOW); Robot_run(Robot_stop);}
}
void loop(){
  // delay(500);
  // Serial.println(analogRead(A3));
  // Serial.println(analogRead(A2));
  // Serial.println(analogRead(A1));
  
  auto_run();
  while(flag_auto == 1){
  Romote_ctrl();
  }
}