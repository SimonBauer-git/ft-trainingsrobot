//programm zur steuerung meines trainingsroboters mit poti

#include <AFMotor.h>
#include <Servo.h>
#include <PID_v1_bc.h>
char SerialVal;
const int close = 180;
const int open = 90;
long unsigned int pm = 0;
double speed_a1, speed_a2, speed_a3;

bool reached_a1, reached_a2, reached_a3;
double uebergabe_a1, uebergabe_a2, uebergabe_a3, demand_a1, demand_a2, demand_a3, pos_a1, pos_a2, pos_a3;

PID m2(&pos_a2, &speed_a2, &demand_a2, 10.0, 20.0, 0.01, DIRECT);
PID m3(&pos_a3, &speed_a3, &demand_a3, 5.0, 10, 0.01, DIRECT);

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

  m2.SetMode(AUTOMATIC);
  m3.SetMode(AUTOMATIC);

  m2.SetOutputLimits(-255.0, 255.0);
  m3.SetOutputLimits(-255.0, 255.0);
}

void loop() {
  programm();
}

//motorsteuerung basisbefehle


void homing() {  //homing sequences
  moverobot(990, 730, 260);
  delay(2000);
}



void moverobot(double uebergabe_a1, double uebergabe_a2, double uebergabe_a3) {

  demand_a1 = uebergabe_a1;  //fix for weird behavoir when directly using demand in the pid controller
  demand_a2 = uebergabe_a2;
  demand_a3 = uebergabe_a3;

  while (reached_a1 == false || reached_a2 == false || reached_a3 == false) {
    //_____________________achse 1________________//
    if (reached_a1 == false) {

      if (demand_a1 == pos_a1) {
        a1.run(RELEASE);
        reached_a1 = true;
      }

      pos_a1 = analogRead(A7);

      if (demand_a1 > pos_a1 && reached_a1 == false) {
        a1.run(FORWARD);
      }

      if (demand_a1 < pos_a1 && reached_a1 == false) {
        a1.run(BACKWARD);
      }
    }

    //_____________________achse 2________________//


    if (demand_a2 == pos_a2) {
      reached_a2 = true;
      a2.run(RELEASE);
    }
    if (reached_a2 == false) {

      pos_a2 = analogRead(A8);
      m2.Compute();
      if (speed_a2 < 0) {
        a2.setSpeed((speed_a2) * -1);
        a2.run(BACKWARD);
      }

      if (speed_a2 > 0) {
        a2.setSpeed(speed_a2);
        a2.run(FORWARD);
      }
    }

    //_____________________achse 3________________//


    if (demand_a3 == pos_a3) 
    { reached_a3 = true; }
    pos_a3 = analogRead(A8) - analogRead(A9);
    m3.Compute();
    if (speed_a3 < 0) {
      a3.setSpeed((speed_a3) * -1);
      a3.run(BACKWARD);
    }

    if (speed_a3 > 0) {
      a3.setSpeed(speed_a3);
      a3.run(FORWARD);
    }

    if (speed_a3 == 0) {
      a3.run(RELEASE);
      reached_a3 = true;
    }


    //____________________________________________________//
    Serial.print("J1=");
    Serial.print(pos_a1);
    Serial.print(",");
    Serial.print(" J2=");
    Serial.print(pos_a2);
    Serial.print(",");
    Serial.print(" J3=");
    Serial.print(pos_a3);
    Serial.print(" flags=");
    Serial.print(reached_a1);
    Serial.print(reached_a2);
    Serial.println(reached_a3);

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
  a3.run(RELEASE);
}
//-----------------------------------------------------------------------//
//manuelle steuerung mit wasdx bzw. ik,
void manuell() {
  Serial.println("Manuelle Steuerung");
  delay(500);
  a2.setSpeed(125);
  a3.setSpeed(125);
  a1.setSpeed(255);
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
      Serial.println(analogRead(A8) - analogRead(A9));
      pm = millis();
    }
  }
}
