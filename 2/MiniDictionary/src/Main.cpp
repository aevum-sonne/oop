#include "CommandLine/CommandLine.h"

int main(int argc, const char * argv[])
{
    MiniDictionary miniDict;
    CommandLine::ProcessCommandLine(miniDict);

    return 0;
}