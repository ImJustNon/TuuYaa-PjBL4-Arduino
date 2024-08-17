#include <WiFiManager.h> 
#include <WiFi.h>  
#include <HardwareSerial.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int alertDelay = 500;
// กำหนดพินสำหรับ Buzzer
const int alertBuzzerPin = 23;
const int stopSwitchPin = 15;
// กำหนดพินสำหรับแถวและคอลัมน์
const int relay_1 = 32;
const int relay_2 = 33;
const int relay_3 = 25;
const int relay_4 = 26;
const int relay_5 = 27;
const int relay_6 = 14;
const int relay_7 = 12;

const int relay_A = 18;
const int relay_B = 5;
const int relay_C = 17;
const int relay_D = 16;

// ตั้งค่า
const String boxKey = "nonlnwza";
const String postCheckTime = "http://192.168.74.52:8899/api/alert/gettoday";
const String postRemoveTime = "http://192.168.74.52:8899/api/alert/remove";
// stupid var
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
int enableWifiReconnect = 0;
bool startAlert = false;
String alertJsonData = "";
String mealJsonData = "";
int mealCount = 0;
String alertDataId = "";
String selectedLedChannel = "";
// genious var
String jsonBuffer;
LiquidCrystal_I2C lcd(0x27, 16, 2);
HardwareSerial Com(1);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
  Serial.begin(9600);
  
  // ตั้งค่า LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("                ");
  lcd.setCursor(0, 1); lcd.print("                ");
  // ตั้งค่าพินแถวเป็น OUTPUT
  SetupModulePins();
  SetupDefaultStatusForEachModule();

  WiFiManager wifiManager;
  lcd.setCursor(0, 0); lcd.print("SSID : ESP32_AP");
  lcd.setCursor(0, 1); lcd.print("IP : 192.168.4.1");
  if (!wifiManager.autoConnect("ESP32_AP")) {
    Serial.println("Failed to connect and hit timeout");
    lcd.setCursor(0, 0); lcd.print("WiFi : FAIL     ");
    lcd.setCursor(0, 1); lcd.print(" Restarting.... ");
    delay(3000);
    ESP.restart();
    delay(5000);
  }
  Serial.println("Connected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 0); lcd.print("WiFi : OK       ");
  lcd.setCursor(0, 1); lcd.print("                ");
  
  SyncUTCTime();

  

  // // ตั้งค่าสถานะของ LED ที่ต้องการเปิด
  // ledMatrix[0][0] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[1][1] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[0][2] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[0][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[1][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[3][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  lcd.setCursor(0, 0); lcd.print("Status : Ready  ");
  lcd.setCursor(0, 1); lcd.print("                ");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      enableWifiReconnect = 1; // enable wifi re-connection
      updateAlertTime();
      checkAlertTime();
      // removeAlertTime();
      // ScanLedChange();
      // StartAlertSound();
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

void updateAlertTime(){
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

  Serial.println(currentAlertArrayDataLength);

  if(currentAlertArrayDataLength != 0){ // have data
    for(int i = 0; i < currentAlertArrayDataLength; i++){
      String selectedAlertTimeData = currentAlertArrayData[i]["time"];
      unsigned long long selectedAlertTimeInt = strtoull(selectedAlertTimeData.c_str(), NULL, 10);
      unsigned long long currentTimeInt = strtoull((currentTime + "000").c_str(), NULL, 10);

      Serial.println(selectedAlertTimeInt);
      Serial.println(currentTimeInt);
      
      if(currentTimeInt > selectedAlertTimeInt){ // เช็คเวลาปัจจุบันกับเวลาทั้งหมดในขอมูลเเจ้งเตือน
        String selectedAlertSlotData = currentAlertArrayData[i]["slot"];
        int selectedAlertIdData = currentAlertArrayData[i]["id"];
        JSONVar selectedMealData = currentAlertArrayData[i]["meal"];
        mealCount = selectedMealData.length();
        selectedLedChannel = selectedAlertSlotData;
        String joinedMealData = JoinArray(selectedMealData);

        Serial.println(joinedMealData);

        if(selectedMealData.length() > 1){ // have two meal
          for(int i = 0; i < selectedMealData.length(); i++){
            WriteAlertLed(selectedAlertSlotData, LOW);
            lcd.setCursor(0, 0); lcd.print("Channel : " + String(selectedAlertSlotData) + "     ");
            lcd.setCursor(0, 1); lcd.print("Meal : " + String(joinedMealData) + "     ");
            startAlert = true;
            alertDataId = String(selectedAlertIdData);
            StartAlertSound();
            if(i == selectedMealData.length() - 1){
              break;
            }
            delay(1 * 60 * 60 * 1000); //3600000 // 1hr
          }
          break;
        }
        else {
          WriteAlertLed(selectedAlertSlotData, LOW);
          lcd.setCursor(0, 0); lcd.print("Channel : " + String(selectedAlertSlotData) + "     ");
          lcd.setCursor(0, 1); lcd.print("Meal : " + String(joinedMealData) + "     ");
          startAlert = true;
          alertDataId = String(selectedAlertIdData);
          StartAlertSound();
          break;
        }
      }
    }
    removeAlertTime();
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

      if(stopSwitchStatus == 0){ // it will be 1 when touch switch
        startAlert = false;
        WriteAlertLed(selectedLedChannel, HIGH); // turn light off
        digitalWrite(alertBuzzerPin, HIGH); // turn buzzer off
        lcd.setCursor(0, 0); lcd.print("Channel : Opened           ");

        int closeChannelSwitchCheck = true;
        while(closeChannelSwitchCheck){
          int switchStatusValue = digitalRead(stopSwitchPin);
          delay(2000);
          if(switchStatusValue == 1){
            closeChannelSwitchCheck = false;
            lcd.setCursor(0, 0); lcd.print("Channel : Closed           ");
          }
        }
      }
    }  
    // RemoveAlertTime();  
    // ESPRestart();
  }
}

void removeAlertTime(){
  // removeAlertJsonDataFromArray();
  Serial.println(alertJsonData);

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

// void removeAlertJsonDataFromArray(){
//   int idToRemove = alertDataId.toInt();
//   JSONVar alertDataParsedJson = JSON.parse(alertJsonData);
//   Serial.println(alertDataParsedJson.length());
//   JSONVar newArray;
//   if(alertDataParsedJson.length() != 0){
//     for (int i = 0; i < alertDataParsedJson.length(); i++) {
//       int scanForCheckId = alertDataParsedJson[i]["id"];
//       if (scanForCheckId != idToRemove){
//         // If it doesn't match, add it to the new array
//         int indexlegth = newArray.length() || 0;
//         newArray[indexlegth] = alertDataParsedJson[i];
//       }
//     }
//     alertJsonData = String(JSON.stringify(newArray));
//   }
// }
