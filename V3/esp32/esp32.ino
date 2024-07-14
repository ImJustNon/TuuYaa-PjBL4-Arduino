#include <WiFiManager.h> 
#include <WiFi.h>  
#include <HardwareSerial.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// กำหนดพินสำหรับ Buzzer
const int alertBuzzerPin = 55;
const int stopSwitchPin = 56;
// กำหนดพินสำหรับแถวและคอลัมน์
const int rowPins[7] = {65,66,67,68,69,70,71};
const int colPins[4] = {72,73,74,75};
// อาร์เรย์สำหรับเก็บสถานะของ LED
bool ledMatrix[7][4] = {
  {false, false, false, false}, // แถว 1
  {false, false, false, false}, // แถว 2
  {false, false, false, false}, // แถว 3
  {false, false, false, false}, // แถว 4
  {false, false, false, false}, // แถว 5
  {false, false, false, false}, // แถว 6
  {false, false, false, false}  // แถว 7
};
// ตั้งค่า
const String boxKey = "nonlnwza";
const String postCheckTime = "http://192.168.8.52:8899/api/alert/check";
const String postRemoveTime = "http://192.168.8.52:8899/api/alert/remove";
// stupid var
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
int enableWifiReconnect = 0;
bool startAlert = false;
String alertJsonData = "";
String alertDataId = "";
// genious var
String jsonBuffer;
LiquidCrystal_I2C lcd(0x27, 16, 2);
HardwareSerial Com(1);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
  Serial.begin(9600);
  pinMode(alertBuzzerPin, OUTPUT); // ตั้งค่าพิน Buzzer เป็น OUTPUT
  // ตั้งค่า LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
  lcd.print("LCD1602 I2c Test");
  // ตั้งค่าพินแถวเป็น OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }
  // ตั้งค่าพินคอลัมน์เป็น OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH); // ใช้ HIGH เพราะจะใช้ LOW เพื่อเปิด LED
  }
  
  WiFiManager wifiManager;
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
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

  

  // // ตั้งค่าสถานะของ LED ที่ต้องการเปิด
  // ledMatrix[0][0] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[1][1] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[0][2] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[0][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[1][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[3][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]

}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      enableWifiReconnect = 1; // enable wifi re-connection
      getAlertTime();
      checkAlertTime();
      ScanLedChange();
      StartAlertSound();
      // Serial.println(GetCurrentTime());
    } else {
      Serial.println("WiFi Disconnected");
      if(enableWifiReconnect == 1){
        ESPRestart();
      }
      // SyncUTCTime();
    }
    lastTime = millis();
    startAlert = true;
  }
}

void getAlertTime(){
  String currentTime = GetCurrentTime();
  String postJsonData = "{\"boxKey\":\"" + boxKey + "\", \"currentTime\": \"" + currentTime + "\" }";
  String checkTimeData = HttpPostRequest(postCheckTime.c_str(), postJsonData.c_str());
  JSONVar checkTimeDataObjectPost = JSON.parse(checkTimeData);
  if (JSON.typeof(checkTimeDataObjectPost) == "undefined"){
    Serial.println("Parsing checkTimeData input failed!");
    return;
  }
  String checkTimeDataObjectPost_ResponseStatus = checkTimeDataObjectPost["status"];
  JSONVar checkTimeDataObjectPost_AlertJsonData = checkTimeDataObjectPost["data"];
  if(checkTimeDataObjectPost_ResponseStatus == "OK"){
    alertJsonData = JSON.stringify(checkTimeDataObjectPost_AlertJsonData); // update alert data
    // Serial.println(AlertJsonData);
  }
}

void checkAlertTime(){
  String currentTime = GetCurrentTime();
  String currentAlertJsonData = alertJsonData;
  JSONVar currentAlertArrayData = JSON.parse(currentAlertJsonData);
  int currentAlertArrayDataLength = currentAlertArrayData.length();

  if(currentAlertArrayDataLength != 0){ // have data
    for(int i = 0; i < currentAlertArrayDataLength; i++){
      String selectedAlertTimeData = currentAlertArrayData[i]["time"];
      int selectedAlertTimeInt = selectedAlertTimeData.toInt();
      int currentTimeInt = currentTime.toInt();

      if(currentTimeInt > selectedAlertTimeInt){ // เช็คเวลาปัจจุบันกับเวลาทั้งหมดในขอมูลเเจ้งเตือน
        String selectedAlertSlotData = currentAlertArrayData[i]["slot"];
        int selectedAlertSlotDataFirstNumber = String(selectedAlertSlotData.charAt(0)).toInt();
        int selectedAlertSlotDataSecondNumber = String(selectedAlertSlotData.charAt(1)).toInt();
        String selectedAlertIdData = currentAlertArrayData[i]["id"];

        ledMatrix[selectedAlertSlotDataFirstNumber][selectedAlertSlotDataSecondNumber] = true;
        startAlert = true;
        alertDataId = selectedAlertIdData;
        break;
      }
    }
  }
}

void StartAlertSound(){
  if(startAlert == true){
    while(startAlert){
      digitalWrite(alertBuzzerPin, LOW);
      delay(250);
      digitalWrite(alertBuzzerPin, HIGH);
      delay(500);
      int stopSwitchStatus = digitalRead(stopSwitchPin);

      if(stopSwitchStatus == 0){
        startAlert = false;
      }
    }
    RemoveAlertTime();    
    // ESPRestart();
  }
}

void RemoveAlertTime(){
  String alertId = alertDataId;
  String postJsonData = "{\"boxKey\":\"" + boxKey + "\", \"alertId\": \"" + alertId + "\" }";
  String removeTimeData = HttpPostRequest(postRemoveTime.c_str(), postJsonData.c_str());
  JSONVar removeTimeDataObjectPost = JSON.parse(removeTimeData);
  if (JSON.typeof(removeTimeDataObjectPost) == "undefined"){
    Serial.println("Parsing removeTimeData input failed!");
    return;
  }
  String removeTimeDataObjectPost_ResponseStatus = removeTimeDataObjectPost["status"];
  // if(checkTimeDataObjectPost_ResponseStatus == "OK"){
  //   // ESPRestart();
  // }
}
