#include <HardwareSerial.h>  // Use HardwareSerial instead of SoftwareSerial for ESP32

HardwareSerial Com(1);  // Use Serial1 (RX pin 16, TX pin 17) for ESP32

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  Com.begin(9600, SERIAL_8N1, 16, 17);  // Initialize Serial1 with RX pin 16, TX pin 17
}

void loop() {
  static int value1, value2;
  static char SerialBuffer[4];
  static char SerialData;
  static byte SerialState = 0;
  static byte SerialIndex = 0;
  static double Timeout = millis();
  
  if (Com.available()) {
    SerialData = Com.read();  

    switch(SerialState) {
      case 0:
        if (SerialData == '#') {
          SerialState = 1; 
          SerialIndex = 0;
        }
        break;
              
      case 1:
        if (SerialData == ':') {
          SerialBuffer[SerialIndex] = '\0';
          value1 = atoi(SerialBuffer);
          SerialIndex = 0;
          SerialState = 2;  
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 4) {
            SerialState = 0;
          }
        }
        break;
              
      case 2:
        if (SerialData == ';') {
          SerialBuffer[SerialIndex] = '\0';
          value2 = atoi(SerialBuffer);
  
          Serial.print("Rx receive value1: ");
          Serial.print(value1);
          Serial.print(" value2: ");
          Serial.println(value2);
          Timeout = millis();
          SerialState = 0;
        } else {
          SerialBuffer[SerialIndex] = SerialData;
          if (++SerialIndex == 4) {
            SerialState = 0;
          }  
        }
        break;
    }
  }

  if ((millis() - Timeout) > 200) {
    Timeout = millis();
    Serial.println("การเชื่อมต่อมีปัญหา");  // Thai characters: "Connection problem"
  }
}
