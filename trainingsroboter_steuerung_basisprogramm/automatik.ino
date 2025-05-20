//dieser teil des code ist modular auswechselbar
void programm() {
  automatik();
}

void manuell() {
  Serial.println("Manuelle Steuerung")
  delay(500);
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


void automatik() {
  Serial.println("Automatik, s oder k zum beenden");
  a2.setSpeed(255);
  a3.setSpeed(255);
  bool e1 = false;
  while (e1 == false) {

    moverobot(500, 850, 300);
    delay(2000);
    moverobot(990, 730, 130);
    delay(2000);

    if (Serial.available()) {
      SerialVal = Serial.read();
    }

    if (SerialVal == 's' || SerialVal == 'k') { e1 = true; }
  }
}
a1.run(RELEASE);
a2.run(RELEASE);
a3.run(RELEASE);
}
