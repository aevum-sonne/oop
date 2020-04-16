#pragma once

#include <iostream>
#include <optional>
#include <algorithm>
#include <cctype>
#include <string>

class Args
{
public:
    std::optional<Args> ParseArgs(std::string string);
    std::string word, translation;
    static std::string ToLowerCase(std::string string);
};