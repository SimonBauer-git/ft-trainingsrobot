//programm zur steuerung meines trainingsroboters mit poti

#include <AFMotor.h>
#include <Servo.h>

char SerialVal;
const int close = 180;
const int open = 90;
long unsigned int pm = 0;

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

void automatik() {
  a2.setSpeed(255);
  a3.setSpeed(255);
  bool e1 = false;
  while (e1 == false) {

moverobot(500,850,300);
delay(2000);
moverobot(990,730,130);
delay(2000);

    if (Serial.available()) {
      SerialVal = Serial.read();
    }

    if (SerialVal == 's' || SerialVal == 'k') { e1 = true; }
    if (millis() - pm > 200) {
      Serial.print("Automatikmodus, ");
      Serial.print(analogRead(A7));
      Serial.print(",");
      Serial.print(analogRead(A8));
      Serial.print(",");
      Serial.println(analogRead(A9));
      pm = millis();
    }
  }
  a1.run(RELEASE);
  a2.run(RELEASE);
  a3.run(RELEASE);
}

void manuell() {
  a2.setSpeed(125);
  a3.setSpeed(80);
  if (Serial.available()) {
    SerialVal = Serial.read();
  }

  switch (SerialVal) {
    case 'w':
      a2.run(FORWARD);
      break;
    case 's':
      a1.run(RELEASE);
      a2.run(RELEASE);
      a3.run(RELEASE);
      break;
    case 'k':
      a1.run(RELEASE);
      a2.run(RELEASE);
      a3.run(RELEASE);
      break;
    case 'x':
      a2.run(BACKWARD);
      break;
    case 'a':
      a1.run(FORWARD);
      break;
    case 'd':
      a1.run(BACKWARD);
      break;
    case 'i':
      a3.run(BACKWARD);
      break;
    case ',':
      a3.run(FORWARD);
      break;
    case 'h':
      homing();
      break;
    case 'p':
      automatik();
      break;
  }
  if (millis() - pm > 200) {
    Serial.print(analogRead(A7));
    Serial.print(",");
    Serial.print(analogRead(A8));
    Serial.print(",");
    Serial.println(analogRead(A9));
    pm = millis();
  }
}


