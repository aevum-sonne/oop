#include <Shapes/Rectangle.h>
#include <sstream>
#include <utility>

Rectangle::Rectangle(Point point, double width, double height,
        std::uint32_t outline, std::uint32_t fill)
        : m_point(point)
        , m_width(width)
        , m_height(height)
        , m_outline(outline)
        , m_fill(fill)
{
}

double Rectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

double Rectangle::GetArea() const
{
    return m_width * m_height;
}

std::string Rectangle::ToString() const
{
    std::stringstream ss;

    ss << std::fixed << std::setprecision(3);
    ss << "Shape: Rectangle" << std::endl;
    ss << "Area: " << GetArea() << std::endl;
    ss << "Perimeter: " << GetPerimeter() << std::endl;
    ss << "Outline color: #" << std::hex << m_outline << std::endl;
    ss << "Fill color: #" << std::hex << m_fill << std::endl;
    ss << "Width: " << m_width << std::endl;
    ss << "Height: " << m_height << std::endl;
    ss << "Left top point: " << GetLeftTop() << std::endl;
    ss << "Right bottom point: " << GetRightBottom() << std::endl;

    return ss.str();
}

std::uint32_t Rectangle::GetOutlineColor() const
{
    return m_outline;
}

std::uint32_t Rectangle::GetFillColor() const
{
    return m_fill;
}

Point Rectangle::GetLeftTop() const
{
    return m_point;
}

Point Rectangle::GetRightBottom() const
{
    Point point{point.x = m_point.x + m_width, m_point.y - m_height};

    return point;
}

double Rectangle::GetWidth() const
{
    return m_width;
}

double Rectangle::GetHeight() const
{
    return m_height;
}
