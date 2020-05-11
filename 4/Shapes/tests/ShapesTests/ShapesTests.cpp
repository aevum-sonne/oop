#define BOOST_TEST_MODULE ShapesTests

#include <Constants/Constants.h>
#include <Shapes/Triangle.h>
#include <Shapes/Rectangle.h>
#include <Shapes/Circle.h>
#include <Shapes/LineSegment.h>
#include <Point/Point.h>
#include <boost/test/unit_test.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <memory>

struct Triangle_
{
    const Point expectedVertex1 = {-10, 0};
    const Point expectedVertex2 = {0, 25};
    const Point expectedVertex3 = {30, 0};
    const std::uint32_t expectedOutline = std::stoul("D56851", nullptr, MathConstants::STOUL_BASE);
    const std::uint32_t expectedFill = std::stoul("50251C", nullptr, MathConstants::STOUL_BASE);

    const double expectedPerimeter = 105.977;
    const double expectedArea = 500.000;

    Triangle triangle;
    Triangle_()
            : triangle(expectedVertex1, expectedVertex2, expectedVertex3,
                       expectedOutline, expectedFill)
    {
    }
};

BOOST_FIXTURE_TEST_SUITE(TriangleSuite, Triangle_)
    BOOST_AUTO_TEST_CASE(is_correct_vertex1)
    {
        BOOST_CHECK_EQUAL(Triangle_::expectedVertex1, triangle.GetVertex1());
    }

    BOOST_AUTO_TEST_CASE(is_correct_vertex2)
    {
        BOOST_CHECK_EQUAL(Triangle_::expectedVertex2, triangle.GetVertex2());
    }

    BOOST_AUTO_TEST_CASE(is_correct_vertex3)
    {
        BOOST_CHECK_EQUAL(Triangle_::expectedVertex3, triangle.GetVertex3());
    }

    BOOST_AUTO_TEST_CASE(is_correct_outline_color)
    {
        BOOST_CHECK_EQUAL(Triangle_::expectedOutline, triangle.GetOutlineColor());
    }

    BOOST_AUTO_TEST_CASE(is_correct_fill_color)
    {
        BOOST_CHECK_EQUAL(Triangle_::expectedFill, triangle.GetFillColor());
    }

    BOOST_AUTO_TEST_CASE(is_correct_perimeter)
    {
        BOOST_TEST(std::fabs(Triangle_::expectedPerimeter - triangle.GetPerimeter())
                   < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_area)
    {
        BOOST_TEST(std::fabs(Triangle_::expectedArea - triangle.GetArea())
                   < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_info)
    {
        std::string expectedOutput = "Shape: Triangle\nArea: 500.000\nPerimeter: 105.977\nOutline color: #d56851\n"
                      "Fill color: #50251c\nVertex 1: (-10.000; 0.000)\nVertex 2: (0.000; 25.000)\n"
                      "Vertex 3: (30.000; 0.000)\n";

        BOOST_CHECK_EQUAL(expectedOutput, triangle.ToString());
    }

BOOST_AUTO_TEST_SUITE_END()

struct Rectangle_
{
    const Point expectedLeftTop = {-2.9, 10.33};
    const Point expectedRightBottom = {5.55, -2};
    const double expectedWidth = 8.45;
    const double expectedHeight = 12.33;
    const std::uint32_t expectedOutline = std::stoul("A28594", nullptr, MathConstants::STOUL_BASE);
    const std::uint32_t expectedFill = std::stoul("C94253", nullptr, MathConstants::STOUL_BASE);

    const double expectedPerimeter = 41.560;
    const double expectedArea = 104.188;

    Rectangle rectangle;
    Rectangle_()
        : rectangle(expectedLeftTop, expectedWidth, expectedHeight, expectedOutline, expectedFill)
    {
    }
};

BOOST_FIXTURE_TEST_SUITE(RectangleSuite, Rectangle_)
    BOOST_AUTO_TEST_CASE(is_correct_left_top)
    {
        BOOST_CHECK_EQUAL(Rectangle_::expectedLeftTop, rectangle.GetLeftTop());
    }

    BOOST_AUTO_TEST_CASE(is_correct_right_bottom)
    {
        BOOST_TEST(Rectangle_::expectedRightBottom - rectangle.GetRightBottom() < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_width)
    {
        BOOST_CHECK_EQUAL(Rectangle_::expectedWidth, rectangle.GetWidth());
    }

    BOOST_AUTO_TEST_CASE(is_correct_height)
    {
        BOOST_CHECK_EQUAL(Rectangle_::expectedHeight, rectangle.GetHeight());
    }

    BOOST_AUTO_TEST_CASE(is_correct_outline_color)
    {
        BOOST_CHECK_EQUAL(Rectangle_::expectedOutline, rectangle.GetOutlineColor());
    }

    BOOST_AUTO_TEST_CASE(is_correct_fill_color)
    {
        BOOST_CHECK_EQUAL(Rectangle_::expectedFill, rectangle.GetFillColor());
    }

    BOOST_AUTO_TEST_CASE(is_correct_perimeter)
    {
        BOOST_TEST(std::fabs(Rectangle_::expectedPerimeter - rectangle.GetPerimeter())
                   < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_area)
    {
        BOOST_TEST(std::fabs(Rectangle_::expectedArea - rectangle.GetArea())
                   < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_info)
    {
        std::string expectedOutput = "Shape: Rectangle\nArea: 104.188\nPerimeter: 41.560\nOutline color: #a28594\n"
                                     "Fill color: #c94253\nWidth: 8.450\nHeight: 12.330\nLeft top point: (-2.900; 10.330)"
                                     "\nRight bottom point: (5.550; -2.000)\n";

        BOOST_CHECK_EQUAL(expectedOutput, rectangle.ToString());
    }

BOOST_AUTO_TEST_SUITE_END()

struct Circle_
{
    const Point expectedCenter = {-2.9, 10.33};
    const double expectedRadius = 17.1;
    const std::uint32_t expectedOutline = std::stoul("F84932", nullptr, MathConstants::STOUL_BASE);
    const std::uint32_t expectedFill = std::stoul("D48442", nullptr, MathConstants::STOUL_BASE);

    const double expectedPerimeter = 107.442;
    const double expectedArea = 918.633;

    Circle circle;
    Circle_()
            : circle(expectedCenter, expectedRadius, expectedOutline, expectedFill)
    {
    }
};

BOOST_FIXTURE_TEST_SUITE(CircleSuite, Circle_)
    BOOST_AUTO_TEST_CASE(is_correct_center)
    {
        BOOST_CHECK_EQUAL(Circle_::expectedCenter, circle.GetCenter());
    }

    BOOST_AUTO_TEST_CASE(is_correct_radius)
    {
        BOOST_CHECK_EQUAL(Circle_::expectedRadius, circle.GetRadius());
    }

    BOOST_AUTO_TEST_CASE(is_correct_outline_color)
    {
        BOOST_CHECK_EQUAL(Circle_::expectedOutline, circle.GetOutlineColor());
    }

    BOOST_AUTO_TEST_CASE(is_correct_fill_color)
    {
        BOOST_CHECK_EQUAL(Circle_::expectedFill, circle.GetFillColor());
    }

    BOOST_AUTO_TEST_CASE(is_correct_perimeter)
    {
        BOOST_TEST(std::fabs(Circle_::expectedPerimeter - circle.GetPerimeter())
                   < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_area)
    {
        BOOST_TEST(std::fabs(Circle_::expectedArea - circle.GetArea())
                   < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_info)
    {
        std::string expectedOutput = "Shape: Circle\nArea: 918.633\nPerimeter: 107.442\nOutline color: #f84932\n"
                                     "Fill color: #d48442\nCenter point: (-2.900; 10.330)"
                                     "\nRadius: 17.100\n";

        BOOST_CHECK_EQUAL(expectedOutput, circle.ToString());
    }

BOOST_AUTO_TEST_SUITE_END()

struct LineSegment_
{
    const Point expectedStartPoint = {30, 40};
    const Point expectedEndPoint = {10, 20};
    const std::uint32_t expectedOutline = std::stoul("f00000", nullptr, MathConstants::STOUL_BASE);

    const double expectedPerimeter = 28.284;

    LineSegment lineSegment;
    LineSegment_()
                : lineSegment(expectedStartPoint, expectedEndPoint, expectedOutline)
    {
    }
};

BOOST_FIXTURE_TEST_SUITE(LineSegmentSuite, LineSegment_)
    BOOST_AUTO_TEST_CASE(is_correct_start_point)
    {
        BOOST_CHECK_EQUAL(LineSegment_::expectedStartPoint, lineSegment.GetStartPoint());
    }
    
    BOOST_AUTO_TEST_CASE(is_correct_end_point)
    {
        BOOST_CHECK_EQUAL(LineSegment_::expectedEndPoint, lineSegment.GetEndPoint());
    }

    BOOST_AUTO_TEST_CASE(is_correct_outline_color)
    {
        BOOST_CHECK_EQUAL(LineSegment_::expectedOutline, lineSegment.GetOutlineColor());
    }

    BOOST_AUTO_TEST_CASE(is_correct_perimeter)
    {
        std::cout << lineSegment.GetPerimeter() << std::endl;
        BOOST_TEST(std::fabs(LineSegment_::expectedPerimeter - lineSegment.GetPerimeter())
            < MathConstants::ACCEPTABLE_DELTA);
    }

    BOOST_AUTO_TEST_CASE(is_correct_info)
    {
        std::string expectedOutput = "Shape: Line Segment\nArea: 0.000\nPerimeter: 28.284\nOutline color: #f00000\n"
                                     "Start point: (30.000; 40.000)\nEnd point: (10.000; 20.000)\n";

        BOOST_CHECK_EQUAL(expectedOutput, lineSegment.ToString());
    }

BOOST_AUTO_TEST_SUITE_END()
