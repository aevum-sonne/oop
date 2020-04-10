#include <iostream>
#include "DecodeUtils/DecodeUtils.h"
#include "Args/Args.h"

int main(int argc, const char * argv[])
{
    Args args;
    if (!args.ParseArgs(argc, argv))
    {
        return 1;
    }

    std::cout << HtmlDecode(args.html) << std::endl;

    return 0;
}