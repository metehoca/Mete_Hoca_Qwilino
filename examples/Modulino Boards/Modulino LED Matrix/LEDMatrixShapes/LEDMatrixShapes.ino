#include <Qwilino_LED_Matrix.h>

/*
 * Qwilino LED Matrix - Custom Shapes
 * Demonstrates how to create and display your own custom 
 * 3x32-bit frames in the same format as the Arduino R4.
 */

Qwilino_LED_Matrix matrix;

// Create a custom 12x8 pattern (e.g., a simple square)
// Each 32-bit hex value represents a portion of the matrix rows/columns.
const uint32_t myCustomSquare[] = {
  0x00000000, 
  0x0ff00810, 
  0x08100ff0
};

void setup() {
  Serial.begin(115200);
  if (!matrix.begin()) while(1);
}

void loop() {
  // Load the custom array defined above
  matrix.loadFrame(myCustomSquare);
  matrix.show();
  delay(2000);

  matrix.clear();
  matrix.show();
  delay(1000);
}