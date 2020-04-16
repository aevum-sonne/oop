#include "Args.h"

std::optional<Args> Args::ParseArgs(int argc, const char * argv [])
{
    if (argc == 1)
    {
        std::cout << "Invalid arguments count." << std::endl;
        
        return std::nullopt;
    }

    Args args;
    vector.resize(argc-1, 0);

    for (size_t i = 0; i != vector.size(); i++)
    {
        try
        {
            // Try to convert each non-executable argument into double
            Args::currArg = std::stod(argv[i+1]);
            vector[i] = Args::currArg;
        }
        catch (const std::exception &e)
        {
            std::cout << "Argument \'" << argv[i+1] 
            << "\' isn't a number." << std::endl;

            return std::nullopt;
        }
    }

    return args;
}