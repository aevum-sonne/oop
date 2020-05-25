#define BOOST_TEST_MODULE ComplexTests

#include "../src/Complex/Complex.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/optional.hpp>
#include <utility>

struct AdditionComplexPlusDoubleData
{
    std::vector<std::pair<Complex, double>> complexPlusDoubleTests {
            {Complex(1, 1), 10},
            {Complex(10, 10), 30},
            {Complex(10.5, 55.5), 0.5}
    };

    std::vector<Complex> complexPlusDoubleExpected {
            Complex(11, 1),
            Complex(40, 10),
            Complex(11, 55.5)
    };
};

struct AdditionComplexPlusComplexData
{
    std::vector<std::pair<Complex, Complex>> complexPlusComplexTests {
            {Complex(1, 1), Complex(2, 3)},
            {Complex(10, 10), Complex(0, 0)},
            {Complex(10.5, 55.5), Complex(10.5, 55.5)}
    };

    std::vector<Complex> complexPlusComplexExpected {
            Complex(3, 4),
            Complex(10, 10),
            Complex(21, 111)
    };
};

struct AdditionFixture : AdditionComplexPlusDoubleData, AdditionComplexPlusComplexData
{
    static void CheckAdditionComplexPlusDouble(Complex& expected, Complex& complex, double number)
    {
        BOOST_CHECK_EQUAL(expected, complex + number);
    }

    static void CheckAdditionInBothDirections(Complex& complex, double number)
    {
        BOOST_CHECK_EQUAL(complex + number, number + complex);
    }

    static void CheckAdditionComplexPlusComplex(Complex& expected, Complex& lhs, Complex& rhs)
    {
        BOOST_CHECK_EQUAL(expected, lhs + rhs);
    }
};

