#pragma once

#include <FindMaxEx/FindMaxEx.h>
#include <fstream>

class FindMaxExController
{
public:
    FindMaxExController(std::istream& is, std::ostream& os);
    void ParseCommandLine();
    void ParseArgs(const std::string& args);

    void PrintSportsmanWithMaxHeight();
    void PrintSportsmanWithMaxWeight();

    bool IsSportsmenWereAdded();

private:
    static void VerifyProperties(const std::vector<std::string>& properties);
    static bool IsName(const std::string& name);
    static bool IsBodyParameter(const std::string& parameter);

    static bool ContainsCorrectFullNameProperties(std::vector<std::string> properties);
    static bool ContainsCorrectBodyProperties(std::vector<std::string> properties);

    template <typename Less>
    void PrintSportsmanWithMaxParameter(Less const& less);

    std::istream& m_input;
    std::ostream& m_output;
    std::vector<Sportsman> m_sportsmen;
};