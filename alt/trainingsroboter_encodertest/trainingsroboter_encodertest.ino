#include <AFMotor.h>
const int home_1=51;
const int home_2=53;
const int home_3=52;
int homevalue_1;
int homevalue_2;
int homevalue_3;
const int encoder_3=20;
const int encoder_1=21;
int encodervalue_3=0;
int encodervalue_2=0;
int encodervalue_1=0;
int demand_1=0;
int demand_2=0;
int demand_3=0;
int rdy_1=1;
int rdy_2=0;
int rdy_3=0;
volatile int direction_3;
volatile int direction_1;

AF_DCMotor achse_3 (1);
AF_DCMotor achse_1 (2);
AF_Stepper achse_2(48,2);

void setup() {
pinMode(encoder_3,INPUT_PULLUP);
pinMode(encoder_1,INPUT_PULLUP);

  pinMode(home_1,INPUT_PULLUP);      //pins initialisieren
  pinMode(home_2,INPUT_PULLUP);
  pinMode(home_3,INPUT_PULLUP);

attachInterrupt(digitalPinToInterrupt(encoder_3),encodercount_3,RISING);
attachInterrupt(digitalPinToInterrupt(encoder_1),encodercount_1,RISING);

achse_1.setSpeed(255);
achse_2.setSpeed(70);
achse_3.setSpeed(255);
homing ();}

void loop() {
demand_3=-4;
demand_2=0;
demand_1=-4;
movepos ();
delay(3000);
demand_3=-20;
demand_2=0;
demand_1=0;
movepos();
delay(3000);
}

void encodercount_3 ()
{if(direction_3==1)
  {encodervalue_3++;}
 else
 {encodervalue_3--;}}

void encodercount_1 ()
{if(direction_1==1)
  {encodervalue_1++;}
 else
 {encodervalue_1--;}}


void movepos ()
{while (rdy_1==0||rdy_2==0||rdy_3==0)
{
if(rdy_3==0)
{if (demand_3 < encodervalue_3)
{achse_3.run(FORWARD);
direction_3=0;}

if (demand_3 > encodervalue_3)
{achse_3.run(BACKWARD);
direction_3=1;}

if(demand_3 ==encodervalue_3)
{achse_3.run(RELEASE);
rdy_3=1;}}

if (demand_2 < encodervalue_2)
{achse_2.step(1,FORWARD,DOUBLE);
encodervalue_2--;}
Serial.println(encodervalue_2);
if (demand_2 > encodervalue_2)
{achse_2.step(1,BACKWARD,DOUBLE);
encodervalue_2++;}

if (demand_2 ==encodervalue_2)
{achse_2.release();
 rdy_2=1;}

if(rdy_1==0)
{if (demand_1 < encodervalue_1)
{achse_1.run(FORWARD);
direction_1=0;}

if (demand_1 > encodervalue_1)
{achse_1.run(BACKWARD);
direction_1=1;}

if(demand_1 ==encodervalue_1)
{achse_1.run(RELEASE);
rdy_1=1;}}

}
rdy_1=0;
rdy_2=0;
rdy_3=0;}

void homing()
  {

    homevalue_1=digitalRead(home_1);                //homepositionen bestimmen bzw.anfahren (fahrt gegen endschalter auf allen achsen)
  homevalue_2=digitalRead(home_2);
  homevalue_3=digitalRead(home_3);
  while(homevalue_3==0)
  {homevalue_3=digitalRead(home_3);
    achse_3.run(BACKWARD);}
    achse_3.run(RELEASE);
    
  while(homevalue_2==0)
  {homevalue_2=digitalRead(home_2);
  achse_2.step(1,BACKWARD,DOUBLE);
  achse_2.release();}

  while(homevalue_1==0)
  {homevalue_1=digitalRead(home_1);
  achse_1.run(BACKWARD);}
  achse_1.run(RELEASE);

  encodervalue_1=0;
  encodervalue_2=0;
  encodervalue_3=0;
}
