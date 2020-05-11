#pragma once

#include <Interfaces/ISolidShape.h>

class Triangle: public ISolidShape
{
public:
    Triangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t outline,
            std::uint32_t fill);

    [[nodiscard]] double GetArea() const override;
    [[nodiscard]] double GetPerimeter() const override;

    [[nodiscard]] std::string ToString() const override;

    [[nodiscard]] std::uint32_t GetOutlineColor() const override;
    [[nodiscard]] std::uint32_t GetFillColor() const override;

    [[nodiscard]] Point GetVertex1() const;
    [[nodiscard]] Point GetVertex2() const;
    [[nodiscard]] Point GetVertex3() const;

private:
    static double GetLengthOfSide(Point first, Point second);

    Point m_vertex1, m_vertex2, m_vertex3;
    std::uint32_t m_outline, m_fill;
};