#pragma once

#include "../Matrix3x3/Matrix3x3.h"

const std::string invalidArgumentsCount = "Invalid number of arguments. "
                                          "Using: ./MultMatrix matrix1.txt matrix2.txt";
const std::string firstFileOpenFailed = "Failed to open first file.";
const std::string secondFileOpenFailed = "Failed to open first file.";
const std::string separator = " ";
const std::string outputFileName = "output.txt";

void ReadMatrixFromStream(std::ifstream& inStream, Matrix3x3& matrix3x3);
void WriteMatrixInStream(std::ofstream& outStream, Matrix3x3::matrix_t resultMatrix);
Matrix3x3::matrix_t Multiplier(Matrix3x3::matrix_t firstMatrix3x3, Matrix3x3::matrix_t secondMatrix);
Matrix3x3::matrix_t MultiplyMatricesFromFiles(std::string firstFileName, std::string secondFileName);