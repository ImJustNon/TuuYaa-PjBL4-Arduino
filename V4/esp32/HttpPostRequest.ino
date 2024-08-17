// ========================= post request function =========================
String HttpPostRequest(const char* serverName, const char* postData) {
  WiFiClient client;
  HTTPClient http;
  http.setTimeout(30000);
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(postData);
  String payload = "{}";
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  lcd.setCursor(0, 0); lcd.print("Status : Ready  ");
  lcd.setCursor(0, 1); lcd.print("HTTP : " + String(httpResponseCode) + "     ");
  return payload;
}