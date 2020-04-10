#include "Multiplier/Multiplier.h"
#include "Matrix3x3/Matrix3x3.h"
#include "Exception/Exception.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string SEPARATOR = " ";
const std::string OUTPUT_FILE = "output.txt";
const int NUM_OF_ARGS = 3;

void ReadMatrixFromFile(std::string filename, Matrix3x3 &matrix3x3)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << Exception(INPUT_OPEN_FAILED).GetError() << std::endl;
        throw Exception(INPUT_OPEN_FAILED);
    }

    float currCoef = 0;
    for (size_t row = 0; row != Matrix3x3::SIZE; row++)
    {
        for (size_t col = 0; col != Matrix3x3::SIZE; col++)
        {
            fin >> currCoef;
            matrix3x3.coefs[row][col] = currCoef;
        }
    }

    fin.close();
}

void WriteMatrixInFile(Matrix3x3::matrix_t resultMatrix)
{
    std::ofstream fout(OUTPUT_FILE);

    for (size_t row = 0; row != Matrix3x3::SIZE; row++)
    {
        for (size_t col = 0; col != Matrix3x3::SIZE; col++)
        {
            fout << resultMatrix[row][col] << SEPARATOR;
        }
        fout << std::endl;
    }
}

int main(int argc, const char * argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        std::cout << Exception(ARGC_COUNT).GetError() << std::endl;
        throw Exception(ARGC_COUNT);
    }

    // Read 2 matrices from file and initialize result matrix
    Matrix3x3 firstMatrix3x3;
    ReadMatrixFromFile(argv[1], firstMatrix3x3);
    Matrix3x3 secondMatrix3x3;
    ReadMatrixFromFile(argv[2], secondMatrix3x3);
    Matrix3x3 resultMatrix3x3;

    // Multiply and print the result
    resultMatrix3x3.coefs = Multiplier(firstMatrix3x3.coefs, secondMatrix3x3.coefs);
    resultMatrix3x3.PrintMatrix();
    // Write matrix in file for tests
    WriteMatrixInFile(resultMatrix3x3.coefs);
    return 0;
}