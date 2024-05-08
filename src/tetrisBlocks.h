//
// Created by thijs on 08.05.24.
//

#ifndef TETRIS_TETRISBLOCKS_H
#define TETRIS_TETRISBLOCKS_H

#include "PIOMatrixOutput/color.h"


bool pieceI[4][4] = {{1,1,1,1},
                     {0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};

// 3 -> 0  3 - 3
// 2 -> 1  3 - 2
// 1 -> 2  3 - 1
// 0 -> 3  3 - 0

// max - x

// 1 -> 0
// 0 -> 1
bool pieceJ[4][4] = {{1,0,0,0},
                     {1,1,1,0},
                     {0,0,0,0},
                     {0,0,0,0}};

bool pieceL[4][4] = {{0,0,1,0},
                     {1,1,1,0},
                     {0,0,0,0},
                     {0,0,0,0}};
bool pieceO[4][4] = {{1,1,0,0},
                     {1,1,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
bool pieceS[4][4] = {{0,1,1,0},
                     {1,1,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
bool pieceT[4][4] = {{1,1,1,0},
                     {0,1,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
bool pieceZ[4][4] = {{1,1,0,0},
                     {0,1,1,0},
                     {0,0,0,0},
                     {0,0,0,0}};

#define BLOCK_COUNT 8
bool (*blocks[BLOCK_COUNT])[4][4] = {&pieceI, &pieceJ, &pieceL, &pieceO, &pieceS, &pieceT, &pieceT, &pieceZ};
// we don't want white so... allColors without white
#define COLOR_COUNT 6
Color *blockColors[COLOR_COUNT] = {&colorBlue, &colorCyan, &colorGreen, &colorPurple, &colorRed, &colorYellow};

Color slightlyRed(0.25, 0, 0);
#endif //TETRIS_TETRISBLOCKS_H
