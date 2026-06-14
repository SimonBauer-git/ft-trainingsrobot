/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1_bc.h>
#include <AFMotor.h>
#define PIN_INPUT 9
#define PIN_OUTPUT 3

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=10, Ki=0.02, Kd=0.1;
double uebergabe;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
AF_DCMotor a3(1);  //motor 3 (4) = drehachse unten
void setup()
{Serial.begin(115200);
  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);


  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255.0, 255.0);
}



void moverobot (double uebergabe){
  Setpoint= uebergabe;
 Input = analogRead(A8)-analogRead(PIN_INPUT);
  myPID.Compute();
  Serial.print(Input);
  Serial.print(",");
  Serial.println(Output);
  if(Output < 0)
  {a3.setSpeed((Output)*-1);
  a3.run(BACKWARD);}
  
   if(Output > 0)
  {a3.setSpeed(Output);
  a3.run(FORWARD);}}

void loop()
{ moverobot(250);
}