#include "Tests.h"

TEST_CASE("Empty string")
{
    testWord = std::string();
    Args args;

    REQUIRE(args.ParseArgs(testWord) == std::nullopt);
}

TEST_CASE("Word contains digits symbols")
{
    testWord = "apple123";
    Args args;

    REQUIRE(args.ParseArgs(testWord) == std::nullopt);
}

TEST_CASE("Word contains special symbols")
{
    testWord = "/,ap@@ple";
    Args args;

    REQUIRE(args.ParseArgs(testWord) == std::nullopt);
}

TEST_CASE("Word in dictionary")
{
    testWord = "apple";
    expectedTranslation = "яблоко";
    MiniDictionary miniDict;
    resultTranslation = MiniDictionary::GetTranslation(testWord, miniDict.values);

    REQUIRE(expectedTranslation == resultTranslation);
}

TEST_CASE("Word (upper case) in dictionary")
{
    testWord = "APPLE";
    expectedTranslation = "яблоко";
    MiniDictionary miniDict;
    resultTranslation = MiniDictionary::GetTranslation(testWord, miniDict.values);

    REQUIRE(resultTranslation == expectedTranslation);
}

TEST_CASE("Word (different case) in dictionary")
{
    testWord = "ApPLe";
    expectedTranslation = "яблоко";
    MiniDictionary miniDict;
    resultTranslation = MiniDictionary::GetTranslation(testWord, miniDict.values);

    REQUIRE(expectedTranslation == resultTranslation);
}

TEST_CASE("Phrase in dictionary")
{
    testWord = "The Red Square";
    expectedTranslation = "Красная Площадь";
    MiniDictionary miniDict;
    resultTranslation = MiniDictionary::GetTranslation(testWord, miniDict.values);

    REQUIRE(expectedTranslation == resultTranslation);
}

TEST_CASE("Phrase (upper case) in dictionary")
{
    testWord = "THE RED SQUARE";
    expectedTranslation = "Красная Площадь";
    MiniDictionary miniDict;
    resultTranslation = MiniDictionary::GetTranslation(testWord, miniDict.values);

    REQUIRE(expectedTranslation == resultTranslation);
}

TEST_CASE("Phrase (different case) in dictionary")
{
    testWord = "ThE rED SquARe";
    expectedTranslation = "Красная Площадь";
    MiniDictionary miniDict;
    resultTranslation = MiniDictionary::GetTranslation(testWord, miniDict.values);

    REQUIRE(expectedTranslation == resultTranslation);
}

TEST_CASE("Word isn't in dictionary")
{
    testWord = "not in dict";
    expectedTranslation = std::string();
    MiniDictionary miniDict;
    resultTranslation = MiniDictionary::GetTranslation(testWord, miniDict.values);

    REQUIRE(expectedTranslation == resultTranslation);
}