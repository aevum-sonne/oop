#include <iostream>
#include "Car/Car.h"
#include "CarController/CarController.h"

int main()
{
    Car car;
    CarController carController(car, std::cin, std::cout);

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << "> ";
        if (!carController.HandleCommand())
        {
            std::cout << "Unknown command.\nAvaliable commands: Info, "
                         "TurnOn, TurnOff, SetGear <gear>, SetSpeed "
                         "<speed>" << std::endl;
        }
    }

    return 0;
}