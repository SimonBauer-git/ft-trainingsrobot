//programm zur steuerung meines trainingsroboters mittels serieller schnittstelle
#include <AFMotor.h>
#include <Servo.h>

char bluetoothVal;
const int zu =2;        //variablen initialisieren
const int auf =43;
const int home1=51;
const int home2=53;
const int home3=52;
const int encoder1=21;    //encoderpins zuweisen allerdings nur zwei, da die achse2 einen open-loop schrittmotor besitzt und ein encoder hier somit überflüssig ist
const int encoder3=20;
int homevalue1;
int homevalue2;
int homevalue3;
float encodervalue1=0;
float encodervalue2=0;
float encodervalue3=0;
boolean direction1;
boolean direction3;

Servo greifer;                //servo intitialisieren
AF_Stepper achse2 (48,2);     //motoren definieren
AF_DCMotor achse3 (1);
AF_DCMotor achse1 (2);

void setup(){
  Serial.begin(115200);               //Seriellle schnittstelle starten
  Serial.print("initialisiere");    //UI-Zeug
  delay(100);
  Serial.print(".");
  delay(100);
  Serial.print(".");
  delay(100);
  Serial.print(".");
  delay(100);
  Serial.print(".");
  delay(100);
  Serial.print(".");
  delay(100);
  Serial.print(".");
  delay(100);
  Serial.println(".");
  delay(100);
  pinMode(home1,INPUT_PULLUP);      //pins initialisieren
  pinMode(home2,INPUT_PULLUP);
  pinMode(home3,INPUT_PULLUP);
  pinMode(encoder1,INPUT_PULLUP);
  pinMode(encoder3,INPUT_PULLUP);
  greifer.attach(9);                //servopin definieren
  greifer.write(auf);               //servo öffnen
 attachInterrupt(digitalPinToInterrupt(encoder1),encodercount1,RISING);
 attachInterrupt(digitalPinToInterrupt(encoder3),encodercount3,RISING);
 achse1.setSpeed(255);              //motorgeschwindigkeiten einstellen
 achse2.setSpeed(70);
 achse3.setSpeed(255);
 Serial.println("initialisiert");   //UI-Zeug
}
 
void loop(){
 Serial.print(encodervalue1);
  Serial.print(",");
  Serial.print(encodervalue2);
  Serial.print(","); 
  Serial.println(encodervalue3);
  if(Serial.available())          //wenn daten über die serielle schnittstelle geschrieben werden
    {bluetoothVal=Serial.read();
  }
  switch (bluetoothVal)           //switch, die entscheidet je nachdem was für buchstaben gesendet werden welche aktionen durchgeführt werden sollen
  {case 'w':
  while(bluetoothVal!='s'&&bluetoothVal!='k')
  {
  achse2.step(1,FORWARD,DOUBLE);
  Serial.print(encodervalue1);
  Serial.print(",");
  Serial.print(encodervalue2);
  Serial.print(","); 
  Serial.println(encodervalue3);
  encodervalue2=(encodervalue2+0.0681818181818182);//schrittmotorzeugs
  if (Serial.available())
  {bluetoothVal=Serial.read();}}
  achse2.release();
  break;
  case 's':
  achse1.run(RELEASE);
  achse3.run(RELEASE);
  break;
  case 'k':
  achse1.run(RELEASE);
  achse3.run(RELEASE);
  break;
  case'x':
  while(bluetoothVal!='s'&&bluetoothVal!='k')
  {achse2.step(1,BACKWARD,DOUBLE);
  Serial.println(encodervalue2);
  encodervalue2=(encodervalue2-0.0681818181818182);
  if (Serial.available())       //schrittmotorzeug bloß in die andere richtung
  {bluetoothVal=Serial.read();}
  }
  achse2.release();
  break;
  
  case'a':
  achse1.run(FORWARD);
  direction1=true;
  break;
  case'd':
  achse1.run(BACKWARD);
  direction1=false;
  break;
  case'i':
  achse3.run(BACKWARD);
  direction3=false;
  break;
  case',':
  achse3.run(FORWARD);
  direction3=true;
  break;
  case 'v':
  greifer.write(zu);      //greifersteuerung
  break;
  case 'b':
  greifer.write(auf);
  break;
  case 'h':
  homing();
  break;
  }}

  void homing()
  {Serial.println("homepositionen anfahren...");
    greifer.write(45);
    homevalue1=digitalRead(home1);                //homepositionen bestimmen bzw.anfahren (fahrt gegen endschalter auf allen achsen)
  homevalue2=digitalRead(home2);
  homevalue3=digitalRead(home3);
  while(homevalue3==0)
  {homevalue3=digitalRead(home3);
    achse3.run(BACKWARD);}
    achse3.run(RELEASE);
    Serial.println("achse3 homeposition angefahren");
  while(homevalue2==0)
  {homevalue2=digitalRead(home2);
  achse2.step(1,BACKWARD,DOUBLE);
  achse2.release();}
  Serial.println("achse2 homeposition angefahren");
  while(homevalue1==0)
  {homevalue1=digitalRead(home1);
  achse1.run(BACKWARD);}
  achse1.run(RELEASE);
  Serial.println("achse1 homeposition angefahren");
  encodervalue1=0;
  encodervalue2=-15;
  encodervalue3=-15;
  Serial.println("alle homepositionen angefahren!");}

  void encodercount1()
  {if(direction1==true)
  {encodervalue1=(encodervalue1+3.75);}
  else
  {encodervalue1=(encodervalue1-3,75);}
 // encodervalue1=map(encodervalue1,0,1023,0,360);
 } //encoderwerte auf werte von 0-360° umschreiben

   void encodercount3()
  {if(direction3==true)
  {encodervalue3=encodervalue3+0,5172413793103448;}
  else
  {encodervalue3=encodervalue3-0,5172413793103448;}
  }
