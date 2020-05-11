#include <ShapesController/ShapesController.h>
#include <iostream>

int main ()
{
    ShapesController shapesController(std::cin, std::cout);
    shapesController.PrintUsageGuide();

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << "> ";

        if (!shapesController.HandleCommand())
        {
            if (shapesController.HandledExitCommand())
            {
                break;
            }

            std::cout << "Unknown command. Available commands: "
                         "triangle, rectangle, circle, ls" << std::endl;
        }
    }

    shapesController.PrintShapeWithMinimumPerimeter();
    shapesController.PrintShapeWithMaximumArea();
}