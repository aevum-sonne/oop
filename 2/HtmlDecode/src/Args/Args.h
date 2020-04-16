#pragma once

#include <string>
#include <optional>
#include <iostream>

class Args
{
public:
    std::string html;
    std::optional<Args> ParseArgs(int argc, const char * argv []);
};