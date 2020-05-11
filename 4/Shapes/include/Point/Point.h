#pragma once

#include <fstream>

struct Point
{
    double x;
    double y;

    bool operator==(const Point& point) const;
    bool operator<(double delta) const;
    Point operator-(const Point& point) const;

    friend std::ostream& operator<<(std::ostream& out, const Point& point);
};
