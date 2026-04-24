/*
  Qwilino Buttons - Basic Test
  
  This example demonstrates how to:
  1. Detect button presses (A, B, and C).
  2. Toggle the corresponding LED on the module each time a button is pressed.
*/

#include <Qwilino_Buttons.h>

QwilinoButtons buttons;

// Variables to store the current state of each LED (on/off)
bool ledA = false;
bool ledB = false;
bool ledC = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwilino Buttons Test...");
  
  // Initialize the module. It will use the default I2C port (Wire or Wire1).
  if (!buttons.begin()) {
    Serial.println("ERROR: Buttons module not found! (Address 0x3E)");
    while (1); // Halt the program if the module is missing
  }
  
  Serial.println("Module ready. Press the buttons!");
  
  // Flash all LEDs on startup as a quick visual test
  buttons.setLeds(true, true, true);
  delay(500);
  buttons.setLeds(false, false, false);
}

void loop() {
  // The update() function reads the current state of the buttons from the module.
  // It returns 'true' ONLY if a button has been pressed or released since the last check.
  // This prevents the code from spamming the I2C bus when nothing is happening.
  if (buttons.update()) {
    
    // Check if Button A was just pressed
    if (buttons.isPressed('A')) {
      Serial.println("Button A Pressed!");
      ledA = !ledA; // Toggle the state (if false make true, if true make false)
    }

    // Check if Button B was just pressed
    if (buttons.isPressed('B')) {
      Serial.println("Button B Pressed!");
      ledB = !ledB; // Toggle the state
    }

    // Check if Button C was just pressed
    if (buttons.isPressed('C')) {
      Serial.println("Button C Pressed!");
      ledC = !ledC; // Toggle the state
    }
    
    // Send the new LED states to the module so they light up (or turn off)
    buttons.setLeds(ledA, ledB, ledC);
  }
  
  delay(50); // Small delay for loop stability
}