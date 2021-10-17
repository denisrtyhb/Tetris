//
// Created by Denis Basharin on 16.10.2021.
//

#pragma once
#include "Figure.h"
#include <algorithm>

const int HEIGHT = 15;
const int WIDTH = 10;

#include <iostream>

class Tetris {
public:
    Tetris();
    bool RotateFigure();
    bool MoveFigure(Direction dir);
    void Emulate();
    void Restart();
    bool GameOver() const;
    bool CellState(Point pos) const;
    const Figure& CurrentFigure() const;
    const Figure& NextFigure() const;
    int Score() const;
private:
    void CreateNewFigure();
    void DeleteFullRows();
    bool ValidPosition(const Figure& fig) const;
    void LockCell(const Point& p);
    bool FreeCell(const Point& p) const;
    static Figure RandomFigure();
    std::vector<std::vector<bool> > block;
    Figure current_figure, next_figure;
    int score = 0;
    bool GAME_OVER = false;
};
