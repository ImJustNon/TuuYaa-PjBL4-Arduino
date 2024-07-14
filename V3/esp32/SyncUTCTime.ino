// ========================= sync time function =========================
void SyncUTCTime(){
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 1000000000) {
    delay(1000);
    Serial.println("Waiting for time synchronization...");
  }
  Serial.println("");
  Serial.println("**************************************");
  Serial.println("Time synchronized");
  Serial.println("Current timestamp (seconds since 1970-01-01 00:00:00):");
  Serial.println("**************************************");
}