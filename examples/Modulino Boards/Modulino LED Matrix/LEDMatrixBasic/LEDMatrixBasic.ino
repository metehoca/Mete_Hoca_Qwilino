#include <Qwilino_LED_Matrix.h>

/*
 * Qwilino LED Matrix - Basic Example
 * Demonstrates basic pixel manipulation and turning the matrix on/off.
 * The library automatically selects Wire1 for UNO/Nano R4, and Wire for others.
 */

Qwilino_LED_Matrix matrix;

void setup() {
  Serial.begin(115200);
  
  if (!matrix.begin()) {
    Serial.println("Matrix not found. Check wiring!");
    while (1);
  }
  Serial.println("Matrix ready.");
}

void loop() {
  matrix.clear();

  // Draw a border around the 12x8 matrix
  for (int x = 0; x < 12; x++) {
    matrix.setPixel(x, 0, true); // Top edge
    matrix.setPixel(x, 7, true); // Bottom edge
  }
  for (int y = 0; y < 8; y++) {
    matrix.setPixel(0, y, true); // Left edge
    matrix.setPixel(11, y, true); // Right edge
  }
  
  matrix.show(); // Push data to the screen
  delay(2000);

  // Clear screen and show a single blinking pixel in the center
  for(int i = 0; i < 5; i++) {
    matrix.clear();
    matrix.setPixel(5, 3, true);
    matrix.setPixel(6, 3, true);
    matrix.show();
    delay(300);
    
    matrix.clear();
    matrix.show();
    delay(300);
  }
}