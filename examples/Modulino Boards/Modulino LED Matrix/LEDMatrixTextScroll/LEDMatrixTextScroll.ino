#include <Qwilino_LED_Matrix.h>

/*
 * Qwilino LED Matrix - Text Scroll
 * Demonstrates the built-in text scrolling and character printing 
 * capabilities of the Qwilino matrix driver.
 */

Qwilino_LED_Matrix matrix;

void setup() {
  Serial.begin(115200);
  if (!matrix.begin()) while(1);
}

void loop() {
  // 1. Scrolling Text Example
  // The second parameter is the speed in milliseconds (lower is faster)
  matrix.scrollText("HELLO QWILINO!", 80);
  
  delay(1000);

  // 2. Static Text Example
  // Print a short text. Since the screen is small (12 pixels wide), 
  // only about 2 characters can fit on the screen at once.
  matrix.clear();
  matrix.printText("HI", 0, 1); // Print "HI" starting at X=0, Y=1
  matrix.show();
  
  delay(3000);
}