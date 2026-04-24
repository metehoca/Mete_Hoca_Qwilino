/*
  Qwilino Pixels - Basic Animation Test
  
  This example demonstrates how to:
  1. Initialize the RGB LED module.
  2. Set individual pixels to specific colors and brightness levels.
  3. Push updates using the show() function (framebuffer concept).
*/

#include <Qwilino_Pixels.h>

QwilinoPixels leds;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("Qwilino Pixels Test Starting...");

  // Initialize the module. It automatically selects the correct I2C port (Wire or Wire1).
  if (!leds.begin()) {
    Serial.println("ERROR: Pixels module not found!");
    Serial.println("Check your I2C connections.");
    while (1) delay(100);
  }

  Serial.println("Module is ready. Starting animations...");
}

void loop() {
  // --- Animation 1: Fill Blue Sequentially ---
  Serial.println("Animation: Blue Fill");
  for (int i = 0; i < 8; i++) {
    // set(index, color, brightness)
    // Brightness is 0-255. We use 50 here so it's not blindingly bright.
    leds.set(i, BLUE, 50); 
    
    // show() pushes the memory buffer to the physical LEDs
    leds.show();
    delay(100);
  }
  
  delay(500);

  // --- Animation 2: Instant Red ---
  Serial.println("Animation: All Red");
  for (int i = 0; i < 8; i++) {
    // We update the buffer but don't call show() yet
    leds.set(i, RED, 50);
  }
  // Now we update all 8 LEDs at the exact same time
  leds.show(); 
  delay(1000);

  // --- Animation 3: Turn Off ---
  Serial.println("Animation: Clear");
  leds.clear(); // Sets all colors and brightness to 0 in the buffer
  leds.show();  // Apply changes
  
  delay(1000);
}