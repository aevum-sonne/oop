#pragma once

#include "Sportsman/Sportsman.h"

template <typename T>
struct Less
{
    bool operator() (const T& x, const T& y) const
    {
        return x < y;
    }
};

template <typename T>
struct LessWeight
{
    bool operator() (const T& x, const T& y)
    {
        return x.weight < y.weight;
    }
};

template <typename T>
struct LessHeight
{
    bool operator() (const T& x, const T& y)
    {
        return x.height < y.height;
    }
};