#include <AFMotor.h>

const int encoder3=20;
const int encoder1=21;
int encodervalue3=0;
int encodervalue2=0;
int encodervalue1=0;
int demand_1=0;
int demand_2=0;
int demand_3=0;
int speed3=255;
int rdy_1=1;
int rdy_2=0;
int rdy_3=0;
volatile int direction3;
AF_DCMotor achse3 (1);
AF_DCMotor achse1 (2);
AF_Stepper achse2(48,2);
void setup() {
pinMode(encoder3,INPUT_PULLUP);
pinMode(encoder1,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(encoder3),encodercount1,RISING);
stepper.setSpeed(70);
Serial.begin(9600);}
void loop() {
demand_3=40;
demand_2=50;
movepos ();
demand_3=-20;
demand_2=-100;
movepos();
Serial.print(encodervalue3);
}
void encodercount1 ()
{if(direction3==1)
  {encodervalue3++;}
 else
 {encodervalue3--;}}

void movepos ()
{while (rdy_2==0||rdy_3==0)
{
if(rdy_3==0)
{if (demand_3 < encodervalue3)
{motor.setSpeed(speed3);
  motor.run(FORWARD);
direction3=0;}

if (demand_3 > encodervalue3)
{motor.setSpeed(speed3);
  motor.run(BACKWARD);
direction3=1;}

if(demand_3 ==encodervalue3)
{motor.run(RELEASE);
rdy_3=1;}}

if (demand_2 < encodervalue2)
{stepper.step(1,FORWARD,DOUBLE);
encodervalue2--;}
Serial.println(encodervalue2);
if (demand_2 > encodervalue2)
{stepper.step(1,BACKWARD,DOUBLE);
encodervalue2++;}

if (demand_2 ==encodervalue2)
{rdy_2=1;}
}
rdy_2=0;
rdy_3=0;}
