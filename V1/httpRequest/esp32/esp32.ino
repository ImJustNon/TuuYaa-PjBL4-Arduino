#include <WiFiManager.h> 
#include <WiFi.h>  
#include <HardwareSerial.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <NTPClient.h>
#include <TimeLib.h>

// stupid var
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
bool startAlert = true;
String jsonBuffer;
// genious var
HardwareSerial Com(1);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
  Serial.begin(9600);
  
  WiFiManager wifiManager;
  if (!wifiManager.autoConnect("ESP32_AP")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    ESP.restart();
    delay(5000);
  }
  Serial.println("Connected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  SyncUTCTime();

  Com.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(GetCurrentTime());
      SendSerialValue();
    } else {
      Serial.println("WiFi Disconnected");
      ReconnectWifi();
      // syncTime();
    }
    lastTime = millis();
    startAlert = true;
  }
}




