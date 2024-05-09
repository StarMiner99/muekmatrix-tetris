#include <Arduino.h>
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "tetris.h"

#define BUTTON_SELECT 18
#define BUTTON_MODE 19

MatrixOutput matrix(pio0, 0, 0, 10, 11);
Color blind(255,255,255);
Color ahhhh_im_blinded_by_the_light[8][16] = {};

Tetris tetrisGame(&matrix);

volatile bool rotated = false;

void buttonSelectISR() {
    if (digitalRead(BUTTON_SELECT) == LOW) { // falling edge
        if (!rotated) {
            tetrisGame.moveLeft();
        } else {
            rotated = false;
        }
    }
}

void buttonModeISR() {
    PinStatus modeStatus = digitalRead(BUTTON_MODE);
    if (modeStatus == HIGH) { // rising edge
        if (digitalRead(BUTTON_SELECT) == HIGH) { // rising edge whilst select is pressed
            rotated = true;
            tetrisGame.rotate();
        }
    }
    if (modeStatus == LOW) { // falling edge
        if (!rotated) {
            tetrisGame.moveRight();
        }
        // don't reset rotated because we did not yet release the select button

    }
}

void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("starting");
    // enable Leo's nice little features, for more color range
    matrix.enableSubframes();

    /*
    //matrix.setFrameBufferInterval(0); // we dont need this
    //matrix.enableFrameBuffer();
     */

    /*

    // first of all just for fun blind everyone:
    // populate list to be blinded:
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            ahhhh_im_blinded_by_the_light[i][j] = blind;
        }
    }

    // nah, don't uncomment this
    matrix.setDisplayData(&ahhhh_im_blinded_by_the_light);
    matrix.sendData();
    delay(2000);
    matrix.clearDisplay();
    delay(1000);
     */

    pinMode(BUTTON_SELECT, INPUT_PULLDOWN);
    pinMode(BUTTON_MODE, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(BUTTON_SELECT), buttonSelectISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON_MODE), buttonModeISR, CHANGE);

    Serial.println("starting tetris...");

    tetrisGame.reset();

}

void loop() {
    tetrisGame.loop();
}