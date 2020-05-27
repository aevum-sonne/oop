#include <FindMaxExController/FindMaxExController.h>
#include <iostream>

int main()
{
    FindMaxExController controller(std::cin, std::cout);
    std::string line;

    std::cout << "Usage: <first-name> <patronym> <last-name> "
                 "<height> <weight>" << std::endl;

    controller.ParseCommandLine();

    if (!controller.IsSportsmenWereAdded())
    {
        std::cout << "No arguments were provide." << std::endl;
    }
    else
    {
        controller.PrintSportsmanWithMaxHeight();
        controller.PrintSportsmanWithMaxWeight();
    }

    return 0;
}