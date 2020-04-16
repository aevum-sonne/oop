#include <iostream>
#include <fstream>
#include <string>
#include <optional>

// Number of input arguments
const int argsSize = 5;

// Error messages
const std::string invalidArgumentsCount = "Invalid arguments count.Usage: ./replace "
                                          "<input file> <output file> <search string> <replace string>";
const std::string inputIsEmpty = "Input file is empty.";
const std::string subwordBiggerThenInput = "Replace subword is bigger then input file.";
const std::string inputOpenFailed = "Failed to open input file.";
const std::string inputBad = "Failed to read data from input file.";
const std::string outputOpenFailed = "Failed to open output file.";
const std::string outputFlush = "Failed to write data in output file.";
const std::string emptySubstring = "The substring to find shouldn't be empty.";

struct Args
{
    std::string inputFileName, outputFileName,
                subToSearch, subToReplace;
};

std::optional<Args> ParseArgs(int argc, const char * argv[])
{
    if (argc != argsSize)
    {
        return std::nullopt;
    }
    
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.subToSearch = argv[3];
    args.subToReplace = argv[4];

    return args;
}

std::string Replace(std::string line, std::string subToSearch,
                       std::string subToReplace)
{
    size_t index = line.find(subToSearch);
    for (;;)
    {
        if (index == std::string::npos)
        {
            break;
        }
        
        line.replace(index, subToSearch.length(), subToReplace);
        index = line.find(subToSearch, index + subToReplace.length());
    }
    
    return line;
}

int main(int argc, const char * argv[])
{
    auto args = ParseArgs(argc, argv);
    
    if (!args)
    {
        std::cout << invalidArgumentsCount << std::endl;

        return 1;
    }
    
    // Create stream object with read operataion
    std::ifstream input(args->inputFileName);
            
    // Check if file isn't open
    if (!input.is_open())
    {
        std::cout << inputOpenFailed << std::endl;

        return 1;
    }
    
    std::ofstream output(args->outputFileName);
    
    if (!output.is_open())
    {
        std::cout << outputOpenFailed << std::endl;

        return 1;
    }
    
    // If file is empty
    if (std::filesystem::file_size(args->inputFileName) == 1)
    {
        std::cout << inputIsEmpty << std::endl;

        return 1;
    }
    
    // If replace substring is bigger then input file
    if (args->subToSearch.length() >= std::filesystem::file_size(args->inputFileName))
    {
        std::cout << subwordBiggerThenInput << std::endl;

        return 1;
    }

    // If replace substring is empty
    if (args->subToSearch.length() == 0)
    {
        std::cout << emptySubstring << std::endl;

        return 1;
    }
    
    // Replacement operations
    std::string line, processedLine;
    while (std::getline(input, line))
    {
        processedLine = Replace(line, args->subToSearch, args->subToReplace);
        output << processedLine << std::endl;
    }
    
    // Error occurs while read or writing data,
    // generally causing the loss of integrity
    // of the stream.
    if (input.bad())
    {
        std::cout << inputBad << std::endl;

        return 1;
    }
    
    // This function requests all characters to be
    // written to the controlled sequence.
    if (!output.flush())
    {
        std::cout << outputFlush << std::endl;

        return 1;
    }
    
    return 0;
}
