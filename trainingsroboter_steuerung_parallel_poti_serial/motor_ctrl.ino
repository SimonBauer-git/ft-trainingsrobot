bool reached_a1, reached_a2, reached_a3;
int demand_a1, demand_a2, demand_a3, pos_a1, pos_a2, pos_a3;
long unsigned int pm = 0;

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
    Serial.print(pos_a1);
    Serial.print(",");
    Serial.print(pos_a2);
    Serial.print(",");
    Serial.println(pos_a3);
  }
  //____________________________________________________//

  //flags resetten


  reached_a1 = false;
  reached_a2 = false;
  reached_a3 = false;
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
