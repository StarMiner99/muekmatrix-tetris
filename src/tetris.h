//
// Created by thijs on 08.05.24.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include "PIOMatrixOutput/color.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "block.h"
#include <hardware/structs/rosc.h>

#define SCROLL_SPEED 400
#define START_X 2
#define START_Y 0

#define LOSS_Y 2

class Tetris {
public:
    explicit Tetris(MatrixOutput* matrix);

    void init();
    void loop();

    void moveLeft();
    void moveRight();
    void rotate();

private:
    bool loss;

    Block* flyingBlock;
    volatile int blockX;
    volatile int blockY;
    volatile bool scheduleRotation;

    MatrixOutput* matrix;

    bool map[8][16] = {};
    Color colorMap[8][16] = {};

    Color displayMap[8][16] = {};

    void mergeBlockIntoDisplay();
    void mergeBlockIntoMap();

    void generateNewBlock();

    bool detectCollision();
    void detectAndDeleteRow();
    void detectLoss();
    static uint32_t genRandomNumber(int max);

    unsigned long prevMillis;
    unsigned int tickSpeed = SCROLL_SPEED;
    unsigned int frameSpeed = 17; // about 60fps

    void tick();
    void handleScheduledActions();
};


#endif //TETRIS_TETRIS_H
