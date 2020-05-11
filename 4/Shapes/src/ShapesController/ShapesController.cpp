#include <ShapesController/ShapesController.h>
#include <Shapes/Triangle.h>
#include <Shapes/Rectangle.h>
#include <Shapes/Circle.h>
#include <Shapes/LineSegment.h>
#include <Point/Point.h>
#include <cstring>
#include <sstream>

ShapesController::ShapesController(std::istream &input, std::ostream &output)
    : m_input(input)
    , m_output(output)
    , m_shapeMap(
            {
                    {
                    "triangle", [this](std::istream& stream) {
                        return ConstructTriangle(stream);
                    }},
                    {
                    "rectangle", [this](std::istream& stream) {
                        return ConstructRectangle(stream);
                    }},
                    {
                    "circle", [this](std::istream& stream) {
                        return ConstructCircle(stream);
                    }},
                    {
                    "ls", [this](std::istream& stream) {
                        return ConstructLineSegment(stream);
                    }},
                }
            )
{
}

void ShapesController::PrintUsageGuide()
{
    m_output << ConsoleMessages::INFO_MESSAGE;
    m_output << ConsoleMessages::TRIANGLE_USAGE;
    m_output << ConsoleMessages::RECTANGLE_USAGE;
    m_output << ConsoleMessages::CIRCLE_USAGE;
    m_output << ConsoleMessages::LINE_SEGMENT_USAGE;
}

bool ShapesController::HandleCommand()
{
    getline(m_input, m_commandLine);
    std::istringstream stream(m_commandLine);

    std::string shape;
    stream >> shape;

    auto it = m_shapeMap.find(shape);
    if (it != m_shapeMap.end())
    {
        return it->second(stream);
    }

    return false;
}


bool ShapesController::HandledExitCommand()
{
    if (m_commandLine == ArgumentConstants::EXIT_CODE)
    {
        return true;
    }

    return false;
}

std::vector<std::string> ReadStreamToVector(std::istream& stream)
{
    std::string buff;
    std::vector<std::string> vector;

    while (stream >> buff)
    {
        vector.push_back(buff);
    }

    return vector;
}

bool ShapesController::IsDouble(std::string& string) const
{
    if (string[0] == '.')
    {
        return false;
    }

    char cstr[string.size() + 1];
    strcpy(cstr, string.c_str());

    char* end;
    std::strtod(cstr, &end);

    return !(*cstr == '\0' || end == cstr || *end != '\0');
}

bool ShapesController::IsColor(std::string& string) const
{
    if (ArgumentConstants::COLOR_SIZE != string.size())
    {
        return false;
    }

    for (char c : string)
    {
        if (!(isdigit(c) || (c >= 'a' && c <= 'f') ||
              (c >= 'A' && c <= 'F')))
        {
            return false;
        }
    }

    return true;
}

