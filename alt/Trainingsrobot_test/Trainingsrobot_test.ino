//programm zur steuerung meines trainingsroboters mittels serieller schnittstelle

#include <AFMotor.h>
#include <Servo.h>

char SerialVal;
const int close = 180;
const int open = 90;

Servo greifer;         //servo intitialisieren
AF_DCMotor achse1(1);  //motor 1 = linker motor, letzte achse von unten gesehen
AF_DCMotor achse2(2);  //motor 2 = rechter motor, untere achse des arms
AF_DCMotor achse3(4);  //motor 3 (4) = drehachse unten

void setup() {
  Serial.begin(115200);  //Seriellle schnittstelle starten
  achse1.setSpeed(127);
  achse2.setSpeed(127);
  achse3.setSpeed(255);
  greifer.attach(9);
}

void loop() {

  if (Serial.available())  //wenn daten über die serielle schnittstelle geschrieben werden
  {
    SerialVal = Serial.read();
  }
  switch (SerialVal)  //switch, die entscheidet je nachdem was für buchstaben gesendet werden welche aktionen durchgeführt werden sollen
  {
    case 'w':
      achse1.run(FORWARD);
      break;
    case 's':
      achse1.run(RELEASE);
      achse2.run(RELEASE);
      achse3.run(RELEASE);
      break;
    case 'x':
      achse1.run(BACKWARD);
      break;
    case 'a':
      achse3.run(FORWARD);
      break;
    case 'd':
      achse3.run(BACKWARD);
      break;
    case 'i':
      achse2.run(BACKWARD);
      break;
    case ',':
      achse2.run(FORWARD);
      break;
    case 'k':
      achse1.run(RELEASE);
      achse2.run(RELEASE);
      achse3.run(RELEASE);
      break;

      case 'q':
      greifer.write(open);
      break;
      case 'e':
      greifer.write(close);
      break;
  }
}
