#include "Multiplier.h"
#include <iostream>
#include <string>
#include <fstream>

Matrix3x3::matrix_t Multiplier(Matrix3x3::matrix_t firstMatrix3x3, Matrix3x3::matrix_t secondMatrix)
{
    Matrix3x3 resultMatrix;
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

void ReadMatrixFromStream(std::ifstream& inStream, Matrix3x3& matrix3x3)
{
    float currCoef = 0;
    for (size_t row = 0; row != Matrix3x3::SIZE; row++)
    {
        for (size_t col = 0; col != Matrix3x3::SIZE; col++)
        {
            inStream >> currCoef;
            matrix3x3.coefs[row][col] = currCoef;
        }
    }

    inStream.close();
}

void WriteMatrixInStream(std::ofstream& outStream, Matrix3x3::matrix_t resultMatrix)
{
    std::ofstream fout(outputFileName);

    for (size_t row = 0; row != Matrix3x3::SIZE; row++)
    {
        for (size_t col = 0; col != Matrix3x3::SIZE; col++)
        {
            fout << resultMatrix[row][col] << separator;
        }

        fout << std::endl;
    }
}

Matrix3x3::matrix_t MultiplyMatricesFromFiles(std::string firstFileName, std::string secondFileName)
{
    std::ifstream firstFile(firstFileName);
    if (!firstFile)
    {
        throw std::runtime_error(firstFileOpenFailed);
    }

    std::ifstream secondFile(secondFileName);
    if (!secondFile)
    {
        throw std::runtime_error(secondFileOpenFailed);
    }

    Matrix3x3 firstMatrix, secondMatrix, resultMatrix;
    ReadMatrixFromStream(firstFile, firstMatrix); ReadMatrixFromStream(secondFile, secondMatrix);
    resultMatrix.coefs = Multiplier(firstMatrix.coefs, secondMatrix.coefs);

    return resultMatrix.coefs;
}