BOOST_FIXTURE_TEST_SUITE(complex_overload_binary_plus_operator, AdditionFixture)
    BOOST_AUTO_TEST_CASE(correct_complex_plus_double_result)
    {
        for (auto i = 0; i < complexPlusDoubleTests.size(); i++)
        {
            CheckAdditionComplexPlusDouble(complexPlusDoubleExpected[i], complexPlusDoubleTests[i].first,
                                           complexPlusDoubleTests[i].second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_addition_complex_and_double_in_both_directions)
    {
        for (auto test : complexPlusDoubleTests)
        {
            CheckAdditionInBothDirections(test.first, test.second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_complex_plus_complex_result)
    {
        for (auto i = 0; i < complexPlusComplexTests.size(); i++)
        {
            CheckAdditionComplexPlusComplex(complexPlusComplexExpected[i], complexPlusComplexTests[i].first,
                                            complexPlusComplexTests[i].second);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

struct SubtractionComplexMinusDoubleData
{
    std::vector<std::pair<Complex, double>> complexMinusDoubleTests {
            {Complex(5, 3),      2},
            {Complex(10, 10),    0},
            {Complex(0.5, 55.5), 30.5}
    };

    std::vector<Complex> complexMinusDoubleExpected {
            Complex(3, 3),
            Complex(10, 10),
            Complex(-30, 55.5)
    };
};

struct SubtractionComplexMinusComplexData
{
    std::vector<std::pair<Complex, Complex>> complexMinusComplexTests {
            {Complex(5, 3),      Complex(2, 3)},
            {Complex(10, 10),    Complex(0, 0)},
            {Complex(0.5, 55.5), Complex(100.5, 55.5)}
    };

    std::vector<Complex> complexMinusComplexExpected {
            Complex(3, 0),
            Complex(10, 10),
            Complex(-100, 0)
    };
};

struct SubtractionFixture : SubtractionComplexMinusDoubleData, SubtractionComplexMinusComplexData
{
    static void CheckSubtractionComplexMinusDouble(Complex& expected, Complex& complex, double& number)
    {
        BOOST_CHECK_EQUAL(expected, complex - number);
    }

    static void CheckSubtractionInBothDirections(Complex& complex, double number)
    {
        BOOST_CHECK_EQUAL(complex - number, -1 * (number - complex));
    }

    static void CheckSubtractionComplexMinusComplex(Complex& expected, Complex& lhs, Complex& rhs)
    {
        BOOST_CHECK_EQUAL(expected, lhs - rhs);
    }
};

BOOST_FIXTURE_TEST_SUITE(complex_overload_binary_minus_operator,  SubtractionFixture)
    BOOST_AUTO_TEST_CASE(correct_complex_minus_double_result)
    {
        for (int i = 0; i < complexMinusDoubleTests.size(); i++)
        {
            CheckSubtractionComplexMinusDouble(complexMinusDoubleExpected[i], complexMinusDoubleTests[i].first, complexMinusDoubleTests[i].second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_subtraction_complex_and_double_in_both_directions)
    {
        for (auto test : complexMinusDoubleTests)
        {
            CheckSubtractionInBothDirections(test.first, test.second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_complex_minus_complex_result)
    {
        for (int i = 0; i < complexMinusComplexTests.size(); i++)
        {
            CheckSubtractionComplexMinusComplex(complexMinusComplexExpected[i], complexMinusComplexTests[i].first, complexMinusComplexTests[i].second);
        }
   }
BOOST_AUTO_TEST_SUITE_END()

struct MultiplicationComplexOnComplexData
{
    std::vector<std::pair<Complex, Complex>> complexOnComplexTest {
            {Complex(6, 2),      Complex(19, 58)},
            {Complex(2, 101),    Complex(10, -100)},
            {Complex(2.3, 9.5), Complex(9.2, 22.2)}
    };

    std::vector<Complex> complexOnComplexExpected {
            Complex(-2, 386),
            Complex(10120, 810),
            Complex(-189.74, 138.46)
    };
};

struct MultiplicationComplexOnDoubleData
{
    std::vector<std::pair<Complex, double>> complexOnDoubleTest {
            {Complex(5, 3),      1},
            {Complex(10, 10),    2},
            {Complex(0.5, 55.5), 3}
    };

    std::vector<Complex> complexOnDoubleExpected {
            Complex(5, 3),
            Complex(20, 20),
            Complex(1.5, 166.5)
    };
};

struct MultiplicationFixture : MultiplicationComplexOnComplexData, MultiplicationComplexOnDoubleData
{
    static void CheckComplexOnDoubleMultiplication(Complex& expected, Complex& complex, double& number)
    {
        BOOST_CHECK_EQUAL(expected, complex * number);
    }

    static void CheckMultiplicationInBothDirectionsOnDouble(Complex& complex, double& number)
    {
        BOOST_CHECK_EQUAL(number * complex, complex * number);
    }

    static void CheckComplexOnComplexMultiplication(Complex& expected, Complex& complex1, Complex& complex2)
    {
        BOOST_CHECK_EQUAL(expected, complex1 * complex2);
    }
};

BOOST_FIXTURE_TEST_SUITE(complex_overload_binary_multiplication_operator,  MultiplicationFixture)
    BOOST_AUTO_TEST_CASE(correct_multiply_complex_on_double)
    {
        for (int i = 0; i < complexOnDoubleTest.size(); i++)
        {
            CheckComplexOnDoubleMultiplication(complexOnDoubleExpected[i], complexOnDoubleTest[i].first,
                                               complexOnDoubleTest[i].second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_multiply_complex_in_both_directions_on_double)
    {
        for (auto test : complexOnDoubleTest)
        {
            CheckMultiplicationInBothDirectionsOnDouble(test.first,test.second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_multiply_complex_on_complex)
    {
        for (int i = 0; i < complexOnComplexTest.size(); i++)
        {
            CheckComplexOnComplexMultiplication(complexOnComplexExpected[i], complexOnComplexTest[i].first,
                                                complexOnComplexTest[i].second);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

struct DivisionComplexOnComplexData
{
    std::vector<std::pair<Complex, Complex>> complexOnComplexTest {
            {Complex(10, 5),      Complex(2, 2)},
            {Complex(33, 33),    Complex(33, 33)},
            {Complex(400, 200), Complex(2, 2)}
    };

    std::vector<Complex> complexOnComplexExpected {
            Complex(3.75, -1.25),
            Complex(1, 0),
            Complex(150, -50)
    };
};

struct DivisionComplexOnDoubleData
{
    std::vector<std::pair<Complex, double>> complexOnDoubleTest {
            {Complex(10, 5), 2},
            {Complex(33, 33), 33},
            {Complex(400, 200), 2}
    };

    std::vector<Complex> complexOnDoubleExpected {
            Complex(5, 2.5),
            Complex(1, 1),
            Complex(200, 100)
    };
};

struct DivisionFixture : DivisionComplexOnComplexData, DivisionComplexOnDoubleData
{
    static void CheckComplexOnDoubleDivision(Complex& expected, Complex& complex, double& number)
    {
        BOOST_CHECK_EQUAL(expected, complex / number);
    }

    static void CheckDivisionInBothDirectionsOnDouble(Complex& complex, double& number)
    {
        BOOST_CHECK_EQUAL(number / complex, 1 / (complex / number));
    }

    static void CheckComplexOnComplexDivision(Complex& expected, Complex& complex1, Complex& complex2)
    {
        BOOST_CHECK_EQUAL(expected, complex1 / complex2);
    }
};

BOOST_FIXTURE_TEST_SUITE(complex_overload_binary_division_operator, DivisionFixture)
    BOOST_AUTO_TEST_CASE(correct_divide_complex_on_double)
    {
        for (int i = 0; i < complexOnDoubleTest.size(); i++)
        {
            CheckComplexOnDoubleDivision(complexOnDoubleExpected[i], complexOnDoubleTest[i].first,
                                               complexOnDoubleTest[i].second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_divide_complex_in_both_directions_on_double)
    {
        for (auto test : complexOnDoubleTest)
        {
            CheckDivisionInBothDirectionsOnDouble(test.first, test.second);
        }
    }

    BOOST_AUTO_TEST_CASE(correct_divide_complex_on_complex)
    {
        for (int i = 0; i < complexOnComplexTest.size(); i++)
        {
            CheckComplexOnComplexDivision(complexOnComplexExpected[i], complexOnComplexTest[i].first,
                                                complexOnComplexTest[i].second);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_unary_plus_operator)
    BOOST_AUTO_TEST_CASE(correct_unary_plus_complex)
    {
        Complex expected(11, 11);
        Complex complex(11, 11);

        BOOST_CHECK_EQUAL(expected, +complex);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_unary_minus_operator)
    BOOST_AUTO_TEST_CASE(correct_unary_minus_complex)
    {
        Complex expected(-11, -11);
        Complex complex(11, 11);

        BOOST_CHECK_EQUAL(expected, -complex);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_increment_operator)
    BOOST_AUTO_TEST_CASE(correct_increment_complex_plus_complex)
    {
        Complex expected(4, 2);
        Complex complex(2, 2);
        complex += Complex(2, 0);

        BOOST_CHECK_EQUAL(expected, complex);
    }

    BOOST_AUTO_TEST_CASE(correct_increment_complex_plus_double)
    {
        Complex expected(8, 1);
        Complex complex(6, 1);
        complex += 2;

        BOOST_CHECK_EQUAL(expected, complex);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_decrement_operator)
    BOOST_AUTO_TEST_CASE(correct_decrement_complex_minus_complex)
    {
        Complex expected(0, 2);
        Complex complex(2, 2);
        complex -= Complex(2, 0);

        BOOST_CHECK_EQUAL(expected, complex);
    }

    BOOST_AUTO_TEST_CASE(correct_decrement_complex_minus_double)
    {
        Complex expected(2, 3);
        Complex complex(5, 3);
        complex -= 3;

        BOOST_CHECK_EQUAL(expected, complex);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_multiplication_compound_assignment_operator)
    BOOST_AUTO_TEST_CASE(correct_multiply_complex_and_complex)
    {
        Complex expected(6, 0);
        Complex complex(3, 3);
        complex *= Complex(2, 0);

        BOOST_CHECK_EQUAL(expected, complex);
    }

    BOOST_AUTO_TEST_CASE(correct_multiply_complex_and_double)
    {
        Complex expected(50, 150);
        Complex complex(10, 30);
        complex *= 5;

        BOOST_CHECK_EQUAL(expected, complex);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_division_compound_assignment_operator)
    BOOST_AUTO_TEST_CASE(correct_divide_complex_and_complex)
    {
        Complex expected(1, 3);
        Complex complex(3, 3);
        complex /= Complex(3, 1);

        BOOST_CHECK_EQUAL(expected, complex);
    }

    BOOST_AUTO_TEST_CASE(correct_divide_complex_and_double)
    {
        Complex expected(2, 0.4);
        Complex complex(10, 2);
        complex /= 5;

        BOOST_CHECK_EQUAL(expected, complex);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_equal_operator)
    BOOST_AUTO_TEST_CASE(correct_check_equality_complex_and_complex)
    {
        Complex lhs(3, 4);
        Complex rhs(3, 4);

        BOOST_CHECK(lhs == rhs);
    }

    BOOST_AUTO_TEST_CASE(correct_check_equality_complex_and_double_rhs)
    {
        Complex lhs(33, 0);
        double rhs = 33;

        BOOST_CHECK(lhs == rhs);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_not_equal_operator)
    BOOST_AUTO_TEST_CASE(correct_check_non_equality_complex_and_complex)
    {
        Complex lhs(3, 4);
        Complex rhs(33, 4);

        BOOST_CHECK(lhs != rhs);
    }

    BOOST_AUTO_TEST_CASE(correct_check_non_equality_complex_and_double_rhs)
    {
        Complex lhs(33, 2);
        double rhs = 33;

        BOOST_CHECK(lhs != rhs);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_out_stream_operator)
    BOOST_AUTO_TEST_CASE(correct_out_complex_in_stream)
    {
        std::string expected = "2 + 2i";
        Complex complex(2, 2);

        std::stringstream expectedStream(expected);
        std::stringstream complexStream;
        complexStream << complex;

        BOOST_CHECK_EQUAL(expectedStream.str(), complexStream.str());
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(complex_overload_in_stream_operator)
    BOOST_AUTO_TEST_CASE(correct_put_complex_in_stream)
    {
        Complex complex;
        std::istringstream complexStream("2 2");
        complexStream >> complex;

        BOOST_CHECK_EQUAL("2 2", complexStream.str());
    }
BOOST_AUTO_TEST_SUITE_END()
