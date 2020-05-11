#pragma once

#include <string>

namespace ConsoleMessages
{
    constexpr inline auto INFO_MESSAGE = "Available commands: triangle, rectangle, circle, ls\n"
                                         "Usage:\n";
    constexpr inline auto TRIANGLE_USAGE = "\ttriangle <coord x1> <coord y1> <coord x2> <coord y2> "
                                            "<coord x3> <coord y3> <outline-color> <fill-color>\n";
    constexpr inline auto RECTANGLE_USAGE = "\trectangle <left-top x> <left-top y> <width> <height> "
                                            "<outline-color> <fill-color>\n";
    constexpr inline auto CIRCLE_USAGE = "\tcircle <center x> <center y> <radius> <outline-color> "
                                         "<fill-color>\n";
    constexpr inline auto LINE_SEGMENT_USAGE = "\tls <start-point x> <start-point y> <end-point x> "
                                               "<end-point y> <outline-color>\n\n";
}

namespace ShapeMessages
{
    constexpr inline auto TRIANGLE_INVALID_ARGUMENT = "Invalid arguments count for constructing "
                                                      "triangle.\nUsage: triangle <coord x1> "
                                                      "<coord y1> <coord x2> <coord y2> "
                                                      "<coord x3> <coord y3> <outline-color> "
                                                      "<fill-color>\n";
    constexpr inline auto RECTANGLE_INVALID_ARGUMENT = "Invalid arguments count for constructing "
                                                       "rectangle.\nUsage: rectangle <left-top x> "
                                                       "<left-top y> <width> <height> <outline-color> "
                                                       "<fill-color>\n";
    constexpr inline auto CIRCLE_INVALID_ARGUMENT = "Invalid arguments count for constructing circle.\n"
                                                    "Usage: circle <center x> <center y> <radius> "
                                                    "<outline-color> <fill-color>\n";
    constexpr inline auto LINE_SEGMENT_INVALID_ARGUMENT = "Invalid arguments count for constructing line "
                                                          "segment.\nUsage: ls <start-point x> <start-point y> "
                                                          "<end-point x> <end-point y> <outline-color> \n";

    constexpr inline auto INVALID_COORD_ARGUMENT = " argument is invalid. Must be a number.\n";
    constexpr inline auto INVALID_COLOR_ARGUMENT = " argument is invalid. Must be a hex color\n";

    constexpr inline auto MIN_PERIMETER = "Shape with minimum perimeter:\n\n";
    constexpr inline auto MAX_AREA = "\nShape with maximum area:\n\n";
}

namespace MathConstants
{
    constexpr inline auto STOUL_BASE = 16;
    constexpr inline auto ACCEPTABLE_DELTA = 0.001;
}

namespace ArgumentConstants
{
    constexpr inline auto EXIT_CODE = "q";

    constexpr inline auto COLOR_SIZE = 6;
    constexpr inline auto COLOR_COUNT = 2;
    constexpr inline auto LS_COLOR_COUNT = 1;

    constexpr inline auto TRIANGLE_COUNT = 8;
    constexpr inline auto RECTANGLE_COUNT = 6;
    constexpr inline auto CIRCLE_COUNT = 5;
    constexpr inline auto LINE_SEGMENT_COUNT = 5;
}