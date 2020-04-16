#include "Car.h"

bool Car::IsTurnedOn() const
{
    return m_isEngineRunning;
}

int Car::GetSpeed() const
{
    return m_currentSpeed;
}

Gear Car::GetGear() const
{
    return m_currentGear;
}

Direction Car::GetDirection() const
{
    return m_currentDirection;
}

bool Car::TurnOnEngine()
{
    if (!m_isEngineRunning)
    {
        m_isEngineRunning = true;
        m_isCarStandingStill = true;

        return true;
    }

    return false;
}

bool Car::TurnOffEngine()
{
    if (m_isCarStandingStill && m_currentGear == Gear::Neutral)
    {
        m_isEngineRunning = false;

        return true;
    }

    return false;
}

bool Car::IsSpeedInRangeOfGear(int speed, Gear gear) const
{
    std::pair<int, int> speedRange = m_gearToSpeedRange.find(gear)->second;

    return speed >= speedRange.first && speed <= speedRange.second;
}

bool Car::IsSpeedChangesInDirectionOfZero(int speed) const
{
    return (m_currentDirection == Direction::Backward && speed > m_currentSpeed)
           || (m_currentDirection == Direction::Forward && speed < m_currentSpeed);
}

void Car::UpdateCarState(int speed)
{
    m_currentSpeed = speed;
    m_isCarStandingStill = (m_currentSpeed == 0);
    m_currentDirection = (m_isCarStandingStill) ? Direction::Still
            :   (m_currentGear==Gear::Reverse) ? Direction::Backward
            :   Direction::Forward;

}

bool Car::SetGear(int gear)
{
    // Convert input int gear to enum type Gear
    Gear inputGear = Gear(gear + 1);

    // Engine is turned off
    if (!m_isEngineRunning)
    {
        return false;
    }

    // While car is running
    if (!m_isCarStandingStill)
    {
        // Can't shift at Reverse or to Reverse gear
        if (m_currentGear == Gear::Reverse || inputGear == Gear::Reverse)
        {
            return false;
        }
        // Can't shift at Reverse or Neutral to First gear
        else if (((m_currentGear == Gear::Reverse || m_currentGear == Gear::Neutral)
                  && inputGear == Gear::First))
        {
            return false;
        }
    }

    // Current speed not in gear speed range
    if (!IsSpeedInRangeOfGear(m_currentSpeed, inputGear))
    {
        return false;
    }

    m_currentGear = inputGear;

    return true;

}

bool Car::SetSpeed(int speed)
{
    // Engine is turned off
    if (!m_isEngineRunning)
    {
        return false;
    }

    // At neutral gear speed can be changed only in the direction of zero
    if (m_currentGear == Gear::Neutral)
    {
        if (!IsSpeedChangesInDirectionOfZero(speed))
        {
            return false;
        }
    }

    // Input speed not in speed range of current gear
    if (!IsSpeedInRangeOfGear(speed, m_currentGear))
    {
        return false;
    }

    UpdateCarState(speed);

    return true;
}