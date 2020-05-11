#include <Point/Point.h>
#include <cmath>

bool Point::operator==(const Point& point) const
{
    return x == point.x && y == point.y;
}

Point Point::operator-(const Point& point) const
{
    Point result{std::fabs(x - point.x), std::fabs(y - point.y)};

    return result;
}

bool Point::operator<(double delta) const
{
    return x < delta && y < delta;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << std::fixed << std::setprecision(3) << "(" << point.x << "; "
        << point.y << ")";

    return out;
}