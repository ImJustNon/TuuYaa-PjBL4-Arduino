

// กำหนดพินสำหรับแถวและคอลัมน์
const int rowPins[7] = {13, 12, 11, 10, 9, 8, 7};
const int colPins[4] = {6, 5, 4, 3};

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
  // ledMatrix[0][0] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[1][1] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[0][2] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[0][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[1][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
  // ledMatrix[3][3] = true; // [เเถว(เเนวนอน)][คอลัมน์(เเนวตั้ง)]
}

void loop() {
  ledMatrix[1][1] = true;
  ScanLedChange();
  delay(100);
  ledMatrix[1][1] = false;
  ScanLedChange();
  delay(100);
}

void ScanLedChange(){
// สแกนแถวและคอลัมน์เพื่อเปิด LED ตามตำแหน่งที่กำหนด
  for (int row = 0; row < 7; row++) {
    digitalWrite(rowPins[row], HIGH); // เปิดแถวปัจจุบัน

    for (int col = 0; col < 4; col++) {
      if (ledMatrix[row][col]) {
        digitalWrite(colPins[col], LOW); // เปิด LED ที่ตำแหน่งนี้
      }
    }

    delay(1); // หน่วงเวลาเล็กน้อยเพื่อให้ LED สว่างพอ

    for (int col = 0; col < 4; col++) {
      digitalWrite(colPins[col], HIGH); // ปิด LED ที่ตำแหน่งนี้
    }

    digitalWrite(rowPins[row], LOW); // ปิดแถวปัจจุบัน
  }
}
