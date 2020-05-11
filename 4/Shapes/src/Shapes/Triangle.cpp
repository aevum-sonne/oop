#include <Shapes/Triangle.h>
#include <cmath>
#include <sstream>

Triangle::Triangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t outline, std::uint32_t fill)
            : m_vertex1(vertex1)
            , m_vertex2(vertex2)
            , m_vertex3(vertex3)
            , m_outline(outline)
            , m_fill(fill)
{
}

double Triangle::GetArea() const
{
    return std::fabs(0.5 * ((m_vertex1.x-m_vertex3.x) * (m_vertex2.y-m_vertex3.y)
        - (m_vertex2.x-m_vertex3.x) * (m_vertex1.y-m_vertex3.y)));
}

double Triangle::GetLengthOfSide(Point first, Point second)
{
    return std::sqrt(pow((first.x-second.x), 2)
    + pow((first.y-second.y), 2));
}

double Triangle::GetPerimeter() const
{
    return GetLengthOfSide(m_vertex1, m_vertex2)
    + GetLengthOfSide(m_vertex1, m_vertex3)
    + GetLengthOfSide(m_vertex3, m_vertex2);
}

std::string Triangle::ToString() const
{
    std::stringstream ss;

    ss << std::fixed << std::setprecision(3);

    ss << "Shape: Triangle" << std::endl;
    ss << "Area: " << GetArea() << std::endl;
    ss << "Perimeter: " << GetPerimeter() << std::endl;
    ss << "Outline color: #" << std::hex << m_outline << std::endl;
    ss << "Fill color: #" << std::hex << m_fill << std::endl;
    ss << "Vertex 1: " << m_vertex1 << std::endl;
    ss << "Vertex 2: " << m_vertex2 << std::endl;
    ss << "Vertex 3: " << m_vertex3 << std::endl;

    return ss.str();
}

std::uint32_t Triangle::GetOutlineColor() const
{
    return m_outline;
}

std::uint32_t Triangle::GetFillColor() const
{
    return m_fill;
}

Point Triangle::GetVertex1() const
{
    return m_vertex1;
}

Point Triangle::GetVertex2() const
{
    return m_vertex2;
}

Point Triangle::GetVertex3() const
{
    return m_vertex3;
}
