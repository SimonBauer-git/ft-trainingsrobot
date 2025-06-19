//dieser teil des codes ist modular auswechselbar
void programm() {
  automatik();
}

void automatik() {
  Serial.println("Automatik, s oder k zum beenden");
  delay(500);
  a2.setSpeed(255);
  a3.setSpeed(255);
  while (true) {
    moverobot(500, 850, 300);
    delay(2000);
    moverobot(990, 730, 300);
    moverobot(990, 730, 130);
    delay(2000);
    
  }
}
