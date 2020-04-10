#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <bitset>

const std::string OUTPUT_PATH = "output.txt";
const char RIGHT_ROTATION = 'R';
const char LEFT_ROTATION = 'L';
const int ARGC_SIZE = 4;
const int SIZE_INT = 32;

// Output error messages
const std::string ARGC_COUNT = "Invalid arguments count. Usage: ./RotateByte <byte> <shiftInterval> L/R.";
const std::string NEGATIVE_VALUE = "Negative value in <byte> or <shiftInterval>.";
const std::string BYTE_SIZE = "The byte number is not in range [0, 255].";
const std::string NO_BYTE = "There is no byte number entered.";
const std::string NOT_INT = "Invalid value type in <byte> or <shiftInterval> (must be int > 0).";
const std::string INVALID_ROTATION = "Invalid value in <shiftDirection> (must be char by value 'L' or 'R').";

// Returns 0 if <byte> or <shiftInterval> isn't a number
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
    if (argc != ARGC_SIZE)
    {
        std::cout << ARGC_COUNT << std::endl;
        return std::nullopt;
    }
    
    for (int i = 0; i < 2; i++)
    {
        if (!IsNumber(argv[i+1]))
        {
            std::cout << NOT_INT << std::endl;
            return std::nullopt;
        }
    }

    if (std::stoi(argv[1]) < 0 || std::stoi(argv[2]) < 0)
    {
        std::cout << NEGATIVE_VALUE << std::endl;
        return std::nullopt;
    }
    
    if (std::stoi(argv[1]) > 255)
    {
        std::cout << BYTE_SIZE << std::endl;
        return std::nullopt;
    }

    char ch = argv[3][0];
    if (ch != LEFT_ROTATION && ch != RIGHT_ROTATION)
    {
        std::cout << INVALID_ROTATION << std::endl;
        return std::nullopt;
    }
    
    Args args;
    args.byte = std::stoi(argv[1]);
    args.shiftInterval = std::stoi(argv[2]);
    args.shiftDirection = argv[3][0];
    
    return args;
}

uint32_t RotateLeft(uint32_t value, unsigned int count) {
    return (value << count) | (value >> (SIZE_INT - count));
}

uint32_t RotateRight(uint32_t value, unsigned int count) {
    return (value >> count);
}

int main(int argc, const char * argv[]) {
    std::ofstream output(OUTPUT_PATH);
    
    auto args = ParseArgs(argc, argv);
    if (!args) return 1;
    if (args->shiftDirection == RIGHT_ROTATION)
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
