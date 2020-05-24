#include "Tests.h"

TEST_CASE("Empty stream")
{
    const char *stream[] = {
            NULL
    };
    Args args;

    REQUIRE(args.ParseArgs(1, stream) == std::nullopt);
}

TEST_CASE("Args isn't a numbers")
{
    const char *stream[] = {
            EXECUTABLE.c_str(),
            "DJS.29A",
            "...",
            "34A",
            NULL
    };
    Args args;

    REQUIRE(args.ParseArgs(5, stream) == std::nullopt);
}

TEST_CASE("Correct args double type")
{
    const char *stream[] = {
            EXECUTABLE.c_str(),
            "7834.29",
            "8202.1",
            "34.002",
            "60.238"
    };
    expectedVector = {7834.29, 8202.1, 34.002, 60.238};
    Args args;
    args.ParseArgs(5, stream);

    REQUIRE(args.vector == expectedVector);
}

TEST_CASE("Empty vector <>")
{
    expectedVector = {};
    testVector = {};
    resultVector = MultVectorOnMin(testVector);

    REQUIRE(resultVector == expectedVector);
}

TEST_CASE("Unit vector <1, 1, 1, 1>")
{
    expectedVector = {1, 1, 1, 1};
    testVector = {1, 1, 1, 1};
    resultVector = MultVectorOnMin(testVector);

    REQUIRE(resultVector == expectedVector);
}

TEST_CASE("Vector of double with zero <5512.535, 235.854, 0, 54.21>")
{
    expectedVector = {0, 0, 0, 0};
    testVector = {5512.535, 235.854, 0, 54.21};
    resultVector = MultVectorOnMin(testVector);

    REQUIRE(resultVector == expectedVector);
}

TEST_CASE("Vector of double <495.125, 8433.334, 611.2, 31.02>")
{
    expectedVector = {15358.778, 261602.021, 18959.424, 962.24};
    testVector = {495.125, 8433.334, 611.2, 31.02};
    resultVector = MultVectorOnMin(testVector);

    REQUIRE(resultVector == expectedVector);
}

TEST_CASE("Ascending sort")
{
    expectedVector = {34.0, 45.34, 54.68, 458.34, 982.002};
    testVector = {45.34, 458.34, 982.002, 34, 54.68};
    resultVector = SortVector(testVector);

    REQUIRE(resultVector == expectedVector);
}

TEST_CASE("3 zeroes")
{
    expectedVector = {0, 0, 0};
    testVector = {0, 0, 0};
    resultVector = SortVector(testVector);

    REQUIRE(resultVector == expectedVector);
}