// กำหนดพินสำหรับแถวและคอลัมน์
const int rowPins[7] = {17, 5, 18, 19, 21, 22, 23};
const int colPins[4] = {26, 25, 33, 32};

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

void setup() {
  // ตั้งค่าพินแถวเป็น OUTPUT
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  // ตั้งค่าพินคอลัมน์เป็น OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH); // ใช้ HIGH เพราะจะใช้ LOW เพื่อเปิด LED
  }
}

void loop() {
  ledMatrix[6][2] = true; // เปิด LED ที่ตำแหน่งนี้
  long startTime = millis();
  while (millis() - startTime < 5000) { // 5 วินาที
    ScanLedChange();
  }

  ledMatrix[6][2] = false; // ปิด LED ที่ตำแหน่งนี้
  startTime = millis();
  while (millis() - startTime < 5000) { // 5 วินาที
    ScanLedChange();
  }
}

void ScanLedChange() {
  // สแกนแถวและคอลัมน์เพื่อเปิด LED ตามตำแหน่งที่กำหนด
  for (int row = 0; row < 7; row++) {
    digitalWrite(rowPins[row], HIGH); // เปิดแถวปัจจุบัน

    for (int col = 0; col < 4; col++) {
      if (ledMatrix[row][col]) {
        digitalWrite(colPins[col], LOW); // เปิด LED ที่ตำแหน่งนี้
      } else {
        digitalWrite(colPins[col], HIGH); // ปิด LED ที่ตำแหน่งนี้
      }
    }

    delay(2); // หน่วงเวลาเล็กน้อยเพื่อให้ LED สว่างพอ

    digitalWrite(rowPins[row], LOW); // ปิดแถวปัจจุบัน
  }
}
