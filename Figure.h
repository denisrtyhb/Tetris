//
// Created by Denis Basharin on 16.10.2021.
//

#pragma once

#include <vector>
#include "Point.h"

enum Direction {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

class Figure {
private:
    std::vector<Point> points;
    Point pos;

public:
    Figure() = default;
    Figure(std::vector<Point> &&fig) : points(fig), pos() {
    }
    std::vector<Point> Position(const Point& dif) const;
    std::vector<Point> Position() const;
    Figure Move(Direction dir) const;
    Figure Rotate() const;
    static Figure RandomFigure(int x, int y);
};

Figure RandomFigure(int x, int y);

