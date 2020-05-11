#pragma once

#include <Constants/Constants.h>
#include <Shapes/Rectangle.h>
#include <iostream>
#include <map>
#include <vector>
#include <memory>

class ShapesController
{
public:
    ShapesController(std::istream& input, std::ostream& output);

    void PrintUsageGuide();

    bool HandleCommand();
    bool HandledExitCommand();

    void PrintShapeWithMinimumPerimeter();
    void PrintShapeWithMaximumArea();

    bool IsDouble(std::string& string) const;
    bool IsColor(std::string& string) const;

private:
    bool ConstructTriangle(std::istream& stream);
    bool ConstructRectangle(std::istream& stream);
    bool ConstructCircle(std::istream& stream);
    bool ConstructLineSegment(std::istream& stream);

    static bool CompareShapesByPerimeter(std::unique_ptr<IShape>& first, std::unique_ptr<IShape>& second);
    static bool CompareShapesByArea(std::unique_ptr<IShape>& first, std::unique_ptr<IShape>& second);

    using Handler = std::function<bool(std::istream& args)>;
    using ShapeMap = std::map<std::string, Handler>;

    std::istream& m_input;
    std::ostream& m_output;

    std::string m_commandLine;

    std::vector<std::unique_ptr<IShape>> m_shapes;

    const ShapeMap m_shapeMap;
};