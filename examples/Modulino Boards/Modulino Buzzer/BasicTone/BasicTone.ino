/*
  Qwilino Buzzer - Basic Tone Test
  
  This example demonstrates how to:
  1. Initialize the buzzer module.
  2. Play simple tones with specific frequencies and durations.
  3. Create a siren effect using a loop.
*/

#include <Qwilino_Buzzer.h>

QwilinoBuzzer buzzer;

void setup() {
  Serial.begin(115200);
   
  // Initialize the module. It will use the default I2C port (Wire or Wire1).
  if (!buzzer.begin()) {
    Serial.println("ERROR: Buzzer module not found! Check your wiring.");
    while(1); // Halt the program if the module is missing
  }
  
  Serial.println("Buzzer connected. Playing melody...");
}

void loop() {
  // Play a simple beep at 1000 Hz for 200 milliseconds
  buzzer.tone(1000, 200);
  delay(500);
  
  // Play a lower tone at 500 Hz for 200 milliseconds
  buzzer.tone(500, 200);
  delay(500);
  
  // Play a higher tone at 2000 Hz for 200 milliseconds
  buzzer.tone(2000, 200);
  delay(1000);
  
  // Create a siren effect by gradually increasing the frequency
  // The frequency goes from 500 Hz to 1450 Hz in steps of 50 Hz
  for(int i = 500; i < 1500; i += 50){
    buzzer.tone(i, 20); // Play each frequency for 20 milliseconds
    delay(20);
  }
  
  // Wait for 2 seconds before restarting the loop
  delay(2000);
}