// ========================= get Current Time function =========================
String GetCurrentTime(){
  timeClient.update();
  time_t now = time(nullptr);
  String timestampString = String(now); 
  return timestampString + "000"; // add 000 for change year from 1990 to current(2024)
}
