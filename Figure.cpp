//
// Created by Denis Basharin on 16.10.2021.
//

#include "Figure.h"
#include <iostream>

std::vector<Figure> FourPointFigures = {
        Figure({{0, 0},
                {1, 0},
                {2, 0},
                {0, 1}}),
        Figure({{0,  0},
                {1,  0},
                {0,  1},
                {-1, 1}}),
        Figure({{0,  0},
                {1,  0},
                {-1, 0},
                {-2, 0}}),
        Figure({{0, 0},
                {1, 0},
                {0, 1},
                {1, 1}}),
        Figure({{0,  0},
                {1,  0},
                {-1, 0},
                {0,  1}}),
};

std::vector<Point> Figure::Position(const Point& dif) const {
    std::vector<Point> res;
    for (auto& p : points) {
        res.push_back(p + dif);
    }
    return res;
}

std::vector<Point> Figure::Position() const {
    std::vector<Point> res;
    for (auto& p : points) {
        res.push_back(p + pos);
    }
    return res;
}

Figure Figure::Move(Direction dir) const {
    Figure res = *this;
    if (dir == Direction::DOWN) {
        res.pos.x -= 1;
    } else if (dir == Direction::LEFT) {
        res.pos.y -= 1;
    } else if (dir == Direction::UP) {
        res.pos.x += 1;
    } else {
        res.pos.y += 1;
    }
    return res;
}

Figure Figure::Rotate() const{
    Figure res = *this;
    for (auto &p: res.points) {
        std::swap(p.x, p.y);
        p.x *= -1;
    }
    return res;
}

Figure Figure::RandomFigure(int x, int y) {
    Figure res = FourPointFigures[rand() % FourPointFigures.size()];
    res.pos = {x, y};
    if (rand() & 1) {
        for (auto& p : res.points) {
            p.x *= -1;
            p.y *= -1;
        }
    }
    return res;
}
