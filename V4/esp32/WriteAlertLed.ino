void WriteAlertLed(String value, int status){
  if(value == "A1"){
    digitalWrite(relay_A, status);
    digitalWrite(relay_1, status);
  }
  else if(value == "A2"){
    digitalWrite(relay_A, status);
    digitalWrite(relay_2, status);
  }
  else if(value == "A3"){
    digitalWrite(relay_A, status);
    digitalWrite(relay_3, status);
  }
  else if(value == "A4"){
    digitalWrite(relay_A, status);
    digitalWrite(relay_4, status);
  }
  else if(value == "A5"){
    digitalWrite(relay_A, status);
    digitalWrite(relay_5, status);
  }
  else if(value == "A6"){
    digitalWrite(relay_A, status);
    digitalWrite(relay_6, status);
  }
  else if(value == "A7"){
    digitalWrite(relay_A, status);
    digitalWrite(relay_7, status);
  }
  else if(value == "B1"){
    digitalWrite(relay_B, status);
    digitalWrite(relay_1, status);
  }
  else if(value == "B2"){
    digitalWrite(relay_B, status);
    digitalWrite(relay_2, status);
  }
  else if(value == "B3"){
    digitalWrite(relay_B, status);
    digitalWrite(relay_3, status);
  }
  else if(value == "B4"){
    digitalWrite(relay_B, status);
    digitalWrite(relay_4, status);
  }
  else if(value == "B5"){
    digitalWrite(relay_B, status);
    digitalWrite(relay_5, status);
  }
  else if(value == "B6"){
    digitalWrite(relay_B, status);
    digitalWrite(relay_6, status);
  }
  else if(value == "B7"){
    digitalWrite(relay_B, status);
    digitalWrite(relay_7, status);
  }
  else if(value == "C1"){
    digitalWrite(relay_C, status);
    digitalWrite(relay_1, status);
  }
  else if(value == "C2"){
    digitalWrite(relay_C, status);
    digitalWrite(relay_2, status);
  }
  else if(value == "C3"){
    digitalWrite(relay_C, status);
    digitalWrite(relay_3, status);
  }
  else if(value == "C4"){
    digitalWrite(relay_C, status);
    digitalWrite(relay_4, status);
  }
  else if(value == "C5"){
    digitalWrite(relay_C, status);
    digitalWrite(relay_5, status);
  }
  else if(value == "C6"){
    digitalWrite(relay_C, status);
    digitalWrite(relay_6, status);
  }
  else if(value == "C7"){
    digitalWrite(relay_C, status);
    digitalWrite(relay_7, status);
  }
  else if(value == "D1"){
    digitalWrite(relay_D, status);
    digitalWrite(relay_1, status);
  }
  else if(value == "D2"){
    digitalWrite(relay_D, status);
    digitalWrite(relay_2, status);
  }
  else if(value == "D3"){
    digitalWrite(relay_D, status);
    digitalWrite(relay_3, status);
  }
  else if(value == "D4"){
    digitalWrite(relay_D, status);
    digitalWrite(relay_4, status);
  }
  else if(value == "D5"){
    digitalWrite(relay_D, status);
    digitalWrite(relay_5, status);
  }
  else if(value == "D6"){
    digitalWrite(relay_D, status);
    digitalWrite(relay_6, status);
  }
  else if(value == "D7"){
    digitalWrite(relay_D, status);
    digitalWrite(relay_7, status);
  }
}