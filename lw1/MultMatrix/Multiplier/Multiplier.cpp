#include "Multiplier.h"
#include <iostream>

Matrix3x3::matrix_t Multiplier(Matrix3x3::matrix_t firstMatrix3x3, Matrix3x3::matrix_t secondMatrix)
{
    Matrix3x3 resultMatrix;
    float sum;

    for (size_t row = 0; row != Matrix3x3::SIZE; row++)
    {
        for (size_t col = 0; col != Matrix3x3::SIZE; col++)
        {
            resultMatrix.coefs[row][col] = 0;
            for (size_t k = 0; k != Matrix3x3::SIZE; k++)
            {
                resultMatrix.coefs[row][col] += firstMatrix3x3[row][k] * secondMatrix[k][col];
            }
        }
    }
    
    return resultMatrix.coefs;
}