#pragma once

#include <Interfaces/ISolidShape.h>

class Rectangle: public ISolidShape
{
public:
    Rectangle(Point point, double width, double height,
              std::uint32_t outline, std::uint32_t fill);

    [[nodiscard]] double GetArea() const override;
    [[nodiscard]] double GetPerimeter() const override;

    [[nodiscard]] std::string ToString() const override;

    [[nodiscard]] std::uint32_t GetOutlineColor() const override;
    [[nodiscard]] std::uint32_t GetFillColor() const override;

    [[nodiscard]] Point GetLeftTop() const;
    [[nodiscard]] Point GetRightBottom() const;
    [[nodiscard]] double GetWidth() const;
    [[nodiscard]] double GetHeight() const;

private:
    Point m_point;
    double m_width, m_height;
    std::uint32_t m_outline, m_fill;
};