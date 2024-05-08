//
// Created by thijs on 08.05.24.
//

#include "block.h"

void Block::translateBlockToColor() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            colorArray[i][j] = blockArray[i][j] ? *color : colorBlank;
        }
    }
}

Block::Block(bool (*blockArray)[4][4], Color *color) {
    this->color = color;
    // let's copy the array ...
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->blockArray[i][j] = blockArray[i][j];
        }
    }
    translateBlockToColor();
}

Color (*Block::getColorArray())[4][4] {
    return &colorArray;
}

int Block::getCollisionOnCol(int col) { // returns the row on which the piece would technically collide at the desired column(0 = no collision)
    int colCount = 0;

    for (int i = 0; i < 4; ++i) {
        if (blockArray[i][col]) {
            colCount = i;
        }
    }

    return colCount;
}

void Block::rotateBlock() { // always clockwise
    // buffer
    bool bufferArr[4][4];

    // rotation point is always the most left lower pixel from the block
    int rotationRow = 0;
    for (int i = 0; i < 4; ++i) {
        if (blockArray[i][0]) {
            rotationRow = i;
        }
    }

    double normalizer = (double)rotationRow / 2;

    // calculate rotated matrix
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {

            double x = -1 * (i - normalizer) + normalizer; // this should do the trick

            if (x >= 0 && x <= 3) {
                bufferArr[j][(int)x] = blockArray[i][j];
            }

        }
    }

    // overwrite old matrix and update values
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            blockArray[i][j] = bufferArr[i][j];
        }
    }
    translateBlockToColor();

    rotation = (rotation + 1) % 4; // set the rotation value

}
