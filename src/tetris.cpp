//
// Created by thijs on 08.05.24.
//

#include "tetris.h"
#include "tetrisBlocks.h"


// pick random block
// put it at top
// let it fall
// as soon as we touch something stop the block
// repeat
void Tetris::init() {
    generateNewBlock();
}

void Tetris::loop() {
    if (millis() - prevMillis >= frameSpeed) { // update display
        if (!loss) {
            mergeBlockIntoDisplay();
        }
        matrix->setDisplayData(&displayMap);
        matrix->sendData();
    }

    if (millis() - prevMillis >= tickSpeed && !loss) { // update game
        Serial.println("tick");
        tick();

        prevMillis = millis();
    }

}

void Tetris::tick() {


    if(detectCollision()) {
        mergeBlockIntoMap();
        detectAndDeleteRow();
        detectLoss(); // after row deletion to give the player one last chance, although it won't help much
        generateNewBlock();
    }

    if (loss) {
        // overlay with red color:
        for (int i = 0; i < MATRIX_HEIGHT; ++i) {
            for (int j = 0; j < MATRIX_LENGTH; ++j) {
                displayMap[i][j].add(&slightlyRed);
            }
        }
    }

    blockY++;
}

Tetris::Tetris(MatrixOutput *matrix) {
    this->matrix = matrix;
    prevMillis = millis();
    scheduleRotation = false;
    loss = false;
}

void Tetris::mergeBlockIntoDisplay() {
    // copy the current map
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            displayMap[i][j] = colorMap[i][j];
        }
    }

    // overlay it with a block at coordinates x and y
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // keep in mind that blocks are moving from left to right therefore we rotate the coordinates

            int actualY = MATRIX_HEIGHT - 1 - (blockX + i);
            if (actualY >= 0 && actualY <= 7) {
                if (displayMap[actualY][blockY + j].equals(&colorBlank)) {
                    displayMap[actualY][blockY + j] = (*flyingBlock->getColorArray())[j][i];
                }
            }

        }
    }
}

void Tetris::mergeBlockIntoMap() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // rotate the coords (same as merge into display)
            int actualY = MATRIX_HEIGHT - 1 - (blockX + i);
            if (actualY >= 0 && actualY <= 7) {
                map[actualY][blockY + j] |= (*flyingBlock->getBlockArray())[j][i];
                if (colorMap[actualY][blockY + j].equals(&colorBlank)) {
                    colorMap[actualY][blockY + j] = (*flyingBlock->getColorArray())[j][i];
                }
            }
        }
    }
}

bool Tetris::detectCollision() {
    // check every column of currently flying block
    for (int i = 0; i < 4; ++i) {
        int lengthInCol = flyingBlock->getLengthInColumn(i);
        if (lengthInCol != 0) {
            int checkX = MATRIX_HEIGHT - 1 - (blockX + i);
            int checkY = blockY + lengthInCol;
            if (checkY >= MATRIX_LENGTH) return true;
            if (map[checkX][checkY]) return true;
        }
    }

    return false;
}

void Tetris::generateNewBlock() {
    uint32_t randomBlockIndex = genRandomNumber(BLOCK_COUNT - 1);
    uint32_t randomColorIndex = genRandomNumber(COLOR_COUNT - 1);

    delete flyingBlock;
    flyingBlock = new Block(blocks[randomBlockIndex], blockColors[randomColorIndex]);

    blockX = START_X;
    blockY = START_Y;
}

uint32_t Tetris::genRandomNumber(int max) {
    uint32_t random;
    for (int i = 0; i < 4*8; ++i) { // 4 bytes
        random |= rosc_hw->randombit;
        random = random << 1;
    }
    return (random % max);
}

void Tetris::moveLeft() {
    // our block always aligns with the left side so no need in calculating widths

    bool allowMove = true;
    for (int i = 0; i < 4; ++i) {
        int checkX = MATRIX_HEIGHT - 1 - (blockX - 1);
        if (checkX >= 0) {
            if (map[checkX][blockY + i]) {
                allowMove = false;
            }
        }
    }

    if (blockX - 1 >= 0 && allowMove) {
        blockX--;
    }
}

void Tetris::moveRight() {
    // find out how far we are sticking out to the right
    int width = 4;
    bool inColumn = false;
    for (int i = 3; i >= 0; --i) {
        for (int j = 0; j < 4; ++j) {
            inColumn |= (*flyingBlock->getBlockArray())[j][i];
        }

        if (!inColumn) {
            width--;
        }

    }

    // check if we are moving into another block

    bool allowMove = true;
    for (int i = 0; i < 4; ++i) {
        int widthOnRow = 0;
        for (int j = 0; j < 4; ++j) {
            if ((*flyingBlock->getBlockArray())[i][j]) {
                widthOnRow = j+1;
            }
        }
        // check if collision is imminent
        int checkX = MATRIX_HEIGHT - 1 - (blockX + widthOnRow);
        if (checkX <= 7) {
            if (widthOnRow != 0 && map[checkX][blockY + i]) {
                allowMove = false;
            }
        }

    }

    if (blockX + width <= MATRIX_HEIGHT - 1 && allowMove) {
        blockX++;
    }
}

void Tetris::rotate() {
    // this might be bad nothing is volatile oopsie daisy -> implement scheduled rotation


    flyingBlock->rotateBlock();
    // we might need to push the block to the left, back into the screen:
    int width = 4;
    bool inColumn = false;
    for (int i = 3; i >= 0; --i) {
        for (int j = 0; j < 4; ++j) {
            inColumn |= (*flyingBlock->getBlockArray())[j][i];
        }

        if (!inColumn) {
            width--;
        }

    }

    if (blockX + width > MATRIX_HEIGHT) {
        blockX = MATRIX_HEIGHT - width;
    }


}

void Tetris::detectAndDeleteRow() {
    for (int i = 0; i < MATRIX_LENGTH; ++i) {
        bool rowComplete = true;
        for (int j = 0; j < MATRIX_HEIGHT; ++j) {
            if (!map[j][i]) { // we turn around the display by 90° therefore swap
                rowComplete = false;
            }
        }

        if (rowComplete) {
            // remove row
            for (int j = 0; j < i; ++j) { // row 0 cant get a replacement
                for (int k = 0; k < MATRIX_HEIGHT; ++k) {
                    map[k][i-j] = map[k][i-j-1]; // get row above current row and copy it over
                    colorMap[k][i-j] = colorMap[k][i-j-1];
                }
            }
        }
    }



}

void Tetris::detectLoss() {
    // as soon as a block embeds itself into the map at y = 2 -> game over
    for (int i = 0; i < MATRIX_HEIGHT; ++i) {
        if (map[i][LOSS_Y]) {
            loss |= true;
        }
    }
}

