#include "Args.h"

std::string Args::ToLowerCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return string;
}

bool ContainsLettersAndSpacesOnly(std::string string) {
    // Remove all spaces and make lower case
    string.erase(std::remove_if(string.begin(), string.end(), isspace), string.end());
    string = Args::ToLowerCase(string);

    if (string.length() == 0)
    {
        return false;
    }

    for (auto ch : string)
    {
        if (ch < 'a' or ch > 'z')
        {
            return false;
        }
    }

    return true;
}


std::optional<Args> Args::ParseArgs(std::string string)
{
    if (string.length() == 0)
    {
        return std::nullopt;
    }

    Args args;
    word = string;  // Word stores input string without lowercasing

    // Check if string contains only words
    if (!ContainsLettersAndSpacesOnly(word))
    {
        return std::nullopt;
    }

    return args;
}
