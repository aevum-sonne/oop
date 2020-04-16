#pragma once

#include <map>
#include "Gear.h"
#include "Direction.h"

class Car
{
public:
    [[nodiscard]] bool IsTurnedOn() const;
    [[nodiscard]] int GetSpeed() const;
    [[nodiscard]] Gear GetGear() const;
    [[nodiscard]] Direction GetDirection() const;

    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);

private:
    void UpdateCarState(int speed);
    [[nodiscard]] bool IsSpeedInRangeOfGear(int speed, Gear gear) const;
    [[nodiscard]] bool IsSpeedChangesInDirectionOfZero(int speed) const;

    int m_currentSpeed = 0;
    bool m_isEngineRunning = false;
    bool m_isCarStandingStill = true;
    Gear m_currentGear = Gear::Neutral;
    Direction m_currentDirection = Direction::Still;

    const std::map<Gear, std::pair<int, int>> m_gearToSpeedRange
            {
                    {Gear::Reverse, {0, 20}},
                    {Gear::Neutral, {0, 150}},
                    {Gear::First,   {0, 30}},
                    {Gear::Second,  {20, 50}},
                    {Gear::Third,   {30, 60}},
                    {Gear::Fourth,  {40, 90}},
                    {Gear::Fifth,   {50, 150}}
            };
};

