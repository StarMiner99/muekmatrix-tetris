//
// Created by thijs on 08.05.24.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#define SCROLL_SPEED 200

class Tetris {
public:
    void init();
    void loop();

private:
    bool map[8][16] = {};

};


#endif //TETRIS_TETRIS_H
