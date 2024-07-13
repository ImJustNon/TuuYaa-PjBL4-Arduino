#include <SoftwareSerial.h>
SoftwareSerial Com(10, 11);

String incomingData = "";
double Timeout = millis();
char a[128];

void setup() {
  Serial.begin(9600);
  Com.begin(9600);
  Serial.println("Setup complete. Waiting for data...");
}

void loop() {
  if (Com.available()) {
    char SerialData = Com.read();
    Serial.println(SerialData);
  }

  if ((millis() - Timeout) > 200) {
    Timeout = millis();
    Serial.println("การเชื่อมต่อมีปัญหา");
  }
}
