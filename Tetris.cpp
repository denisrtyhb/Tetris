//
// Created by Denis Basharin on 16.10.2021.
//

#include "Tetris.h"
#include <iostream>
Tetris::Tetris() {
    block.assign(HEIGHT, std::vector<bool> (WIDTH, false));
    current_figure = RandomFigure();
    next_figure = RandomFigure();
}

bool Tetris::RotateFigure() {
    if (GAME_OVER) return false;
    auto rotated = current_figure.Rotate();
    if (ValidPosition(rotated)) {
        current_figure = rotated;
        return true;
    }
    return false;
}

bool Tetris::MoveFigure(Direction dir) {
    if (GAME_OVER) return false;
    auto moved = current_figure.Move(dir);
    if (ValidPosition(moved)) {
        current_figure = moved;
        return true;
    }
    return false;
}

void Tetris::Emulate() {
    if (GAME_OVER) return;
    if (MoveFigure(Direction::DOWN)) {
        return;
    }
    CreateNewFigure();
    DeleteFullRows();
}

void Tetris::CreateNewFigure() {
    for (auto& p : current_figure.Position()) {
        LockCell(p);
    }
    if (GAME_OVER) return;
    current_figure = next_figure;
    next_figure = RandomFigure();
}

void Tetris::DeleteFullRows() {
    std::vector<std::vector<bool> > new_block;
    int destroyed = 0;
    for (auto& line : block) {
        bool full = true;
        for (auto x : line) {
            if (!x) {
                full = false;
                break;
            }
        }
        if (!full) {
            new_block.push_back(line);
        } else {
            ++destroyed;
        }
    }
    new_block.resize(HEIGHT, std::vector<bool>(WIDTH, false));
    score += destroyed * (destroyed + 1) / 2;
    block = new_block;
}

bool Tetris::ValidPosition(const Figure &fig) const {
    for (auto& p : fig.Position()) {
        if (!FreeCell(p)) {
            return false;
        }
    }
    return true;
}

bool Tetris::FreeCell(const Point &p) const {
    return p.x >= 0 && p.y >= 0 && p.y < block[0].size() && (p.x >= block.size() || !block[p.x][p.y]);
}

void Tetris::LockCell(const Point &p) {
    if (p.x >= 0 && p.y >= 0 && p.y < block[0].size()) {
        if (p.x < HEIGHT) {
            block[p.x][p.y] = true;
        }
        if (p.x >= HEIGHT - 1) {
            GAME_OVER = true;
        }
    }
}

 void Tetris::Restart() {
    GAME_OVER = false;
    score = 0;
    block.assign(HEIGHT, std::vector<bool>(WIDTH));
    current_figure = RandomFigure();
    next_figure = RandomFigure();
}

bool Tetris::GameOver() const {
    return GAME_OVER;
}

bool Tetris::CellState(Point pos) const {
    return block[pos.x][pos.y];
}

const Figure& Tetris::CurrentFigure() const {
    return current_figure;
}

const Figure& Tetris::NextFigure() const {
    return next_figure;
}

int Tetris::Score() const {
    return score;
}

Figure Tetris::RandomFigure() {
    return Figure::RandomFigure(HEIGHT, 1 + rand() % (WIDTH - 3));
}
