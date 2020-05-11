#define BOOST_TEST_MODULE ShapesControllerTests

#include <Constants/Constants.h>
#include <ShapesController/ShapesController.h>
#include <boost/test/unit_test.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <memory>

struct ShapesControllerDependencies
{
    std::stringstream input;
    std::stringstream output;
};

struct ShapesControllerFixture: ShapesControllerDependencies
{
    ShapesController shapesController;

    ShapesControllerFixture()
                        : shapesController(input, output)
    {
    }

    void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput)
    {
        output = std::stringstream();
        input = std::stringstream();

        BOOST_CHECK(input << command);
        BOOST_CHECK(shapesController.HandleCommand());
        BOOST_CHECK(input.eof());
        BOOST_CHECK_EQUAL(output.str(), expectedOutput);
    }
};

BOOST_FIXTURE_TEST_SUITE(ShapesControllerIsColor, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(is_hex_color_correct_color)
    {
        std::string color1 = "A85893";
        std::string color2 = "000000";
        std::string color3 = "FFFFFF";

        BOOST_CHECK(shapesController.IsColor(color1));
        BOOST_CHECK(shapesController.IsColor(color2));
        BOOST_CHECK(shapesController.IsColor(color3));
    }

    BOOST_AUTO_TEST_CASE(is_hex_color_empty_color)
    {
        std::string color = std::string();

        BOOST_CHECK(!shapesController.IsColor(color));
    }

    BOOST_AUTO_TEST_CASE(is_hex_color_incorrect_size_color)
    {
        std::string color = "589";

        BOOST_CHECK(!shapesController.IsColor(color));
    }

    BOOST_AUTO_TEST_CASE(is_hex_color_incorrect_characters)
    {
        std::string color = "X454LO";

        BOOST_CHECK(!shapesController.IsColor(color));
    }

    BOOST_AUTO_TEST_CASE(is_hex_color_with_symbols_or_punctuation)
    {
        std::string color1 = "/,..][@@";
        std::string color2 = "~.#$&%*";
        std::string color3 = "######";

        BOOST_CHECK(!shapesController.IsColor(color1));
        BOOST_CHECK(!shapesController.IsColor(color2));
        BOOST_CHECK(!shapesController.IsColor(color3));
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShapesControllerIsDouble, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(is_double_correct_double)
    {
        std::string d1 = "584.232";
        std::string d2 = "6779.58393";
        std::string d3 = "0.348";

        BOOST_CHECK(shapesController.IsDouble(d1));
        BOOST_CHECK(shapesController.IsDouble(d2));
        BOOST_CHECK(shapesController.IsDouble(d3));
    }

    BOOST_AUTO_TEST_CASE(is_double_empty_string)
    {
        std::string d = std::string();

        BOOST_CHECK(!shapesController.IsDouble(d));
    }

    BOOST_AUTO_TEST_CASE(is_double_no_digits_before_dot)
    {
        std::string d1 = ".001";
        std::string d2 = ".543";
        std::string d3 = ".";

        BOOST_CHECK(!shapesController.IsDouble(d1));
        BOOST_CHECK(!shapesController.IsDouble(d2));
        BOOST_CHECK(!shapesController.IsDouble(d3));

    }

    BOOST_AUTO_TEST_CASE(is_double_digits_with_non_digit_characters)
    {
        std::string d1 = "D@I..giT.5859";
        std::string d2 = "abcdef1g";
        std::string d3 = "////343.23";

        BOOST_CHECK(!shapesController.IsDouble(d1));
        BOOST_CHECK(!shapesController.IsDouble(d2));
        BOOST_CHECK(!shapesController.IsDouble(d3));
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShapesControllerHandleTriangle, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(can_handle_command_with_no_arguments)
    {
        VerifyCommandHandling("triangle", ShapeMessages::TRIANGLE_INVALID_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_command_with_correct_arguments)
    {
        VerifyCommandHandling("triangle -10 0 0 25 30 0 D56851 50251C", std::string());
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_vertex_argument)
    {
        VerifyCommandHandling("triangle -1A F 0 2X5 30 0 D56851 50251C", std::string("1")
            + ShapeMessages::INVALID_COORD_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_color_argument)
    {
        VerifyCommandHandling("triangle -10 0 0 25 30 0 X3443 ZZZZZ",
                std::string("7") + ShapeMessages::INVALID_COLOR_ARGUMENT);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShapesControllerHandleRectangle, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(can_handle_command_with_no_arguments)
    {
        VerifyCommandHandling("rectangle", ShapeMessages::RECTANGLE_INVALID_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_command_with_correct_arguments)
    {
        VerifyCommandHandling("rectangle -2.9 10.33 8.45 12.33 A28594 C94253", std::string());
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_point_argument)
    {
        VerifyCommandHandling("rectangle -FFFFFF 10.33 8.45 12.33 A28594 C94253", std::string("1")
            + ShapeMessages::INVALID_COORD_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_color_argument)
    {
        VerifyCommandHandling("rectangle -2.9 10.33 8.45 12.33 @@@@ C94253",
                std::string("5") + ShapeMessages::INVALID_COLOR_ARGUMENT);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShapesControllerHandleCircle, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(can_handle_command_with_no_arguments)
    {
        VerifyCommandHandling("circle", ShapeMessages::CIRCLE_INVALID_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_command_with_correct_arguments)
    {
        VerifyCommandHandling("circle -2.9 10.33 17.1 A28594 C94253", std::string());
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_point_argument)
    {
        VerifyCommandHandling("circle -MX.9 10.33 FF332 A28594 C94253", std::string("1")
            + ShapeMessages::INVALID_COORD_ARGUMENT);
        VerifyCommandHandling("circle -2.9 .33 FF332 A28594 C94253", std::string("2")
                                                                        + ShapeMessages::INVALID_COORD_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_color_argument)
    {
        VerifyCommandHandling("circle -2.9 10.33 17.1 ####fdfdd C94253",
                std::string("4") + ShapeMessages::INVALID_COLOR_ARGUMENT);
        VerifyCommandHandling("circle -2.9 10.33 17.1 A28594 PPPP@@@",
                              std::string("5") + ShapeMessages::INVALID_COLOR_ARGUMENT);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShapesControllerHandleLineSegment, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(can_handle_command_with_no_arguments)
    {
        VerifyCommandHandling("ls", ShapeMessages::LINE_SEGMENT_INVALID_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_command_with_correct_arguments)
    {
        VerifyCommandHandling("ls 30 40 10 20 000000", std::string());
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_point_argument)
    {
        VerifyCommandHandling("ls .. 40 10 20 000000",
                std::string("1") + ShapeMessages::INVALID_COORD_ARGUMENT);
        VerifyCommandHandling("ls 30 xxxxxxxxxx 10 20 000000",
                std::string("2") + ShapeMessages::INVALID_COORD_ARGUMENT);
    }

    BOOST_AUTO_TEST_CASE(can_handle_error_with_non_correct_color_argument)
    {
        VerifyCommandHandling("ls 30 40 10 20 #",
                std::string("5") + ShapeMessages::INVALID_COLOR_ARGUMENT);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShapesControllerPrintShapeWithMinimumPerimeter, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(handle_correct_min_shape_no_shapes)
    {
        std::string expectedOutput = std::string();

        ShapesController shapesControllerMinPerimeter(input, output);

        shapesControllerMinPerimeter.HandleCommand();
        shapesControllerMinPerimeter.PrintShapeWithMinimumPerimeter();

        BOOST_CHECK_EQUAL(expectedOutput, output.str());
    }

    BOOST_AUTO_TEST_CASE(print_correct_min_shape_one_shape)
    {
        std::stringstream ss;

        ss << ShapeMessages::MIN_PERIMETER;
        ss << std::fixed << std::setprecision(3);
        ss << "Shape: Triangle" << std::endl;
        ss << "Area: " << 500.000 << std::endl;
        ss << "Perimeter: " << 105.977 << std::endl;
        ss << "Outline color: #" << "d56851" << std::endl;
        ss << "Fill color: #" << "50251c" << std::endl;
        ss << "Vertex 1: " << "(-10.000; 0.000)" << std::endl;
        ss << "Vertex 2: " << "(0.000; 25.000)" << std::endl;
        ss << "Vertex 3: " << "(30.000; 0.000)" << std::endl;

        std::string expectedOutput = ss.str();

        ShapesController shapesControllerMinPerimeter(input, output);
        std::string command = "triangle -10 0 0 25 30 0 d56851 50251c";
        input << command;

        shapesControllerMinPerimeter.HandleCommand();
        shapesControllerMinPerimeter.PrintShapeWithMinimumPerimeter();

        BOOST_CHECK_EQUAL(expectedOutput, output.str());
    }

    BOOST_AUTO_TEST_CASE(print_correct_min_shape_several_shapes)
    {
        std::stringstream ss;

        ss << ShapeMessages::MIN_PERIMETER;
        ss << std::fixed << std::setprecision(3);
        ss << "Shape: Triangle" << std::endl;
        ss << "Area: " << 500.000 << std::endl;
        ss << "Perimeter: " << 105.977 << std::endl;
        ss << "Outline color: #" << "d56851" << std::endl;
        ss << "Fill color: #" << "50251c" << std::endl;
        ss << "Vertex 1: " << "(-10.000; 0.000)" << std::endl;
        ss << "Vertex 2: " << "(0.000; 25.000)" << std::endl;
        ss << "Vertex 3: " << "(30.000; 0.000)" << std::endl;

        std::string expectedOutput = ss.str();

        ShapesController shapesControllerMinPerimeter(input, output);
        std::string command = "triangle -10 0 0 25 30 0 d56851 50251c";
        input << command;
        shapesControllerMinPerimeter.HandleCommand();

        command = "rectangle -2.9 10.33 5.55 -2 8.45 12.33 a28594 c94253";
        input << command;
        shapesControllerMinPerimeter.HandleCommand();

        command = "ls 30 40 10 20 000000";
        input << command;
        shapesControllerMinPerimeter.HandleCommand();

        shapesControllerMinPerimeter.PrintShapeWithMinimumPerimeter();

        BOOST_CHECK_EQUAL(expectedOutput, output.str());
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ShapesControllerPrintShapeWithMaximumArea, ShapesControllerFixture)
    BOOST_AUTO_TEST_CASE(handle_correct_max_shape_no_shapes)
    {
        std::string expectedOutput = std::string();

        ShapesController shapesControllerMaxArea(input, output);

        shapesControllerMaxArea.HandleCommand();
        shapesControllerMaxArea.PrintShapeWithMaximumArea();

        BOOST_CHECK_EQUAL(expectedOutput, output.str());
    }

    BOOST_AUTO_TEST_CASE(print_correct_max_shape_one_shape)
    {
        std::stringstream ss;

        ss << ShapeMessages::MAX_AREA;
        ss << std::fixed << std::setprecision(3);
        ss << "Shape: Triangle" << std::endl;
        ss << "Area: " << 500.000 << std::endl;
        ss << "Perimeter: " << 105.977 << std::endl;
        ss << "Outline color: #" << "d56851" << std::endl;
        ss << "Fill color: #" << "50251c" << std::endl;
        ss << "Vertex 1: " << "(-10.000; 0.000)" << std::endl;
        ss << "Vertex 2: " << "(0.000; 25.000)" << std::endl;
        ss << "Vertex 3: " << "(30.000; 0.000)" << std::endl;

        std::string expectedOutput = ss.str();

        ShapesController shapesControllerMaxArea(input, output);
        std::string command = "triangle -10 0 0 25 30 0 d56851 50251c";
        input << command;

        shapesControllerMaxArea.HandleCommand();
        shapesControllerMaxArea.PrintShapeWithMaximumArea();

        BOOST_CHECK_EQUAL(expectedOutput, output.str());
    }

    BOOST_AUTO_TEST_CASE(print_correct_max_shape_several_shapes)
    {
        std::stringstream ss;

        ss << ShapeMessages::MAX_AREA;
        ss << std::fixed << std::setprecision(3);
        ss << "Shape: Triangle" << std::endl;
        ss << "Area: " << 500.000 << std::endl;
        ss << "Perimeter: " << 105.977 << std::endl;
        ss << "Outline color: #" << "d56851" << std::endl;
        ss << "Fill color: #" << "50251c" << std::endl;
        ss << "Vertex 1: " << "(-10.000; 0.000)" << std::endl;
        ss << "Vertex 2: " << "(0.000; 25.000)" << std::endl;
        ss << "Vertex 3: " << "(30.000; 0.000)" << std::endl;

        std::string expectedOutput = ss.str();

        ShapesController shapesControllerMaxArea(input, output);
        std::string command = "triangle -10 0 0 25 30 0 d56851 50251c";
        input << command;
        shapesControllerMaxArea.HandleCommand();

        command = "rectangle -2.9 10.33 5.55 -2 8.45 12.33 a28594 c94253";
        input << command;
        shapesControllerMaxArea.HandleCommand();

        command = "ls 30 40 10 20 000000";
        input << command;
        shapesControllerMaxArea.HandleCommand();

        shapesControllerMaxArea.PrintShapeWithMaximumArea();

        BOOST_CHECK_EQUAL(expectedOutput, output.str());
    }

BOOST_AUTO_TEST_SUITE_END()