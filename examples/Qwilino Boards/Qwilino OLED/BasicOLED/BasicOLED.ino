/*
  Qwilino OLED - Comprehensive Example (v1.0)

  Shows all features step by step:
    - Connection check (begin() returns bool)
    - Flash text with F() macro (SRAM saving)
    - Label + numeric value combinations
    - Inverted color and sleep mode
*/

#include <Qwilino_OLED.h>

// ── Qwilino_OLED display(0x3C); //Select I2C address (Default: 0x3D)
Qwilino_OLED display;

void setup() {
  Serial.begin(115200);
  
  // ── Selects Wire1 for R4 Wifi and Nano R4, defaults to Wire for others.
  // ── Usage: display.begin(&Wire1)
  if (!display.begin()) {
    Serial.println(F("ERROR: Qwilino OLED not found!"));
    while (true) delay(1000);
  }
  Serial.println(F("Display ready."));

  // ── Flash text with F() macro ──────────────────
   // F("...") -> text stays in Flash, SRAM is not used.
  display.printLine(F("****************"), 0, true);
  display.printLine(F(" QWILINO OLED "),   1, true);
  display.printLine(F("   BasicOLED  "),   2, true);
  display.printLine(F("****************"), 3, true);
  delay(2000);

  // ── Invert color flash effect ───────────────────────────────
  display.invertDisplay(true);
  delay(400);
  display.invertDisplay(false);
  delay(1000);

  display.clear();
}

void loop() {
  // Simulated sensor data
  float temperature = 24.567f;
  int   humidity    = 45;
  long  uptime      = millis() / 1000UL;

  // Usage: printLine(24.56f, 1);                   // Number only, line 1 (left-aligned, 2 decimals default)
  // Usage: printLine(24.567f, 2, 3, true);         // Number only, line 2, 3 decimal places, centered
  // Usage: printLine("TEMP: ", 24.5f, 3, 1, true); // Label + number, line 3, 1 decimal place, centered

  // ── Line 0: fixed header (in Flash with F()) ────────────
  display.printLine(F("== SENSORS =="), 0, true);

  // ── Line 1: Label + float ─────────────────────────────
  display.printLine("Temp: ", temperature, 1, 1);   // 1 decimal

  // ── Line 2: Label + int ───────────────────────────────
  display.printLine("Humidity: %", humidity, 2);

  // ── Line 3: Label + long ──────────────────────────────
  display.printLine("Uptime(s): ", uptime, 3);

  delay(3000);

  // ── Dynamic line update ───────────────────────────
  // Only line 3 changes; other lines do not flicker.
  display.printLine(F("Connection OK..."), 3, true);
  delay(2000);

  // ── Sleep mode ────────────────────────────────────────────
  display.clear();
  display.printLine(F("Entering"),   1, true);
  display.printLine(F("sleep mode..."),  2, true);
  delay(1500);

  display.sleep();
  // Display turns off, content is preserved in RAM
  delay(2000);

  display.wake();    // Display wakes up, previous content comes back
  display.clear();

  display.printLine(F("Display woke up!"), 1, true);
  delay(1500);

  display.clear();
}