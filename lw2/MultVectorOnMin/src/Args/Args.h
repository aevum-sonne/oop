#pragma once

#include "../src/VectorUtils/VectorUtils.h"
#include <iostream>
#include <vector>
#include <string>
#include <optional>

class Args
{
public:
    vector_t vector;
    std::optional<Args> ParseArgs(int argc, const char * argv []);
private:
    double currArg;
};