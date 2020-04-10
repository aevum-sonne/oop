#include "Args.h"

std::optional<Args> Args::ParseArgs(int argc, const char * argv [])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count." << std::endl;

        return std::nullopt;
    };

    Args args;
    args.html = argv[1];

    return args;
}