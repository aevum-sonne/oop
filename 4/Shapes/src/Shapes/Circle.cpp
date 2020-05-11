#include <Shapes/Circle.h>
#include <cmath>
#include <sstream>

Circle::Circle(Point center, double radius, std::uint32_t outline, std::uint32_t fill)
            : m_center(center)
            , m_radius(radius)
            , m_outline(outline)
            , m_fill(fill)
{
}

double Circle::GetArea() const
{
    return M_PI * std::pow(m_radius, 2);
}

double Circle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string Circle::ToString() const
{
    std::stringstream ss;

    ss << std::fixed << std::setprecision(3);
    ss << "Shape: Circle" << std::endl;
    ss << "Area: " << GetArea() << std::endl;
    ss << "Perimeter: " << GetPerimeter() << std::endl;
    ss << "Outline color: #" << std::hex << m_outline << std::endl;
    ss << "Fill color: #" << std::hex << m_fill << std::endl;
    ss << "Center point: " << m_center << std::endl;
    ss << "Radius: " << m_radius << std::endl;

    return ss.str();
}

std::uint32_t Circle::GetOutlineColor() const
{
    return m_outline;
}

std::uint32_t Circle::GetFillColor() const
{
    return m_fill;
}

Point Circle::GetCenter() const
{
    return m_center;
}

double Circle::GetRadius() const
{
    return m_radius;
}
