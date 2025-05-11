//programm zur steuerung meines trainingsroboters mit poti

#include <AFMotor.h>
#include <Servo.h>

char SerialVal;
const int close = 180;
const int open = 90;

Servo tool;        //servo intitialisieren
AF_DCMotor a1(4);  //motor 1 = linker motor, letzte achse von unten gesehen
AF_DCMotor a2(2);  //motor 2 = rechter motor, untere achse des arms
AF_DCMotor a3(1);  //motor 3 (4) = drehachse unten

void setup() {
  Serial.begin(115200);  //Seriellle schnittstelle starten
  a1.setSpeed(255);
  a2.setSpeed(255);
  a3.setSpeed(255);
  tool.attach(9);
  tool.write(open);
}

void loop() {
  manuell();
}
