#include <Qwilino_LED_Matrix.h>

/* * Create an instance of the LED Matrix.
 * The library automatically selects Wire1 for UNO R4 WiFi/Nano R4 
 * and Wire for other boards.
 */
Qwilino_LED_Matrix matrix;

// A heart shape represented in 3x32-bit format (Standard for R4 Matrix)
const uint32_t heartShape[] = {
  0x3184a444,
  0x42081100,
  0xa0040000
};

void setup() {
  Serial.begin(115200);

  /* * Initializing the matrix. 
   * It checks if the hardware is connected to the I2C bus.
   */
  if (!matrix.begin()) {
    Serial.println("Error: Qwilino LED Matrix not found!");
    Serial.println("Check your Qwiic/I2C connections.");
    while (1); // Halt execution if sensor is missing
  }

  Serial.println("Qwilino LED Matrix initialized successfully.");
}

void loop() {
  // --- Method 1: Loading a Full Frame ---
  // This is the fastest way to display complex icons or animations.
  matrix.loadFrame(heartShape);
  matrix.show(); // Push the buffer to the hardware
  delay(2000);

  // --- Method 2: Manual Pixel Control ---
  // You can turn individual LEDs on or off using X (0-11) and Y (0-7) coordinates.
  matrix.clear(); // Clear the internal buffer first
  
  // Draw a simple diagonal line
  for (int i = 0; i < 8; i++) {
    matrix.setPixel(i, i, true); // (X, Y, State)
    matrix.show();               // Update display for each step
    delay(100);
  }
  
  delay(1000);

  // --- Method 3: Clearing the Display ---
  matrix.clear();
  matrix.show();
  delay(1000);
}