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

// 3 -> 0
// 2 -> 1  2 + 4 % 4
// 1 -> 2  1 + 4 % 4
// 0 -> 3 0 + 4 % 4

// 1.5 = lastRow / 2
// (x - 1.5) * -1 +1.5

// 1 -> 0
// 0 -> 1
bool pieceJ[4][4] = {{1,0,0,0},
                     {1,1,1,0},
                     {0,0,0,0},
                     {0,0,0,0}};
bool pieceL[4][4] = {{0,0,0,1},
                     {0,1,1,1},
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

#endif //TETRIS_TETRISBLOCKS_H
