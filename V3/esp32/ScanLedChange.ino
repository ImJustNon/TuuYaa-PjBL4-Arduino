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