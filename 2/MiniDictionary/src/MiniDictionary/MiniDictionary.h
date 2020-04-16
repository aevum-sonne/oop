#pragma once

#include "../Args/Args.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <optional>

class MiniDictionary
{
public:
    using miniDictionary = std::map<std::string, std::string>;

    bool hasChanges;
    miniDictionary values;

    MiniDictionary();
    static void WriteFromFileToDict(std::ifstream& file, miniDictionary& miniDict);
    static void WriteFromDictToFile(std::ofstream& file, miniDictionary& miniDict);
    static void AddTranslationsToDict(miniDictionary& miniDict);
    static void SaveChanges(miniDictionary& miniDict);
    static std::string GetTranslation(std::string word, miniDictionary miniDict);
};