//
// Created by Denis Basharin on 16.10.2021.
//

#pragma once

struct Point {
    int x;
    int y;
    Point() = default;
    Point(int x_, int y_) : x(x_), y(y_) {
    }
    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }
};
