// กำหนดพินสำหรับแถวและคอลัมน์
const int rowPins[7] = {32, 33, 25, 26, 27, 14, 12};
const int colPins[4] = {23, 22, 21, 19};

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

  // ตั้งค่าสถานะของ LED ที่ต้องการเปิด
  
}

void loop() {
  ledMatrix[1][1] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  ScanLedChange();
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

    delay(1); // หน่วงเวลาเล็กน้อยเพื่อให้ LED สว่างพอ

    digitalWrite(rowPins[row], LOW); // ปิดแถวปัจจุบัน
  }
}
