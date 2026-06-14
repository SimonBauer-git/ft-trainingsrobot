//programm zur steuerung meines trainingsroboters mit poti und smoother beschleunigung bzw. abbremsen

#include <AFMotor.h>
#include <Servo.h>

char SerialVal;
const int close = 5;
const int open = 40;

long unsigned int pm = 0;
long unsigned int pm2 = 0;
long unsigned int pm3 = 0;

bool reached_a1, reached_a2, reached_a3;
int demand_a1, demand_a2, demand_a3, pos_a1, pos_a2, pos_a3;
const int min_speed = 20;

Servo tool;        //servo intitialisieren
AF_DCMotor a1(4);  //motor 1 = drehachse unten
AF_DCMotor a2(2);  //motor 2 = rechter motor, untere achse des arms
AF_DCMotor a3(1);  //motor 3 = linker motor, letzte achse von unten gesehen

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
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


void homing() {  //homing sequences
  moverobot(990, 750, 290);
  delay(2000);
}



void moverobot(int demand_a1, int demand_a2, int demand_a3) {
  a1.setSpeed(255);
  a2.setSpeed(0);
  a3.setSpeed(0);
  float a1s = 0;
  float a2s = 0;
  float a3s = 0;
  while (reached_a1 == false || reached_a2 == false || reached_a3 == false) {
    if (reached_a1 == false) {

      if (demand_a1 == pos_a1) {
        a1.run(RELEASE);
        reached_a1 = true;
      }

      pos_a1 = analogRead(A7);

      if (demand_a1 > pos_a1 && reached_a1 == false) {
        a1s += 0.1;
        a1.run(FORWARD);
        //a1.setSpeed(constrain(demand_a1-pos_a1,150,255));
      }

      if (demand_a1 < pos_a1 && reached_a1 == false) {
        a1s += 0.1;
        a1.run(BACKWARD);
        //a1.setSpeed(constrain(demand_a1-pos_a1,150,255));         //slow down before you reach position (not used because the motors are not really that strong, they can rotate the robot at max speed but lower speeds make it unbearably slow, might need tuning)
      }
    }
    //____________________________________________________//

    if (reached_a2 == false) {

      if (demand_a2 == pos_a2) {
        a2.run(RELEASE);
        reached_a2 = true;
      }

      pos_a2 = analogRead(A8);

      if (demand_a2 > pos_a2 && reached_a2 == false) {

        if (millis() - pm2 > 200) {
          a2s += 0.05;
          pm2 = millis();
        }

        a2.run(FORWARD);
        a2.setSpeed(constrain((demand_a2 - pos_a2) * 10, 100, 255));
      }

      if (demand_a2 < pos_a2 && reached_a2 == false) {


        if (millis() - pm2 > 200) {  //accelerate linearly using hw timer
          a2s += 0.05;
          pm2 = millis();
        }

        a2.run(BACKWARD);
        a2.setSpeed(constrain(a2s * (pos_a2 - demand_a2) * 10, 100, 255));  //slow down before you reach position
      }
    }
    //____________________________________________________//

    if (reached_a3 == false) {

      if (demand_a3 == pos_a3) {
        a3.run(RELEASE);
        reached_a3 = true;
      }

      pos_a3 = analogRead(A8) - analogRead(A9);

      if (demand_a3 > pos_a3 && reached_a3 == false) {

        if (millis() - pm3 > 200) {
          a3s += 0.08;
          pm3 = millis();
        }

        a3.run(FORWARD);
        a3.setSpeed(constrain(a3s * (demand_a3 - pos_a3) * 3, 100, 255));
      }

      if (demand_a3 < pos_a3 && reached_a3 == false) {

        if (millis() - pm3 > 200) {
          a3s += 0.08;
          pm3 = millis();
        }

        a3.run(BACKWARD);
        a3.setSpeed(constrain(a3s * (pos_a3 - demand_a3) * 3, 100, 255));
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

    if (Serial1.available()) {
      SerialVal = Serial1.read();
    }

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
  a3.setSpeed(125);
  while (true) {
    if (Serial1.available()) {
      SerialVal = Serial1.read();
    }

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
      case 'u':
        tool.write(open);
        break;
      case 'z':
        tool.write(close);
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
