#pragma once

#include <iostream>
#include "../Car/Car.h"

class CarController
{
public:
    CarController(Car& car, std::istream& input, std::ostream& output);
    bool HandleCommand();

private:
    using Handler = std::function<bool(std::istream& args)>;
    using CommandMap = std::map<std::string, Handler>;

    [[nodiscard]] std::string GetGearName(Gear gear) const;
    [[nodiscard]] std::string GetDirectionName(Direction direction) const;

    bool Info(std::istream& args);
    bool EngineOn(std::istream& args);
    bool EngineOff(std::istream& args);
    bool SetGear(std::istream& args);
    bool SetSpeed(std::istream& args);

    Car m_car;
    std::istream& m_input;
    std::ostream& m_output;

    const CommandMap m_commandMap;
};
