/*
  Qwilino Clock - Basic Time Reading
  
  This example demonstrates how to:
  1. Initialize the Real-Time Clock (RTC) module.
  2. Synchronize time with your computer during upload if power was lost.
  3. Read and print the current date and time to the Serial Monitor.
*/

#include <Qwilino_Clock.h>

Qwilino_Clock rtc;

void setup() {
  Serial.begin(115200);

  // Initialize the RTC. It automatically selects Wire or Wire1 based on your board.
  if (!rtc.begin()) {
    Serial.println("ERROR: Qwilino Clock not found! Check connections.");
    while (1); 
  }

  // Check if the clock stopped (e.g., battery was removed)
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, updating time to compile time...");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  // Get current time from the module
  DateTime now = rtc.now();

  // Print Date: DD.MM.YYYY
  if (now.day() < 10) Serial.print('0');
  Serial.print(now.day()); Serial.print(".");
  if (now.month() < 10) Serial.print('0');
  Serial.print(now.month()); Serial.print(".");
  Serial.print(now.year()); Serial.print(" - ");

  // Print Time: HH:MM:SS
  if (now.hour() < 10) Serial.print('0');
  Serial.print(now.hour()); Serial.print(":");
  if (now.minute() < 10) Serial.print('0');
  Serial.print(now.minute()); Serial.print(":");
  if (now.second() < 10) Serial.print('0');
  Serial.println(now.second());

  delay(1000); // Wait 1 second before next update
}