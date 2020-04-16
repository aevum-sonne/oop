#include "CommandLine.h"

void CommandLine::ProcessCommandLine(MiniDictionary& miniDict)
{
    std::string string = "";

    std::cout << exitGuide << std::endl;
    // Parse command line
    while (getline(std::cin, string))
    {
        if (string == exitCode) break;

        Args args;
        // Get new word if arguments isn't correct
        if (!args.ParseArgs(string))
        {
            std::cout << invalidArguments << std::endl;
            getline(std::cin, string);

            continue;
        }

        args.translation = MiniDictionary::GetTranslation(args.word, miniDict.values);
        // Translation found
        if (args.translation != std::string())
        {
            std::cout << args.translation << std::endl;

            continue;
        }
            // Translation not found
        else
        {
            std::cout << translationNotFound << std::endl;
            getline(std::cin, string);

            // Add translation if string not empty
            if (string != std::string())
            {
                miniDict.hasChanges = true;
                miniDict.values.insert({args.word, string});
                std::cout << "Word '" + args.word + "' saved as '" + string + "\'." << std::endl;
            }
            else
            {
                std::cout << translationNotAdded << std::endl;
            }
            // Get new word
            getline(std::cin, string);
        }
    }

    if (miniDict.hasChanges)
    {
        MiniDictionary::SaveChanges(miniDict.values);
    }
}