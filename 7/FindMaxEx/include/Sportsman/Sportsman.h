#pragma once

#include <string>

constexpr auto SPORTSMAN_PROPERTIES_COUNT = 5;

struct FullName
{
    std::string first, patronym, last;
};

struct Sportsman
{
    FullName name;
    unsigned short height{}, weight{};
};