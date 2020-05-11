#include <Shapes/LineSegment.h>
#include <cmath>
#include <sstream>

LineSegment::LineSegment(Point startPoint, Point endPoint, std::uint32_t outline)
        : m_startPoint(startPoint)
        , m_endPoint(endPoint)
        , m_outline(outline)
{
}

double LineSegment::GetArea() const
{
    return 0;
}

double LineSegment::GetPerimeter() const
{
    return std::sqrt(std::pow(m_endPoint.x - m_startPoint.x, 2)
        + std::pow(m_endPoint.y - m_startPoint.y, 2));
}

std::string LineSegment::ToString() const
{
    std::stringstream ss;

    ss << std::fixed << std::setprecision(3);
    ss << "Shape: Line Segment" << std::endl;
    ss << "Area: " << GetArea() << std::endl;
    ss << "Perimeter: " << GetPerimeter() << std::endl;
    ss << "Outline color: #" << std::hex << m_outline << std::endl;
    ss << "Start point: #" << m_startPoint << std::endl;
    ss << "End point: " << m_endPoint << std::endl;

    return ss.str();
}

std::uint32_t LineSegment::GetOutlineColor() const
{
    return m_outline;
}

Point LineSegment::GetStartPoint() const
{
    return m_startPoint;
}

Point LineSegment::GetEndPoint() const
{
    return m_endPoint;
}
