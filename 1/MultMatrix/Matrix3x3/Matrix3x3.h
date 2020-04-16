#pragma once

#include <iostream>
#include <vector>
#include <string>

class Matrix3x3
{
public:
    using matrix_t = std::vector<std::vector<float> >;
    const static size_t SIZE = 3;
    Matrix3x3();
    void PrintMatrix();
    matrix_t coefs;
};