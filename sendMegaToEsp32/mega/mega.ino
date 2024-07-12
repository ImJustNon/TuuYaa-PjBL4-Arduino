#include <SoftwareSerial.h>

SoftwareSerial Com(10,11); // 10 คือ RX, 11 คือ TX

void setup() {
  Serial.begin(9600);
  Com.begin(9600);  
}

void loop() {
  
  static int value1 = 0;
  static int value2 = 100;
  
  Serial.print("Tx sent value1:");
  Serial.print(value1);
  Serial.print(" value2:");
  Serial.println(value2);
  
  Com.write('#');
  Com.print(value1);
  Com.write(':');
  Com.print(value2);
  Com.write(';');
  
  delay(100);

  if(++value1==100){
    value1 = 0;
  }

  if(value2>0){
    value2--;
  }else{
    value2=100;  
  }
  
}
