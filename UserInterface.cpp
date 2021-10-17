//
// Created by Denis Basharin on 16.10.2021.
//

#include "UserInterface.h"
#include "Tetris.h"

#include <conio.h>
#include <stdio.h>


UserInterface::UserInterface(Tetris& tetris) : game(tetris) {
}

void UserInterface::Draw() const {
    system("cls");
    std::vector<std::vector<int> > print(std::max(HEIGHT, 8), std::vector<int>(WIDTH + 8, -1));
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            print[HEIGHT - 1 - i][j] = game.CellState({i, j});
        }
    }
    for (auto& p : game.CurrentFigure().Position()) {
        if (p.x < HEIGHT) {
            print[HEIGHT - 1 - p.x][p.y] = 3;
        }
    }
    print[0][WIDTH + 2] = 2;
    for (auto& p : game.NextFigure().Position({4, WIDTH + 3})) {
        print[p.x][p.y] = 3;
    }
    for (auto& line : print) {
        for (auto symb : line) {
            if (symb == -1) std::cout << " ";
            else if (symb == 0) std::cout << ".";
            else if (symb == 1) std::cout << "#";
            else if (symb == 2) std::cout << "Score: " << game.Score();
            else if (symb == 3) std::cout << "%";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void UserInterface::HandleClicks() {
    if (kbhit()) {
        char command = getch();
        bool changed = false;
        if (command == 'w') {
            changed = game.RotateFigure();
        } else if (command == 'a') {
            changed = game.MoveFigure(Direction::LEFT);
        } else if (command == 'd') {
            changed = game.MoveFigure(Direction::RIGHT);
        } else if (command == 's') {
            changed = game.MoveFigure(Direction::DOWN);
        }
        if (changed) {
            Draw();
        }
    }
}

void UserInterface::Emulate() {
    if (clock() - last_turn < clock_per_step) return;
    last_turn = clock();
    game.Emulate();
    ++rounds_passed;
    if (rounds_passed == 50) {
        clock_per_step = clock_per_step * 7 / 10;
    }
    Draw();
}

bool UserInterface::GameOver() const {
    return game.GameOver();
}

bool UserInterface::AskForRestart() {
    std::cout << "Your final score is " << game.Score() << std::endl;
    std::cout << "Restart ? y/n ";
    while(true) {
        while (!kbhit()) {
        }
        char ans = getch();
        if (ans == 'y' || ans == 'Y') {
            game.Restart();
            return true;
        } else if (ans == 'n' || ans == 'N') {
            return false;
        }
    }
}
