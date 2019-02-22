// MIT License

// Copyright (c) 2019 OISL-Yonsei

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int state = 0;

void setup() {
  // initialize serial
  Serial.begin(9600);
  matrix.begin();

  /* Custom your own LED matrix in here */
  // matrix.fillScreen(matrix.Color333(r, g, b));
  // matrix.drawRect(leftupX, leftupY, rightdownX, rightdownY, matrix.Color333(r, g, b));
  // matrix.drawPixel(posX, posY,matrix.Color333(r, g, b));
}

void loop() {

  int color = 0;  
  int posX = 0;
  int posY = 0;
  int leftupX = 0;
  int leftupY = 0;
  int rightdownX = 0;
  int rightdownY = 0;

  switch (state)
  {
    case 0: // init state
      // Serial.println("1.All pixels 2.Point pixel 3.Fill pixels")
      Serial.println("Enter mode number:");
      Serial.flush();
      state = 10;
      break;

    case 10: // Serial wait state
      if(Serial.available() > 0){
        long buf = Serial.parseInt();
        state = buf;
      }
      break;

    case 1: // All pixels
        if(Serial.available() > 0){
          // Serial.println("1.Red 2.Green 3.Blue 4.White");
          Serial.println("Enter Color :");
          color = Serial.parseInt();
        }
        if(color != 0){
          switch (color)
          {
            case 1: // Red
              matrix.fillScreen(matrix.Color333(7, 0, 0));
              state = 0;
              break;
            case 2: // Green
              matrix.fillScreen(matrix.Color333(0, 7, 0));
              state = 0;
              break;
            case 3: // Blue
              matrix.fillScreen(matrix.Color333(0, 0, 7));
              state = 0;
              break;
            case 4: // White
              matrix.fillScreen(matrix.Color333(7, 7, 7));
              state = 0;
              break;
          }                            
        }
      break;
    
    case 2: // Point pixel
        if(Serial.available() > 0){
          Serial.println("Enter Position(x,y),color :");
          posX = Serial.parseInt() - 1;
          posY = Serial.parseInt() - 1;
          color = Serial.parseInt();
        }
        // fill the screen with 'black'
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        if(color != 0){
          switch (color)
          {
            case 1: // Red
              matrix.drawPixel(posX, posY,matrix.Color333(7, 0, 0));
              state = 0;
              break;
            case 2: // Green
              matrix.drawPixel(posX, posY,matrix.Color333(0, 7, 0));
              state = 0;
              break;
            case 3: // Blue
              matrix.drawPixel(posX, posY,matrix.Color333(0, 0, 7));
              state = 0;
              break;
            case 4: // White
              matrix.drawPixel(posX, posY,matrix.Color333(7, 7, 7));
              state = 0;
              break;
          }                            
        }
      break;

      /* To be updated */
      // case 3: // Fill pixels
      //   if(Serial.available() > 0){
      //     Serial.println("Enter Position(x1,y1,x2,y2),color :");
      //     leftupX = Serial.parseInt() - 1;
      //     leftupY = Serial.parseInt() - 1;
      //     rightdownX = Serial.parseInt() - 1;
      //     rightdownY = Serial.parseInt() - 1;
      //     color = Serial.parseInt();
      //   }
      //   // fill the screen with 'black'
      //   matrix.fillScreen(matrix.Color333(0, 0, 0));
      //   if(color != 0){
      //     switch (color)
      //     {
      //       case 1: // Red
      //         matrix.drawRect(leftupX, leftupY, rightdownX, rightdownY, matrix.Color333(7, 0, 0));
      //         state = 0;
      //         break;
      //       case 2: // Green
      //         matrix.drawRect(leftupX, leftupY, rightdownX, rightdownY, matrix.Color333(0, 7, 0));
      //         state = 0;
      //         break;
      //       case 3: // Blue
      //         matrix.drawRect(leftupX, leftupY, rightdownX, rightdownY, matrix.Color333(0, 0, 7));
      //         state = 0;
      //         break;
      //       case 4: // White
      //         matrix.drawRect(leftupX, leftupY, rightdownX, rightdownY, matrix.Color333(7, 7, 7));
      //         state = 0;
      //         break;
      //     }                            
      //   }
      // break;
  }
}
