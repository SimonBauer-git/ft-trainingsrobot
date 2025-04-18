bool direction_a1, direction_a2, direction_a3, reached_a1, reached_a2, reached_a3, flag_1, flag_2, flag_3;
int demand_a1, demand_a2, demand_a3, pos_a1, pos_a2, pos_a3;

void A_1() {
  if (analogRead(A7)>750 && flag_1 == false) {
    if (direction_a1 == false) { pos_a1--; }
    if (direction_a1 == true) { pos_a1++; }
    flag_1 = true;
    delay(40);                                         //"debounce" delay, um zu verhindern das der encoder zu viele schritte erkennt
  }
  else {
    flag_1 = false; }
}
//__________________________________//

void A_2() {
  if (analogRead(A8)>150 && flag_2 == false) {
    if (direction_a2 == false) { pos_a2--; }
    if (direction_a2 == true) { pos_a2++; }
    flag_2 = true;
    delay(40);                                         //"debounce" delay, um zu verhindern das der encoder zu viele schritte erkennt
  }
  else {
    flag_2 = false; }
}
//_________________________________//


void A_3() {
  if (analogRead(A9)>400 && flag_3 == false) {
    if (direction_a3 == false) { pos_a3--; }
    if (direction_a3 == true) { pos_a3++; }
    flag_3 = true;
    delay(40);                                         //"debounce" delay, um zu verhindern das der encoder zu viele schritte erkennt
  }
  else {
    flag_3 = false; }
}
//_________________________________//

void homing() {  //homing sequence
//achse 2
a2.run(FORWARD);
delay(1000);
while(digitalRead(14)==1)
{a2.run(BACKWARD);}
a2.run(RELEASE);
delay(100);
while(digitalRead(14)==0){
a2.run(FORWARD);
delay(20);}
a2.run(RELEASE);
//achse 3
a3.run(BACKWARD);
delay(1000);
while(digitalRead(14)==1)
{a3.run(FORWARD);}
a3.run(RELEASE);
delay(100);
while(digitalRead(14)==0){
a3.run(BACKWARD);
delay(20);}
a3.run(RELEASE);
//achse 1
while(digitalRead(14)==1)
{a1.run(FORWARD);}
a1.run(RELEASE);
delay(100);
while(digitalRead(14)==0){
a1.run(BACKWARD);
delay(20);}
a1.run(RELEASE);
}



void moverobot(int demand_a1, int demand_a2, int demand_a3) {
while(reached_a1 == false || reached_a2 == false || reached_a3 == false){
  if (reached_a1 == false) {
    A_1();

    if (demand_a1 > pos_a1 && reached_a1 == false) {
      direction_a1 = true;
      a1.run(FORWARD);
    }

    if (demand_a1 < pos_a1 && reached_a1 == false) {
      direction_a1 = false;
      a1.run(BACKWARD);
    }

    if (demand_a1 == pos_a1) {
      a1.run(RELEASE);
      reached_a1 = true;
    }}
//____________________________________________________//

  if (reached_a2 == false) {
    A_2();

    if (demand_a2 > pos_a2 && reached_a2 == false) {
      direction_a2 = true;
      a2.run(FORWARD);
    }

    if (demand_a2 < pos_a2 && reached_a2 == false) {
      direction_a2 = false;
      a2.run(BACKWARD);
    }

    if (demand_a2 == pos_a2) {
      a2.run(RELEASE);
      reached_a2 = true;
    }
    }
//____________________________________________________//

  if (reached_a3 == false) {
    A_3();

    if (demand_a3 > pos_a3 && reached_a3 == false) {
      direction_a3 = true;
      a3.run(FORWARD);
    }

    if (demand_a3 < pos_a3 && reached_a3 == false) {
      direction_a3 = false;
      a3.run(BACKWARD);
    }

    if (demand_a3 == pos_a3) {
      a3.run(RELEASE);
      reached_a3 = true;
    }
    }
}
//____________________________________________________//
  
  //flags resetten
  

  reached_a1 = false;
  reached_a2 = false;
  reached_a3 = false;
}
