#pragma once

#include "../MiniDictionary/MiniDictionary.h"
#include <string>

namespace CommandLine
{
    const std::string invalidArguments = "Invalid arguments. Enter word or phrase to translate.";
    const std::string translationNotFound = "Not found. Enter translation or empty string to reject.";
    const std::string translationNotAdded = "The translation isn't added. Enter word or phrase to translate.\n";
    const std::string exitCode = "...";
    const std::string exitGuide = "Enter '...' to terminate program.";

    void ProcessCommandLine(MiniDictionary& miniDict);
};


