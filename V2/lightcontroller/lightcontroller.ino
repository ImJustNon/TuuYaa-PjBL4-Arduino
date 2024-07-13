const int LED_A1[] = {13, 6};
const int LED_A2[] = {12, 6};
const int LED_A3[] = {11, 6};
const int LED_A4[] = {10, 6};
const int LED_A5[] = {9, 6};
const int LED_A6[] = {8, 6};
const int LED_A7[] = {7, 6};
const int LED_B1[] = {13, 5};
const int LED_B2[] = {12, 5};
const int LED_B3[] = {11, 5};
const int LED_B4[] = {10, 5};
const int LED_B5[] = {9, 5};
const int LED_B6[] = {8, 5};
const int LED_B7[] = {7, 5};
const int LED_C1[] = {13, 4};
const int LED_C2[] = {12, 4};
const int LED_C3[] = {11, 4};
const int LED_C4[] = {10, 4};
const int LED_C5[] = {9, 4};
const int LED_C6[] = {8, 4};
const int LED_C7[] = {7, 4};
const int LED_D1[] = {13, 3};
const int LED_D2[] = {12, 3};
const int LED_D3[] = {11, 3};
const int LED_D4[] = {10, 3};
const int LED_D5[] = {9, 3};
const int LED_D6[] = {8, 3};
const int LED_D7[] = {7, 3};


void setup(){
  Serial.begin(115200);
  SetPinMode_A();
  SetPinMode_B();
  SetPinMode_C();
  SetPinMode_D();
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
}

void loop(){
  SetLED("A1", 1);
  SetLED("A2", 1);
  SetLED("A3", 1);
  SetLED("A4", 1);
  SetLED("B4", 1);
  SetLED("D7", 1);
}

void SetLED(String col, int state){
  int positive;
  int negative;
  if(state == 1){
    positive = 1;
    negative = 0;
  }
  else {
    positive = 0;
    negative = 0;
  }

  if(col == "A1"){
    digitalWrite(LED_A1[0], positive);
    digitalWrite(LED_A1[1], negative);
  }
  else if(col == "A2"){
    digitalWrite(LED_A2[0], positive);
    digitalWrite(LED_A2[1], negative);
  }
  else if(col == "A3"){
    digitalWrite(LED_A3[0], positive);
    digitalWrite(LED_A3[1], negative);
  }
  else if(col == "A4"){
    digitalWrite(LED_A4[0], positive);
    digitalWrite(LED_A4[1], negative);
  }
  else if(col == "A5"){
    digitalWrite(LED_A5[0], positive);
    digitalWrite(LED_A5[1], negative);
  }
  else if(col == "A6"){
    digitalWrite(LED_A6[0], positive);
    digitalWrite(LED_A6[1], negative);
  }
  else if(col == "A7"){
    digitalWrite(LED_A7[0], positive);
    digitalWrite(LED_A7[1], negative);
  }
  else if(col == "B1"){
    digitalWrite(LED_B1[0], positive);
    digitalWrite(LED_B1[1], negative);
  }
  else if(col == "B2"){
    digitalWrite(LED_B2[0], positive);
    digitalWrite(LED_B2[1], negative);
  }
  else if(col == "B3"){
    digitalWrite(LED_B3[0], positive);
    digitalWrite(LED_B3[1], negative);
  }
  else if(col == "B4"){
    digitalWrite(LED_B4[0], positive);
    digitalWrite(LED_B4[1], negative);
  }
  else if(col == "B5"){
    digitalWrite(LED_B5[0], positive);
    digitalWrite(LED_B5[1], negative);
  }
  else if(col == "B6"){
    digitalWrite(LED_B6[0], positive);
    digitalWrite(LED_B6[1], negative);
  }
  else if(col == "B7"){
    digitalWrite(LED_B7[0], positive);
    digitalWrite(LED_B7[1], negative);
  }
  else if(col == "C1"){
    digitalWrite(LED_C1[0], positive);
    digitalWrite(LED_C1[1], negative);
  }
  else if(col == "C2"){
    digitalWrite(LED_C2[0], positive);
    digitalWrite(LED_C2[1], negative);
  }
  else if(col == "C3"){
    digitalWrite(LED_C3[0], positive);
    digitalWrite(LED_C3[1], negative);
  }
  else if(col == "C4"){
    digitalWrite(LED_C4[0], positive);
    digitalWrite(LED_C4[1], negative);
  }
  else if(col == "C5"){
    digitalWrite(LED_C5[0], positive);
    digitalWrite(LED_C5[1], negative);
  }
  else if(col == "C6"){
    digitalWrite(LED_C6[0], positive);
    digitalWrite(LED_C6[1], negative);
  }
  else if(col == "C7"){
    digitalWrite(LED_C7[0], positive);
    digitalWrite(LED_C7[1], negative);
  }
  else if(col == "D1"){
    digitalWrite(LED_D1[0], positive);
    digitalWrite(LED_D1[1], negative);
  }
  else if(col == "D2"){
    digitalWrite(LED_D2[0], positive);
    digitalWrite(LED_D2[1], negative);
  }
  else if(col == "D3"){
    digitalWrite(LED_D3[0], positive);
    digitalWrite(LED_D3[1], negative);
  }
  else if(col == "D4"){
    digitalWrite(LED_D4[0], positive);
    digitalWrite(LED_D4[1], negative);
  }
  else if(col == "D5"){
    digitalWrite(LED_D5[0], positive);
    digitalWrite(LED_D5[1], negative);
  }
  else if(col == "D6"){
    digitalWrite(LED_D6[0], positive);
    digitalWrite(LED_D6[1], negative);
  }
  else if(col == "D7"){
    digitalWrite(LED_D7[0], positive);
    digitalWrite(LED_D7[1], negative);
  }
}

