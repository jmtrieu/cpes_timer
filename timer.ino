/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED 7-Segment backpacks 
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
int inPin = 8;
int val = 0;

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
  pinMode( inPin, INPUT );
}

void loop() {
  
  boolean drawDots = true;
  matrix.drawColon(drawDots);
  
  for (uint16_t minutes = 29; minutes > 0; minutes-- ) {
    matrix.writeDigitNum( 0 , ( minutes / 10 ), drawDots );
    matrix.writeDigitNum( 1, ( minutes % 10 ), drawDots );
    
    for ( uint16_t seconds = 59; seconds > 0; seconds-- ) {
      delay(1000);
      matrix.writeDigitNum( 3, ( seconds / 10 ), drawDots );
      matrix.writeDigitNum( 4, ( seconds % 10 ), drawDots );
      matrix.writeDisplay();

      val = digitalRead(inPin);
        if (val == HIGH ) {   
          Serial.print("Nick sux"); // turn OFF
        } else {
          Serial.print("Chris also sux");  // turn ON
      }
    }
    delay(1000);
    matrix.writeDigitNum( 3, 0, drawDots );
    matrix.writeDigitNum( 4, 0, drawDots );
    matrix.writeDisplay();
  }
}
