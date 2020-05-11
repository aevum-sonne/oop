#pragma once

#include <Interfaces/IShape.h>
#include <Point/Point.h>

class LineSegment: public IShape
{
public:
    LineSegment(Point startPoint, Point endPoint, std::uint32_t outline);

    [[nodiscard]] double GetArea() const override;
    [[nodiscard]] double GetPerimeter() const override;

    [[nodiscard]] std::string ToString() const override;

    [[nodiscard]] std::uint32_t GetOutlineColor() const override;

    [[nodiscard]] Point GetStartPoint() const;
    [[nodiscard]] Point GetEndPoint() const;

private:
    Point m_startPoint, m_endPoint;
    std::uint32_t m_outline;
};