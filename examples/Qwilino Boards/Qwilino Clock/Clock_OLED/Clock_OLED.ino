/*
  Qwilino Clock - OLED Display Example (Native)
  
  This example demonstrates how to:
  1. Read the time from the Qwilino Clock (RTC) module.
  2. Display the current time, date, and day using the lightweight 
     Qwilino_OLED library instead of heavy third-party graphic libraries.
*/

#include <Wire.h>
#include <Qwilino_Clock.h>
#include <Qwilino_OLED.h>

// Initialize the OLED display. 
// Note: Default address in library is 0x3D. If your screen uses 0x3C, specify it here:
Qwilino_OLED display;

Qwilino_Clock rtc;

// Array to easily convert day numbers to their names
const char* days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(115200);

  // Initialize the OLED display. It automatically selects Wire or Wire1.
  if (!display.begin()) {
    Serial.println(F("ERROR: Qwilino OLED not found!"));
    while (1) delay(100);
  }
  
  // Initialize the RTC module
  if (!rtc.begin()) {
    Serial.println(F("ERROR: Qwilino Clock not found! Check connections."));
    while (1) delay(100);
  }

  // If power was lost (e.g., battery removed), sync with compile time
  if (rtc.lostPower()) {
    Serial.println(F("RTC lost power, setting time to compile time..."));
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  // --- Static Header ---
  // We print this once in setup() using the F() macro to save RAM.
  display.printLine(F("== LOCAL TIME =="), 0, true);
}

void loop() {
  // Fetch current time
  DateTime now = rtc.now();
  
  // Buffers to hold our formatted text
  char timeBuf[16];
  char dateBuf[16];

  // Format Time as HH:MM:SS (e.g., 09:05:02)
  sprintf(timeBuf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  // Format Date as DD.MM.YYYY (e.g., 05.08.2024)
  sprintf(dateBuf, "%02d.%02d.%04d", now.day(), now.month(), now.year());

  // --- Dynamic Updates ---
  // Qwilino_OLED's printLine automatically clears only the specific line, 
  // preventing screen flicker. We use 'true' to center the text.
  display.printLine(timeBuf, 1, true);                  // Line 1: Time
  display.printLine(dateBuf, 2, true);                  // Line 2: Date
  display.printLine(days[now.dayOfTheWeek()], 3, true); // Line 3: Day of the Week

  delay(1000); // Wait 1 second before the next update
}