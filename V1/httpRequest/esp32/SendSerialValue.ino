// ========================= Send value function =========================
void SendSerialValue() {
  // checkAlertTime();
  static int value1 = 0;
  static int value2 = 100;



  String stringData = "A" + String(value1) + ",A" + String(value2);
  int stringDataLength = stringData.length();
  String finalStringData = String(stringDataLength) + ";" + stringData;

  Com.print(finalStringData);

  delay(100);

  Serial.print("Tx sent value1:");
  Serial.println(finalStringData);

  if (++value1 == 100) {
    value1 = 0;
  }

  if (value2 > 0) {
    value2--;
  } else {
    value2 = 100;
  }
}