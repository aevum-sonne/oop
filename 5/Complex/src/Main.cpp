#include "Complex/Complex.h"
#include <iostream>
#include <sstream>

int main()
{
    std::string line;

    while (getline(std::cin, line) && line != "q")
    {
        std::istringstream ss(line);
        Complex complex;

        ss >> complex;
        std::cout << complex << std::endl;
    }
}