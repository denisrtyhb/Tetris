//
// Created by Denis Basharin on 16.10.2021.
//

#include "Tetris.h"
#include "UserInterface.h"

int main() {
    srand(time(NULL));
    Tetris game;
    UserInterface interface(game);
    while (!interface.GameOver() || interface.AskForRestart()) {
        interface.Emulate();
        interface.HandleClicks();
    }
    return 0;
}
