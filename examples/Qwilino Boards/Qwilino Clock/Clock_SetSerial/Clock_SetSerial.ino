#include <Wire.h>
#include "Qwilino_Clock.h"

Qwilino_Clock rtc;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!rtc.begin()) {
    while (1) {
      Serial.println("Qwilino Clock not found!");
      delay(1000);
    }
  }
}

void loop() {
  if (Serial.available() > 0) {
    while (Serial.available() > 0) { Serial.read(); }

    Serial.println("\n--- SET NEW DATE/TIME ---");
    int year   = askValue("Year (e.g. 2026): ");
    int month  = askValue("Month (1-12): ");
    int day    = askValue("Day (1-31): ");
    int hour   = askValue("Hour (0-23): ");
    int minute = askValue("Minute (0-59): ");
    int second = askValue("Second (0-59): ");

    rtc.adjust(DateTime(year, month, day, hour, minute, second));

    Serial.println("\nTIME UPDATED!");
    Serial.println("----------------------------\n");
  }

  DateTime now = rtc.now();

  if (now.day() < 10) Serial.print('0');
  Serial.print(now.day()); Serial.print(".");
  if (now.month() < 10) Serial.print('0');
  Serial.print(now.month()); Serial.print(".");
  Serial.print(now.year()); Serial.print(" - ");
  if (now.hour() < 10) Serial.print('0');
  Serial.print(now.hour()); Serial.print(":");
  if (now.minute() < 10) Serial.print('0');
  Serial.print(now.minute()); Serial.print(":");
  if (now.second() < 10) Serial.print('0');
  Serial.print(now.second());

  Serial.println("   [Press any key + Enter to set the time]");

  delay(1000);
}

int askValue(String question) {
  Serial.print(question);
  while (Serial.available() == 0) {
  }
  int value = Serial.parseInt();
  Serial.println(value);
  while (Serial.available() > 0) { Serial.read(); }
  return value;
}