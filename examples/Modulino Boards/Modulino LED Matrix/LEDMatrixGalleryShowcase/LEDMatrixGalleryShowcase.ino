#include <Qwilino_LED_Matrix.h>

/*
 * Qwilino LED Matrix - Gallery Showcase
 * Demonstrates how to load pre-defined 3x32-bit frames (shapes) 
 * built directly into the Qwilino library.
 */

Qwilino_LED_Matrix matrix;

void setup() {
  Serial.begin(115200);
  if (!matrix.begin()) while(1);
}

void loop() {
  // Load and display the Heart shape from the library gallery
  matrix.loadFrame(Qwilino_Gallery_Heart);
  matrix.show();
  delay(1500);

  // Load and display the Smile shape
  matrix.loadFrame(Qwilino_Gallery_Smile);
  matrix.show();
  delay(1500);

  // Load and display the Check (Tick) mark
  matrix.loadFrame(Qwilino_Gallery_Check);
  matrix.show();
  delay(1500);

  // Load and display the Cross (X) mark
  matrix.loadFrame(Qwilino_Gallery_Cross);
  matrix.show();
  delay(1500);
}