#include <WiFiManager.h>   // Library for WiFi configuration
#include <WiFi.h>          // ESP32 WiFi library
#include <HardwareSerial.h>

HardwareSerial Com(1); // Use hardware UART port 1 on ESP32

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging

  // Initialize WiFiManager
  WiFiManager wifiManager;
  
  // Uncomment the following line for debug output
  // wifiManager.setDebugOutput(true);

  // Try to connect to saved WiFi credentials, if not found, enter configuration mode
  if (!wifiManager.autoConnect("ESP32_AP")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    // Reset and try again or do whatever you want
    ESP.restart();
    delay(5000);
  }

  // On successful connect
  Serial.println("Connected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize your communication port (Com) here
  Com.begin(9600, SERIAL_8N1, 16, 17); // RX pin 16, TX pin 17
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

  if (++value1 == 100) {
    value1 = 0;
  }

  if (value2 > 0) {
    value2--;
  } else {
    value2 = 100;  
  }
}
