#include <iostream>
#include <fstream>
#include <string>
#include <optional>

const std::string argcCount = "Invalid arguments count. Usage: ./RotateByte <byte> <shiftInterval> L/R.";
const std::string negativeValue = "Negative value in <byte> or <shiftInterval>.";
const std::string byteSize = "The byte number is not in range [0, 255].";
const std::string notInt = "Invalid value type in <byte> or <shiftInterval> (must be int > 0).";
const std::string invalidRotation = "Invalid value in <shiftDirection> (must be char by value 'L' or 'R').";
const std::string outputPath = "output.txt";

const char rightRotation = 'R';
const char leftRotation = 'L';
const int argcSize = 4;
const int sizeInt = 32;

bool IsNumber(const std::string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!std::isdigit(s[i]))
        {
            return 0;
        }
    }
    return 1;
}

struct Args
{
    char shiftDirection;
    int byte, shiftInterval;
};

// Parse arguments or throw error message
std::optional<Args> ParseArgs(int argc, const char * argv[])
{
    if (argc != argcSize)
    {
        std::cout << argcCount << std::endl;

        return std::nullopt;
    }
    
    for (int i = 0; i < 2; i++)
    {
        if (!IsNumber(argv[i+1]))
        {
            std::cout << notInt << std::endl;

            return std::nullopt;
        }
    }

    if (std::stoi(argv[1]) < 0 || std::stoi(argv[2]) < 0)
    {
        std::cout << negativeValue << std::endl;

        return std::nullopt;
    }
    
    if (std::stoi(argv[1]) > 255)
    {
        std::cout << byteSize << std::endl;

        return std::nullopt;
    }

    char ch = argv[3][0];
    if (ch != leftRotation && ch != rightRotation)
    {
        std::cout << invalidRotation << std::endl;

        return std::nullopt;
    }
    
    Args args;
    args.byte = std::stoi(argv[1]);
    args.shiftInterval = std::stoi(argv[2]);
    args.shiftDirection = argv[3][0];
    
    return args;
}

uint32_t RotateLeft(uint32_t value, unsigned int count)
{
    return (value << count) | (value >> (sizeInt - count));
}

uint32_t RotateRight(uint32_t value, unsigned int count)
{
    return (value >> count);
}

int main(int argc, const char * argv[]) {
    std::ofstream output(outputPath);
    
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    if (args->shiftDirection == rightRotation)
    {
        std::cout << RotateRight(args->byte, args->shiftInterval) << std::endl;
        output << RotateRight(args->byte, args->shiftInterval) << std::endl;

    }
    else
    {
        std::cout << RotateLeft(args->byte, args->shiftInterval) << std::endl;
        output << RotateLeft(args->byte, args->shiftInterval) << std::endl;
    }

    return 0;
}
