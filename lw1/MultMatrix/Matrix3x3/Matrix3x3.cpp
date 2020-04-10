#include "Matrix3x3.h"
#include <iostream>
#include <vector>
#include <cmath>

Matrix3x3::Matrix3x3()
{
    // Initialize matrix3x3 with zeroes
    coefs.resize(Matrix3x3::SIZE, std::vector<float>(Matrix3x3::SIZE, 0));
}

void Matrix3x3::PrintMatrix()
{
    for (size_t row = 0; row != SIZE; row++)
    {
        for (size_t col = 0; col != SIZE; col++)
        {
            std::cout << coefs[row][col] << " ";
        }
        std::cout << std::endl;
    }
}