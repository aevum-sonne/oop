// #pragma once
#include <string>

// Error messages
const std::string ARGC_COUNT = "Invalid number of arguments. \
Using: ./MultMatrix matrix1.txt matrix2.txt";
const std::string INPUT_OPEN_FAILED = "Failed to open input file.";

class Exception
{
public:
    Exception(std::string errorMsg);
    const std::string GetError();
private:
    std::string errMsg;
};