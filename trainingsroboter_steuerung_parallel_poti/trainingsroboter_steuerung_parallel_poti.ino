bool reached_a1, reached_a2, reached_a3;
int demand_a1, demand_a2, demand_a3, pos_a1, pos_a2, pos_a3;

void homing() {  //homing sequence
moverobot(950,730,800);
delay(2000);
}



void moverobot(int demand_a1, int demand_a2, int demand_a3) {
  demand_a1=constrain(demand_a1, 580, 1000);
  demand_a2=constrain(demand_a2, 730, 1000);
  demand_a3=constrain(demand_a3, 800, 1000);

while(reached_a1 == false || reached_a2 == false || reached_a3 == false){
  if (reached_a1 == false) {
    pos_a1=analogRead(A7);

    if (demand_a1 > pos_a1 && reached_a1 == false) {
      a1.run(FORWARD);
    }

    if (demand_a1 < pos_a1 && reached_a1 == false) {
      a1.run(BACKWARD);
    }

    if (demand_a1 == pos_a1) {
      a1.run(RELEASE);
      reached_a1 = true;
    }}
//____________________________________________________//

  if (reached_a2 == false) {
    pos_a2=analogRead(A8);

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
    pos_a3=analogRead(A9);

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
Serial.println(pos_a3);}
//____________________________________________________//
  
  //flags resetten
  

  reached_a1 = false;
  reached_a2 = false;
  reached_a3 = false;
}
