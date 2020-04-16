#include "CarControllerTests.h"
#include <sstream>
#include <string>

std::stringstream GetConsoleOut(Car& car, std::stringstream& input)
{
    std::stringstream output;
    CarController carController(car, input, output);
    carController.HandleCommand();

    return output;
}

TEST_CASE("Input stream is empty")
{
    Car car;
    std::stringstream input, output, expected;
    output = GetConsoleOut(car, input);

    REQUIRE(expected.str() == output.str());
}

TEST_CASE("Info")
{
    SECTION("At Still direction")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "Info";
        expected << "Car info:" << std::endl;
        expected << "Engine: on" << std::endl;
        expected << "Speed: 0" << std::endl;
        expected << "Gear: Neutral" << std::endl;
        expected << "Direction: Still" << std::endl;
        car.TurnOnEngine();
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("At Forward direction")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "Info";
        expected << "Car info:" << std::endl;
        expected << "Engine: on" << std::endl;
        expected << "Speed: 20" << std::endl;
        expected << "Gear: First" << std::endl;
        expected << "Direction: Forward" << std::endl;
        car.TurnOnEngine();
        car.SetGear(1); car.SetSpeed(20);
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("At Backward direction")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "Info";
        expected << "Car info:" << std::endl;
        expected << "Engine: on" << std::endl;
        expected << "Speed: 20" << std::endl;
        expected << "Gear: Reverse" << std::endl;
        expected << "Direction: Backward" << std::endl;
        car.TurnOnEngine();
        car.SetGear(-1); car.SetSpeed(20);
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }
}

TEST_CASE("Turn on engine")
{
    SECTION("Turn on not running engine")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "EngineOn";
        expected << "Engine is turned on." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Turn on already running engine")
    {
        Car car;
        car.TurnOnEngine();
        std::stringstream input, output, expected;
        input << "EngineOn";
        expected << "Engine is already running." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }
}

TEST_CASE("Turn off engine")
{
    SECTION("Turn off running engine while car is still")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "EngineOff";
        car.TurnOnEngine();
        expected << "Engine is turned off." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Turn off running engine while car is running")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "EngineOff";
        car.TurnOnEngine();
        car.SetGear(1); car.SetSpeed(30);
        expected << "Can't turn off engine when car is running." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Turn off running engine at non-neutral gear")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "EngineOff";
        car.TurnOnEngine();
        car.SetGear(1);
        expected << "Can't turn off engine at non-neutral gear." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }
}

TEST_CASE("Set correct gear")
{
    SECTION("Set first gear")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetGear 1";
        car.TurnOnEngine();
        expected << "Gear is shifted to First." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set third gear")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetGear 3";
        car.TurnOnEngine();
        car.SetGear(1); car.SetSpeed(30);
        expected << "Gear is shifted to Third." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set first gear at reverse gear with zero speed")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetGear 1";
        car.TurnOnEngine(); car.SetGear(-1);
        expected << "Gear is shifted to First." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }
}

TEST_CASE("Set incorrect gear")
{
    SECTION("Set fourth gear at neutral gear")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetGear 4";
        car.TurnOnEngine();
        expected << "Gear hasn't changed." << std::endl;
        expected << "Current speed = 0 isn't in Fourth gear speed range." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set neutral gear at reverse gear with non-zero speed")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetGear 0";
        car.TurnOnEngine();
        car.SetGear(-1); car.SetSpeed(20);
        expected << "Gear hasn't changed." << std::endl;
        expected << "Can't shift Reverse gear to Neutral while car is moving." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set first gear at reverse gear with non-zero speed")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetGear 1";
        car.TurnOnEngine();
        car.SetGear(-1); car.SetSpeed(20);
        expected << "Gear hasn't changed." << std::endl;
        expected << "Can't shift Reverse gear to First while car is moving." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set fifth gear at first gear")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetGear 5";
        car.TurnOnEngine();
        car.SetGear(1); car.SetSpeed(30);
        expected << "Gear hasn't changed." << std::endl;
        expected << "Current speed = 30 isn't in Fifth gear speed range." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }
}


TEST_CASE("Set correct speed")
{
    SECTION("Set speed at first gear")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetSpeed 30";
        car.TurnOnEngine();
        car.SetGear(1);
        expected << "Speed set to 30." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set speed at reverse gear")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetSpeed 20";
        car.TurnOnEngine();
        car.SetGear(-1);
        expected << "Speed set to 20." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set max speed")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetSpeed 150";
        car.TurnOnEngine();
        car.SetGear(1); car.SetSpeed(30);
        car.SetGear(3); car.SetSpeed(60);
        car.SetGear(5);
        expected << "Speed set to 150." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }
}

TEST_CASE("Set incorrect speed")
{
    SECTION("Set negative speed")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetSpeed -20";
        car.TurnOnEngine();
        expected << "Argument isn't a positive number." << std::endl;
        expected << "Speed hasn't changed." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set symbols in speed")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetSpeed sdj@3!";
        car.TurnOnEngine();
        expected << "Argument isn't a number." << std::endl;
        expected << "Speed hasn't changed." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }

    SECTION("Set speed that above max speed")
    {
        Car car;
        std::stringstream input, output, expected;
        input << "SetSpeed 999";
        car.TurnOnEngine();
        car.SetGear(1); car.SetSpeed(30);
        car.SetGear(3); car.SetSpeed(55);
        car.SetGear(5);
        expected << "Speed hasn't changed." << std::endl;
        expected << "Speed isn't in current gear's speed range." << std::endl;
        output = GetConsoleOut(car, input);

        REQUIRE(expected.str() == output.str());
    }
}