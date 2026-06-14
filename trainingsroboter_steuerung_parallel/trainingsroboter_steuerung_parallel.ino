//programm zur steuerung meines trainingsroboters

#include <AFMotor.h>
#include <Servo.h>

char SerialVal;
const int close = 180;
const int open = 90;
const int home_23=14;

Servo tool;        //servo intitialisieren
AF_DCMotor a1(4);  //motor 1 = linker motor, letzte achse von unten gesehen
AF_DCMotor a2(2);  //motor 2 = rechter motor, untere achse des arms
AF_DCMotor a3(1);  //motor 3 (4) = drehachse unten

void setup() {
  Serial.begin(115200);  //Seriellle schnittstelle starten
  a1.setSpeed(255);
  a2.setSpeed(127);
  a3.setSpeed(127);
  tool.attach(9);
  tool.write(open);
  pinMode(14,INPUT_PULLUP);
  homing();
  
}

void loop() {
  moverobot(-5, 10, -5);
  delay(2000);
  moverobot(0, 0, 0);
  delay(2000);
}
