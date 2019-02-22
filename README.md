# LED-matrix
Adafruit RGBmatrixPanel Controller using Arduino Uno

## 0. Install
1. Install [Arduino IDE](https://www.arduino.cc/en/main/software)
2. Open Arduino Library Manager(Sketch->Include Library->Manage Libraries...)
3. Search for “gfx” and “rgb matrix panel” and install the corresponding Adafruit libraries.
4. Connect Arduino Uno(This code is *not* support Arduino Mega).
5. Upload Sketch.

## 1. How to Use
1. Open Serial monitor
2. Enter mode number
    * Mode description
        |  Mode number  |     Mode                              |
        | :-----------: | -----------                           |
        |       1       | Fill all(32x32) pixels in same color  |
        |       2       | Fill one pixel that selected          |
3. Enter required number
    * Mode 1\
        Enter color number\
        ```ex) 3 ```
    * Mode 2\
        Enter position(x,y) and color number\
        ```ex) 3 4 1```
    * Color description
        |  Color number  |     Color     |
        | :-----------: | :-----------:  |
        |       1       |  Red |
        |       2       |  Green |
        |       3       |  Blue |
        |       4       |  White |
4. Return to **number 2**

## 2. Function Description

* ```matrix.Color333(r, g, b)```

    Enter R,G,B Leds intensity in range 0~7.

* ```matrix.fillScreen(matrix.Color333(r, g, b))```
    
    Fill all pixels in entered color.

* ```matrix.drawRect(leftupX, leftupY, rightdownX, rightdownY, matrix.Color333(r, g, b))```

    Draw rectangle selected position(leftup to rightdown) in entered color.\
    Position range(X,Y) is 0~31.

* ```matrix.drawPixel(posX, posY,matrix.Color333(r, g, b))```

    Fill one pixels selected position(X,Y) in entered color.\
    Position range(X,Y) is 0~31.

## 3. Custom Leds

You can custom Led color and positions that add function in **Line 53**

## Reference
[Adafruit tutorial](https://learn.adafruit.com/32x16-32x32-rgb-led-matrix?view=all#test-example-code)