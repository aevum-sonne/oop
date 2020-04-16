#include "CarController.h"
#include <sstream>

CarController::CarController(Car& car, std::istream& input, std::ostream& output)
    : m_car(car)
    , m_input(input)
    , m_output(output)
    , m_commandMap(
                {
                        {"Info",std::bind(&CarController::Info, this, std::placeholders::_1)},
                        {
                         "EngineOn",  [this](std::istream &stream) {
                            return EngineOn(stream);
                        }},
                        {
                         "EngineOff", [this](std::istream &stream) {
                            return EngineOff(stream);
                        }},
                        {
                         "SetSpeed",  [this](std::istream &stream) {
                            return SetSpeed(stream);
                        }},
                        {
                         "SetGear",   [this](std::istream &stream) {
                            return SetGear(stream);
                        }},
                    })
{
}

bool CarController::HandleCommand()
{
    std::string commandLine;
    getline(m_input, commandLine);
    std::istringstream stream(commandLine);

    std::string command;
    stream >> command;

    auto it = m_commandMap.find(command);
    if (it != m_commandMap.end())
    {
        return it->second(stream);
    }

    return false;
}

bool CarController::Info(std::istream& args)
{
    m_output << "Car info:" << std::endl;

    if (m_car.IsTurnedOn())
    {
        m_output << "Engine: on" << std::endl;
        m_output << "Speed: " + std::to_string(m_car.GetSpeed()) << std::endl;
        m_output << "Gear: " + GetGearName(m_car.GetGear()) << std::endl;
        m_output << "Direction: " + GetDirectionName(m_car.GetDirection()) << std::endl;
    }
    else
    {
        m_output << "Engine: off" << std::endl;
    }

    return true;
}


bool CarController::EngineOn(std::istream &args)
{
    if (m_car.TurnOnEngine())
    {
        m_output << "Engine is turned on." << std::endl;
    }
    else
    {
        m_output << "Engine is already running." << std::endl;
    }

    return true;
}

bool CarController::EngineOff(std::istream &args)
{
    if (m_car.TurnOffEngine())
    {
        m_output << "Engine is turned off." << std::endl;
    }
    else if (!(m_car.GetDirection() == Direction::Still))
    {
        m_output << "Can't turn off engine when car is running." << std::endl;
    }
    else
    {
        m_output << "Can't turn off engine at non-neutral gear." << std::endl;
    }

    return true;
}

bool CarController::SetSpeed(std::istream& args)
{
    int speed;
    args >> speed;

    if (args.fail())
    {
        m_output << "Argument isn't a number." << std::endl;
        m_output << "Speed hasn't changed." << std::endl;

        return true;
    }

    if (speed < 0)
    {
        m_output << "Argument isn't a positive number." << std::endl;
        m_output << "Speed hasn't changed." << std::endl;

        return true;
    }

    if (m_car.SetSpeed(speed))
    {
        m_output << "Speed set to " + std::to_string(speed) + "." << std::endl;
    }
    else
    {
        m_output << "Speed hasn't changed." << std::endl;

        if (!m_car.IsTurnedOn())
        {
            m_output << "Engine isn't running." << std::endl;
        }
        else if (((m_car.GetGear() == Gear::Neutral)
        && !(m_car.GetDirection() == Direction::Backward && speed > m_car.GetSpeed()))
        || (m_car.GetDirection() == Direction::Forward && speed < m_car.GetSpeed()))
        {
            m_output << "Can't change speed at neutral gear "
                         "while car is moving." << std::endl;
        }
        else
        {
            m_output << "Speed isn't in current gear's speed range." << std::endl;
        }
    }

    return true;
}

bool CarController::SetGear(std::istream& args)
{
    int gear;
    args >> gear;
    Gear inputGear = Gear(gear + 1);

    if (args.fail())
    {
        m_output << "Argument isn't an integer." << std::endl;
        m_output << "Gear hasn't changed." << std::endl;
    }
    else if (m_car.SetGear(gear))
    {
        m_output << "Gear is shifted to " + GetGearName(inputGear) + "." << std::endl;
    }
    else
    {
        m_output << "Gear hasn't changed." << std::endl;

        if (!m_car.IsTurnedOn())
        {
            m_output << "Engine isn't running." << std::endl;
        }
        else if (m_car.GetGear() == Gear::Reverse || inputGear == Gear::Reverse
                 || ((m_car.GetGear() == Gear::Reverse || m_car.GetGear() == Gear::Neutral)
                 && inputGear == Gear::First))
        {
            m_output << "Can't shift Reverse gear to " << GetGearName(inputGear)
                      << " while car is moving." << std::endl;
        }
        else
        {
            m_output << "Current speed = " << m_car.GetSpeed()
                      << " isn't in " << GetGearName(inputGear) << " gear speed range." << std::endl;
        }
    }

    return true;
}

std::string CarController::GetGearName(Gear gear) const
{
    switch (gear)
    {
        case Gear::Neutral:
        {
            return "Neutral";
        }
        case Gear::Reverse:
        {
            return "Reverse";
        }
        case Gear::First:
        {
            return "First";
        }
        case Gear::Second:
        {
            return "Second";
        }
        case Gear::Third:
        {
            return "Third";
        }
        case Gear::Fourth:
        {
            return "Fourth";
        }
        case Gear::Fifth:
        {
            return "Fifth";
        }
    }
}

std::string CarController::GetDirectionName(Direction direction) const
{
    switch (direction)
    {
        case Direction::Forward:
        {
            return "Forward";
        }
        case Direction::Backward:
        {
            return "Backward";
        }
        case Direction::Still:
        {
            return "Still";
        }
    }
}