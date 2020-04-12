#include "Multiplier/Multiplier.h"
#include "Matrix3x3/Matrix3x3.h"
#include <string>
#include <fstream>

const int numberOfArgs = 3;

int main(int argc, const char * argv[])
{
    if (argc != numberOfArgs)
    {
        throw std::runtime_error(invalidArgumentsCount);
    }

    // Get and print result of multiplication of 2 matrices from files
    Matrix3x3 resultMatrix3x3;
    resultMatrix3x3.coefs = MultiplyMatricesFromFiles(argv[1], argv[2]);
    resultMatrix3x3.PrintMatrix();

    // Write matrix for unit tests
    std::ofstream output(outputFileName);
    WriteMatrixInStream(output, resultMatrix3x3.coefs);

    return 0;
}