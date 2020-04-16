#include "MiniDictionary.h"

MiniDictionary::MiniDictionary()
{
    hasChanges = false;
    AddTranslationsToDict(values);
}

void MiniDictionary::WriteFromFileToDict(std::ifstream& file, miniDictionary& miniDict)
{
    std::string string, buff, key = "", value = "";
    while (getline(file, string))
    {
        std::stringstream ss(string);
        ss >> buff;

        //  Parse key field
        while (buff.back() != ':')
        {
            key += " " + buff;
            ss >> buff;
        }

        if (key == "")  // One word in input
        {
            key = buff.substr(0, buff.size() - 1);
        }
        else    // Process last word and erase space in the beginning of key
        {
            //  Remove ':' character from last element in key and space in beginning
            key += " " + buff.substr(0, buff.size() - 1);
            key = key.substr(1, key.size() - 1);
        }

        //  Parse value field
        while (ss >> buff)
        {
            value += " " + buff;
        }

        // Remove ' ' as first element in value
        value = value.substr(1, value.size());

        miniDict.insert({key, value});
        value = ""; key = "";
    }

    file.close();
}

void MiniDictionary::AddTranslationsToDict(miniDictionary& miniDict)
{
    std::ifstream file("Dictionary.txt");
    if (!file)
    {
        throw std::runtime_error("Input open failed.");
    }

    // Add translations from "Dictionary.txt" to miniDictionary
    WriteFromFileToDict(file, miniDict);
}

std::string MiniDictionary::GetTranslation(std::string word, miniDictionary miniDict)
{
    for (auto elem : miniDict)
    {
        if (Args::ToLowerCase(elem.first) == Args::ToLowerCase(word))
        {
            return elem.second;
        }
    }

    return std::string();
}

void MiniDictionary::WriteFromDictToFile(std::ofstream& file, miniDictionary& miniDict)
{
    for (auto elem : miniDict)
    {
        file << elem.first + ": " + elem.second << std::endl;
    }
}

void MiniDictionary::SaveChanges(miniDictionary& miniDict)
{
    std::cout << "The dictionary was changed. Do you want to save last changes? (y/n)" << std::endl;
    char answer;
    std::cin >> answer;

    if (answer == 'y' or answer == 'Y')
    {
        std::ofstream file("Dictionary.txt");
        WriteFromDictToFile(file, miniDict);
        std::cout << "Changes were saved." << std::endl;
    }
    else
    {
        std::cout << "Changes weren't saved." << std::endl;
    }
}