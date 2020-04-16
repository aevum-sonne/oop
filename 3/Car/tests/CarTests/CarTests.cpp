#include "CarTests.h"

TEST_CASE("Turn on the engine")
{
    Car car;

    REQUIRE(car.TurnOnEngine());
}

TEST_CASE("Turn off the engine")
{
    SECTION("Turn off the engine while car is still")
    {
        Car car;
        car.TurnOnEngine();

        REQUIRE(car.TurnOffEngine());
    }

    SECTION("Turn off the engine while car is moving")
    {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1); car.SetSpeed(20);

        REQUIRE(!car.TurnOffEngine());
    }
}

TEST_CASE("Set correct gear")
{
    SECTION("Set first gear")
    {
        gear = 1;
        Car car;
        car.TurnOnEngine();

        REQUIRE(car.SetGear(gear));
    }

    SECTION("Set twice first gear")
    {
        gear = 1;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);

        REQUIRE(car.SetGear(gear));
    }

    SECTION("Set third gear")
    {
        gear = 1; speed = 30;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear); car.SetSpeed(speed);
        gear = 3;

        REQUIRE(car.SetGear(gear));
    }

    SECTION("Set first gear at reverse gear with zero speed")
    {
        gear = -1;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);
        gear = 1;

        REQUIRE(car.SetGear(gear));
    }
}

TEST_CASE("Set reverse gear")
{
    SECTION("Set reverse gear at neutral gear with zero speed")
    {
        gear = -1;
        Car car;
        car.TurnOnEngine();

        REQUIRE(car.SetGear(gear));
    }

    SECTION("Set reverse gear at neutral gear with non-zero speed")
    {
        gear = 1;
        speed = 10;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);
        car.SetSpeed(speed);
        gear = 0;
        speed = 2;
        car.SetGear(gear);
        car.SetSpeed(speed);
        gear = -1;

        REQUIRE(!car.SetGear(gear));
    }

    SECTION("Set reverse gear at fifth gear")
    {
        gear = 1, speed = 30;
        Car car;
        car.TurnOnEngine();

        car.SetGear(gear);
        car.SetSpeed(speed);
        gear = 3, speed = 55;
        car.SetGear(gear);
        car.SetSpeed(speed);
        gear = 5, speed = 80;
        car.SetGear(gear);
        car.SetSpeed(speed);
        gear = -1;

        REQUIRE(!car.SetGear(gear));
    }

    SECTION("Set reverse gear at first when car isn't moving")
    {
        gear = 1;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);
        gear = -1;

        REQUIRE(car.SetGear(gear));
    }

    SECTION("Set reverse gear at first when car is moving")
    {
        gear = 1;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);
        gear = -1;
        speed = 10;
        car.SetSpeed(speed);

        REQUIRE(!car.SetGear(gear));
    }
}

TEST_CASE("Set incorrect gear")
{
    SECTION("Set fourth gear at neutral gear")
    {
        gear = 4;
        Car car;
        car.TurnOnEngine();

        REQUIRE(!car.SetGear(gear));
    }

    SECTION("Set neutral gear at reverse gear with non-zero speed")
    {
        gear = -1; speed = 10;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear); car.SetSpeed(speed);
        gear = 0;
        car.SetGear(gear);
        gear = 1;

        REQUIRE(!car.SetGear(gear));
    }

    SECTION("Set first gear at reverse gear with non-zero speed")
    {
        gear = -1; speed = 10;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear); car.SetSpeed(speed);
        gear = 1;

        REQUIRE(!car.SetGear(gear));
    }

    SECTION("Set fifth gear at first gear")
    {
        gear = 1; speed = 30;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear); car.SetSpeed(speed);
        gear = 5;

        REQUIRE(!car.SetGear(gear));
    }
}


TEST_CASE("Set correct speed")
{
    SECTION("Set speed in range of first gear")
    {
        gear = 1;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);

        REQUIRE(car.SetSpeed(25));
    }

    SECTION("Set speed at reverse gear")
    {
        gear = -1; speed = 20;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);

        REQUIRE(car.SetSpeed(speed));
    }

    SECTION("Set max speed")
    {
        gear = 1, speed = 30;
        Car car;
        car.TurnOnEngine();

        car.SetGear(gear); car.SetSpeed(speed);
        gear = 3, speed = 55;
        car.SetGear(gear); car.SetSpeed(speed);
        gear = 5, speed = 150;
        car.SetGear(gear);

        REQUIRE(car.SetSpeed(speed));
    }
}

TEST_CASE("Set incorrect speed")
{
    SECTION("Set negative speed")
    {
        gear = 1, speed = -30;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear);

        REQUIRE(!car.SetSpeed(speed));
    }

    SECTION("Set negative speed at neutral gear with non-zero current speed")
    {
        gear = 1, speed = 20;
        Car car;
        car.TurnOnEngine();
        car.SetGear(gear); car.SetSpeed(speed);
        gear = 0; speed = -99999;
        car.SetGear(gear);

        REQUIRE(!car.SetSpeed(speed));
    }

    SECTION("Set speed that above max speed")
    {
        gear = 1, speed = 30;
        Car car;
        car.TurnOnEngine();

        car.SetGear(gear); car.SetSpeed(speed);
        gear = 3, speed = 55;
        car.SetGear(gear); car.SetSpeed(speed);
        gear = 5, speed = 200;
        car.SetGear(gear);

        REQUIRE(!car.SetSpeed(speed));
    }
}