bool ShapesController::ConstructTriangle(std::istream& stream)
{
    std::vector<std::string> args = ReadStreamToVector(stream);
    if (ArgumentConstants::TRIANGLE_COUNT != args.size())
    {
        m_output << ShapeMessages::TRIANGLE_INVALID_ARGUMENT;

        return true;
    }

    for (int i = 0; i < ArgumentConstants::TRIANGLE_COUNT - ArgumentConstants::COLOR_COUNT; i++)
    {
        if (!IsDouble(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COORD_ARGUMENT;

            return true;
        }
    }

    for (int i = ArgumentConstants::TRIANGLE_COUNT - ArgumentConstants::COLOR_COUNT; i < ArgumentConstants::TRIANGLE_COUNT; i++)
    {
        if (!IsColor(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COLOR_ARGUMENT;

            return true;
        }
    }

    Point vertex1 = {std::stod(args[0]), std::stod(args[1])};
    Point vertex2 = {std::stod(args[2]), std::stod(args[3])};
    Point vertex3 = {std::stod(args[4]), std::stod(args[5])};

    std::uint32_t outline = std::stoul(args[6], nullptr, MathConstants::STOUL_BASE);
    std::uint32_t fill = std::stoul(args[7], nullptr, MathConstants::STOUL_BASE);

    auto ptr = std::make_unique<Triangle>(vertex1, vertex2, vertex3,
            outline, fill);
    m_shapes.push_back(std::move(ptr));

    return true;
}

bool ShapesController::ConstructRectangle(std::istream& stream)
{
    std::vector<std::string> args = ReadStreamToVector(stream);
    if (ArgumentConstants::RECTANGLE_COUNT != args.size())
    {
        m_output << ShapeMessages::RECTANGLE_INVALID_ARGUMENT;

        return true;
    }

    for (int i = 0; i < ArgumentConstants::RECTANGLE_COUNT - ArgumentConstants::COLOR_COUNT; i++)
    {
        if (!IsDouble(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COORD_ARGUMENT;

            return true;
        }
    }

    for (int i = ArgumentConstants::RECTANGLE_COUNT - ArgumentConstants::COLOR_COUNT;
         i < ArgumentConstants::RECTANGLE_COUNT; i++)
    {
        if (!IsColor(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COLOR_ARGUMENT;

            return true;
        }
    }

    Point point{std::stod(args[0]), std::stod(args[1])};

    double width = std::stod(args[2]);
    double height = std::stod(args[3]);

    std::uint32_t outline = std::stoul(args[4], nullptr, MathConstants::STOUL_BASE);
    std::uint32_t fill = std::stoul(args[5], nullptr, MathConstants::STOUL_BASE);

    auto ptr = std::make_unique<Rectangle>(point, width, height, outline, fill);
    m_shapes.push_back(std::move(ptr));

    return true;
}

bool ShapesController::ConstructCircle(std::istream& stream)
{
    std::vector<std::string> args = ReadStreamToVector(stream);
    if (ArgumentConstants::CIRCLE_COUNT != args.size())
    {
        m_output << ShapeMessages::CIRCLE_INVALID_ARGUMENT;

        return true;
    }

    for (int i = 0; i < ArgumentConstants::CIRCLE_COUNT - ArgumentConstants::COLOR_COUNT; i++)
    {
        if (!IsDouble(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COORD_ARGUMENT;

            return true;
        }
    }

    for (int i = ArgumentConstants::CIRCLE_COUNT - ArgumentConstants::COLOR_COUNT;
         i < ArgumentConstants::CIRCLE_COUNT; i++)
    {
        if (!IsColor(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COLOR_ARGUMENT;

            return true;
        }
    }

    Point center{std::stod(args[0]), std::stod(args[1])};

    double radius = std::stod(args[2]);

    std::uint32_t outline = std::stoul(args[3], nullptr, MathConstants::STOUL_BASE);
    std::uint32_t fill = std::stoul(args[4], nullptr, MathConstants::STOUL_BASE);

    auto ptr = std::make_unique<Circle>(center, radius, outline, fill);
    m_shapes.push_back(std::move(ptr));

    return true;
}

bool ShapesController::ConstructLineSegment(std::istream& stream)
{
    std::vector<std::string> args = ReadStreamToVector(stream);
    if (ArgumentConstants::LINE_SEGMENT_COUNT != args.size())
    {
        m_output << ShapeMessages::LINE_SEGMENT_INVALID_ARGUMENT;

        return true;
    }

    for (int i = 0; i < ArgumentConstants::LINE_SEGMENT_COUNT - ArgumentConstants::LS_COLOR_COUNT; i++)
    {
        if (!IsDouble(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COORD_ARGUMENT;

            return true;
        }
    }

    for (int i = ArgumentConstants::LINE_SEGMENT_COUNT - ArgumentConstants::LS_COLOR_COUNT;
         i < ArgumentConstants::LINE_SEGMENT_COUNT; i++)
    {
        if (!IsColor(args[i]))
        {
            m_output << i+1 << ShapeMessages::INVALID_COLOR_ARGUMENT;

            return true;
        }
    }

    Point startPoint = {std::stod(args[0]), std::stod(args[1])};
    Point endPoint = {std::stod(args[2]), std::stod(args[3])};

    std::uint32_t outline = std::stoul(args[4], nullptr, MathConstants::STOUL_BASE);

    auto ptr = std::make_unique<LineSegment>(startPoint, endPoint, outline);
    m_shapes.push_back(std::move(ptr));

    return true;
}

bool ShapesController::CompareShapesByPerimeter(std::unique_ptr<IShape>& first, std::unique_ptr<IShape>& second)
{
    return first->GetPerimeter() < second->GetPerimeter();
}

void ShapesController::PrintShapeWithMinimumPerimeter()
{
    if (!m_shapes.empty())
    {
        auto minShape = std::min_element(m_shapes.begin(), m_shapes.end(),
                CompareShapesByPerimeter);

        m_output << ShapeMessages::MIN_PERIMETER;
        m_output << (*minShape)->ToString();
    }
}

bool ShapesController::CompareShapesByArea(std::unique_ptr<IShape>& first, std::unique_ptr<IShape>& second)
{
    return first->GetArea() < second->GetArea();
}

void ShapesController::PrintShapeWithMaximumArea()
{
    if (!m_shapes.empty())
    {
        auto maxShape = std::max_element(m_shapes.begin(), m_shapes.end(),
                CompareShapesByArea);

        m_output << ShapeMessages::MAX_AREA;
        m_output << (*maxShape)->ToString();
    }
}