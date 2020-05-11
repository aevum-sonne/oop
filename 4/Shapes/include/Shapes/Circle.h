#pragma once

#include <Interfaces/ISolidShape.h>

class Circle: public ISolidShape
{
public:
    Circle(Point center, double radius, std::uint32_t outline, std::uint32_t fill);

    [[nodiscard]] double GetArea() const override;
    [[nodiscard]] double GetPerimeter() const override;

    [[nodiscard]] std::string ToString() const override;

    [[nodiscard]] std::uint32_t GetOutlineColor() const override;
    [[nodiscard]] std::uint32_t GetFillColor() const override;

    [[nodiscard]] Point GetCenter() const;
    [[nodiscard]] double GetRadius() const;

private:
    Point m_center;
    double m_radius;
    std::uint32_t m_outline, m_fill;
};