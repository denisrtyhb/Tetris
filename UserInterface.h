//
// Created by Denis Basharin on 16.10.2021.
//

#pragma once
#include <time.h>
class Tetris;

class UserInterface {
public:
    UserInterface(Tetris& tetris);
    void Emulate();
    void HandleClicks();
    bool GameOver() const;
    bool AskForRestart();

private:
    void Draw() const;
    int rounds_passed = 0;
    int last_turn = 0;
    int clock_per_step = CLOCKS_PER_SEC;
    Tetris& game;
};
