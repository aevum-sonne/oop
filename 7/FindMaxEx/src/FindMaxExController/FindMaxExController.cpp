#include <FindMaxExController/FindMaxExController.h>
#include <boost/algorithm/string.hpp>

FindMaxExController::FindMaxExController(std::istream& is, std::ostream& os)
        : m_input(is)
        , m_output(os)
{
}

void FindMaxExController::ParseCommandLine()
{
    std::string line;

    while (getline(m_input, line) && line != "q")
    {
        try
        {
            ParseArgs(line);
        }
        catch (const std::exception& e)
        {
            m_output << e.what() << std::endl;
        }
    }
}

void FindMaxExController::ParseArgs(const std::string& args)
{
    std::vector<std::string> sportsmanProperties;
    boost::split(sportsmanProperties, args, boost::is_any_of(" "));

    if (SPORTSMAN_PROPERTIES_COUNT != sportsmanProperties.size())
    {
        throw std::invalid_argument("Invalid arguments count.");
    }

    auto nameProperties = std::vector<std::string>(sportsmanProperties.begin(),
            sportsmanProperties.end() - 2);

    if (!ContainsCorrectFullNameProperties(nameProperties))
    {
        throw std::invalid_argument("Invalid name argument.");
    }

    auto bodyProperties = std::vector<std::string>(sportsmanProperties.begin() + 3,
            sportsmanProperties.end());

    if (!ContainsCorrectBodyProperties(bodyProperties))
    {
        throw std::invalid_argument("Invalid body parameter argument (contains non-digit "
                                    "characters or negative).");
    }

    FullName name {sportsmanProperties[0],
                   sportsmanProperties[1],
                   sportsmanProperties[2]};

    unsigned short height, weight;
    try
    {
        height = std::stoi(sportsmanProperties[3]);
        weight = std::stoi(sportsmanProperties[4]);
    }
    catch (const std::exception& e)
    {
        throw std::invalid_argument("Invalid body parameter argument (too big value).");
    }

    Sportsman sportsman = {name, height, weight};
    m_sportsmen.push_back(sportsman);
}

bool FindMaxExController::IsName(const std::string& name)
{
    return std::all_of(name.begin(), name.end(), [](unsigned char c){return std::isalpha(c);});
}

bool FindMaxExController::IsBodyParameter(const std::string& parameter)
{
    return std::all_of(parameter.begin(), parameter.end(), ::isdigit);
}

bool FindMaxExController::ContainsCorrectFullNameProperties(std::vector<std::string> properties)
{
    for (auto& p : properties)
    {
        if (!IsName(p))
        {
            return false;
        }
    }

    return true;
}

bool FindMaxExController::ContainsCorrectBodyProperties(std::vector<std::string> properties)
{
    for (auto& p : properties)
    {
        if (!IsBodyParameter(p))
        {
            return false;
        }
    }

    return true;
}

template<typename Less>
void FindMaxExController::PrintSportsmanWithMaxParameter(Less const& less)
{
    Sportsman max;
    FindMax(m_sportsmen, max, less);

    m_output << max.name.first << " " << max.name.patronym << " " << max.name.last << std::endl;
}

void FindMaxExController::PrintSportsmanWithMaxHeight()
{
    m_output << "Sportsman with max height:" << std::endl;
    PrintSportsmanWithMaxParameter(LessHeight<Sportsman>());
}

void FindMaxExController::PrintSportsmanWithMaxWeight()
{
    m_output << "Sportsman with max weight:" << std::endl;
    PrintSportsmanWithMaxParameter(LessWeight<Sportsman>());
}

bool FindMaxExController::IsSportsmenWereAdded()
{
    return !m_sportsmen.empty();
}
