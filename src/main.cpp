#include <Arduino.h>
#include "PIOMatrixOutput/pio_matrix_output.h"

#define BUTTON_SELECT 18
#define BUTTON_MODE 19

MatrixOutput matrix(pio0, 0, 0, 10, 11);
Color blind(255,255,255);
Color ahhhh_im_blinded_by_the_light[8][16] = {};


void setup() {
    // enable Leo's nice little features, so we don't need to do it ourselves
    matrix.enableSubframes();
    matrix.setFrameBufferInterval(0); // prevent our framebuffer from sending anything
    matrix.enableFrameBuffer();

    // first of all just for fun blind everyone:
    // populate list to be blinded:
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            ahhhh_im_blinded_by_the_light[i][j] = blind;
        }
    }

    matrix.setDisplayData(&ahhhh_im_blinded_by_the_light);
    matrix.sendData();
    delay(2000);
    matrix.clearDisplay();

}

void loop() {
// write your code here
}