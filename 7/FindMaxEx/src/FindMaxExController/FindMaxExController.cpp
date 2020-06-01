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
    std::vector<std::string> properties;
    boost::split(properties, args, boost::is_any_of(" "));

    VerifyProperties(properties);

    FullName name {properties[0],
                   properties[1],
                   properties[2]};

    unsigned short height, weight;
    height = std::stoi(properties[3]);
    weight = std::stoi(properties[4]);

    Sportsman sportsman = {name, height, weight};
    m_sportsmen.push_back(sportsman);
}

void FindMaxExController::VerifyProperties(const std::vector<std::string>& properties)
{
    if (SPORTSMAN_PROPERTIES_COUNT != properties.size())
    {
        throw std::invalid_argument("Invalid arguments count.");
    }

    if (!ContainsCorrectFullNameProperties(properties))
    {
        throw std::invalid_argument("Invalid name argument.");
    }

    if (!ContainsCorrectBodyProperties(properties))
    {
        throw std::invalid_argument("Invalid body parameter argument (contains non-digit "
                                    "characters or negative).");
    }
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
    auto nameProperties = std::vector<std::string>(properties.begin(), properties.end() - 2);

    for (auto& p : nameProperties)
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
    auto bodyProperties = std::vector<std::string>(properties.begin() + 3, properties.end());

    for (auto& p : bodyProperties)
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
