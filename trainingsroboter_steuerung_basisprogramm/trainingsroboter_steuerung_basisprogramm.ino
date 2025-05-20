//programm zur steuerung meines trainingsroboters mit poti

#include <AFMotor.h>
#include <Servo.h>

char SerialVal;
const int close = 180;
const int open = 90;
long unsigned int pm = 0;

bool reached_a1, reached_a2, reached_a3;
int demand_a1, demand_a2, demand_a3, pos_a1, pos_a2, pos_a3;

Servo tool;        //servo intitialisieren
AF_DCMotor a1(4);  //motor 1 = linker motor, letzte achse von unten gesehen
AF_DCMotor a2(2);  //motor 2 = rechter motor, untere achse des arms
AF_DCMotor a3(1);  //motor 3 (4) = drehachse unten

void setup() {
  Serial.begin(115200);
  a1.setSpeed(255);
  a2.setSpeed(255);
  a3.setSpeed(255);
  tool.attach(9);
  tool.write(open);
}

void loop() {
  programm();
}

//motorsteuerung basisbefehle


void homing() {  //homing sequence
  moverobot(990, 730, 130);
  delay(2000);
}



void moverobot(int demand_a1, int demand_a2, int demand_a3) {

  while (reached_a1 == false || reached_a2 == false || reached_a3 == false) {
    if (reached_a1 == false) {
      pos_a1 = analogRead(A7);

      if (demand_a1 > pos_a1 && reached_a1 == false) {
        a1.run(FORWARD);
      }

      if (demand_a1 < pos_a1 && reached_a1 == false) {
        a1.run(BACKWARD);
      }

      if (demand_a1 == pos_a1) {
        a1.run(RELEASE);
        reached_a1 = true;
      }
    }
    //____________________________________________________//

    if (reached_a2 == false) {
      pos_a2 = analogRead(A8);

      if (demand_a2 > pos_a2 && reached_a2 == false) {
        a2.run(FORWARD);
      }

      if (demand_a2 < pos_a2 && reached_a2 == false) {
        a2.run(BACKWARD);
      }

      if (demand_a2 == pos_a2) {
        a2.run(RELEASE);
        reached_a2 = true;
      }
    }
    //____________________________________________________//

    if (reached_a3 == false) {
      pos_a3 = analogRead(A9);

      if (demand_a3 > pos_a3 && reached_a3 == false) {
        a3.run(FORWARD);
      }

      if (demand_a3 < pos_a3 && reached_a3 == false) {
        a3.run(BACKWARD);
      }

      if (demand_a3 == pos_a3) {
        a3.run(RELEASE);
        reached_a3 = true;
      }
    }
    Serial.print("J1=");
    Serial.print(pos_a1);
    Serial.print(",");
    Serial.print(" J2=");
    Serial.print(pos_a2);
    Serial.print(",");
    Serial.print(" J3=");
    Serial.println(pos_a3);

    if (Serial.available()) {
      SerialVal = Serial.read();
    }

    if (SerialVal == 's' || SerialVal == 'k') {
      a1.run(RELEASE);
      a2.run(RELEASE);
      a3.run(RELEASE);
      manuell();
    }
  }
  //____________________________________________________//

  //flags resetten


  reached_a1 = false;
  reached_a2 = false;
  reached_a3 = false;
}
//-----------------------------------------------------------------------//
//manuelle steuerung mit wasdx bzw. ik,
void manuell() {
  Serial.println("Manuelle Steuerung");
  delay(500);
  a2.setSpeed(125);
  a3.setSpeed(80);
  while (true) {
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
      Serial.print("J1=");
      Serial.print(analogRead(A7));
      Serial.print(",");
      Serial.print(" J2=");
      Serial.print(analogRead(A8));
      Serial.print(",");
      Serial.print(" J3=");
      Serial.println(analogRead(A9));
      pm = millis();
    }
  }
}
