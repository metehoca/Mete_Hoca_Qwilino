/*
  Qwilino Knob - Basic Test
  
  This example demonstrates how to:
  1. Initialize the Knob (Rotary Encoder) module.
  2. Read the current rotation position.
  3. Detect rotation direction (clockwise/counter-clockwise).
  4. Detect button presses on the knob.
*/

#include <Qwilino_Knob.h>

QwilinoKnob knob;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("Qwilino Knob Test Starting...");

  // Initialize the module. It automatically selects the correct I2C port (Wire or Wire1).
  // Default I2C address is 0x3A.
  if (!knob.begin()) {
    Serial.println("ERROR: Knob module not found!");
    Serial.println("Please check your wiring.");
    while (1) delay(100);
  }

  Serial.println("Module is ready. Turn the knob or press the button!");
}

void loop() {
  // Fetch the latest data from the module
  // You must call update() in your loop to get fresh values
  knob.update();

  // Get the current position and direction
  int pos = knob.getPosition();
  int dir = knob.getDirection();

  // If the knob was turned, print the new position and direction
  if (dir != 0) {
    Serial.print("Position: ");
    Serial.print(pos);
    
    if (dir == 1) {
      Serial.println(" (Turned Right)");
    } else if (dir == -1) {
      Serial.println(" (Turned Left)");
    }
  }

  // Check if the encoder button is currently being pressed
  if (knob.isPressed()) {
    Serial.println("Button is PRESSED!");
    
    // Optional feature: Reset position to 0 when button is pressed
    // knob.setPosition(0); 
    
    delay(200); // Simple debounce delay to avoid spamming the Serial Monitor
  }

  delay(10); // Small delay for loop stability
}