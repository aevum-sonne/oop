#define BOOST_TEST_MODULE FindMaxExTests

#include <FindMaxExController/FindMaxExController.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(verify_sportsman_argument_parsing)
    FindMaxExController controller(std::cin, std::cout);

    BOOST_AUTO_TEST_SUITE(handle_correct_input_values)
        BOOST_AUTO_TEST_CASE(correct_parameters)
        {
            std::string str1 = "Ivan Ivanovich Lapshin 170 70";
            std::string str2 = "Ivan Ivanovich Ivanov 160 90";

            BOOST_CHECK_NO_THROW(controller.ParseArgs(str1));
            BOOST_CHECK_NO_THROW(controller.ParseArgs(str2));
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(handle_incorrect_input_values)
        BOOST_AUTO_TEST_CASE(empty_input)
        {
            std::string inString = std::string();

            BOOST_CHECK_THROW(controller.ParseArgs(inString), std::invalid_argument);
        }

        BOOST_AUTO_TEST_CASE(non_digit_body_parameters)
        {
            std::string inString = "Ivan Ivanovich Lapshin 17h0 ffffff";

            BOOST_CHECK_THROW(controller.ParseArgs(inString), std::invalid_argument);
        }

        BOOST_AUTO_TEST_CASE(non_letter_name_parameters)
        {
            std::string inString = "1@3 43///43 !!!!!! # @@191991";

            BOOST_CHECK_THROW(controller.ParseArgs(inString), std::invalid_argument);
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(find_max_height_weight)
    BOOST_AUTO_TEST_CASE(find_correct_max_height)
    {
        std::stringstream out;
        FindMaxExController controller(std::cin, out);

        std::string expected = "Sportsman with max height:\nIvan Ivanovich Lapshin\n";
        std::string str1 = "Ivan Ivanovich Lapshin 170 70";
        std::string str2 = "Ivan Ivanovich Ivanov 160 90";

        controller.ParseArgs(str1);
        controller.ParseArgs(str2);
        controller.PrintSportsmanWithMaxHeight();

        BOOST_CHECK_EQUAL(expected, out.str());

        expected += "Sportsman with max height:\nIvan Ivanovich Buyanov\n";
        std::string str3 = "Ivan Ivanovich Buyanov 200 120";

        controller.ParseArgs(str3);
        controller.PrintSportsmanWithMaxHeight();

        BOOST_CHECK_EQUAL(expected, out.str());
    }

    BOOST_AUTO_TEST_CASE(find_correct_max_weight)
    {
        std::stringstream out;
        FindMaxExController controller(std::cin, out);

        std::string expected = "Sportsman with max weight:\nIvan Ivanovich Ivanov\n";
        std::string str1 = "Ivan Ivanovich Lapshin 170 70";
        std::string str2 = "Ivan Ivanovich Ivanov 160 90";

        controller.ParseArgs(str1);
        controller.ParseArgs(str2);
        controller.PrintSportsmanWithMaxWeight();

        BOOST_CHECK_EQUAL(expected, out.str());

        expected += "Sportsman with max weight:\nIvan Ivanovich Buyanov\n";
        std::string str3 = "Ivan Ivanovich Buyanov 200 120";

        controller.ParseArgs(str3);
        controller.PrintSportsmanWithMaxWeight();

        BOOST_CHECK_EQUAL(expected, out.str());
    }
BOOST_AUTO_TEST_SUITE_END()
