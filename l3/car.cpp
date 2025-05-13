#include <iostream>
#include <optional>
#include "Car.h"

Broadcast Car::GetGear() const
{
  return m_broadcast;
}

int Car::GetSpeed() const
{
  return m_speed;
}

bool Car::IsTurnedOn() const
{
  return m_isRunning;
}

bool Car::TurnOnEngine()
{
  if (!IsTurnedOn())
  {
    m_isRunning = true;
    m_speed = 0;
    m_broadcast = ZERO;
  }
  return IsTurnedOn();
}

bool Car::TurnOffEngine()
{
  if (IsTurnedOn() && GetGear() == ZERO && GetSpeed() == 0)
    m_isRunning = false;
  return !IsTurnedOn();
}

bool Car::SetGear(const int gear)
{
  if (!IsTurnedOn())
  {
    m_output << TURN_IF_NOT_RUNNING_ENGUINE;
    return false;
  }

  switch (static_cast<Broadcast>(gear))
  {
  case BACK:
    if (GetSpeed() != 0)
    {
      m_output << CANT_REVERSE_WHILE_MOVING;
      return false;
    }
    m_broadcast = BACK;
    break;
  case ZERO:
    m_broadcast = ZERO;
    break;
  case FIRST:
  case SECOND:
  case THIRD:
  case FOURTH:
  case FIFTH:
    return ChangeGear(static_cast<Broadcast>(gear));
  default:
    m_output << INVALID_GEAR;
    return false;
  }

  return true;
}

bool Car::SetSpeed(const int newSpeed)
{
  if (newSpeed < 0)
  {
    m_output << SPEED_CANT_BE_NEGATIVE;
    return false;
  }
  if (!IsTurnedOn())
  {
    m_output << CANT_SET_SPEED_ENGUINE_OFF;
    return false;
  }
  if (GetGear() == ZERO && newSpeed > GetSpeed())
  {
    m_output << CANT_ACCELERATE_ON_NETURAL;
    return false;
  }
  if (GetGear() == ZERO)
  {
    m_speed = newSpeed;
    return true;
  }

  if (!GetSpeedLimits().has_value())
    return false;
  const std::array<int, 2> LIMITS = GetSpeedLimits().value();
  if ((LIMITS[0] > newSpeed || LIMITS[1] < newSpeed))
  {
    m_output << SPEED_OUT_OF_RANGE;
    return false;
  }

  m_speed = newSpeed;
  return true;
}

bool Car::DisplayInfo() const
{
  m_output << INFO_ENGINE << (IsTurnedOn() ? INFO_ON : INFO_OFF) << '\n';
  m_output << INFO_DIRECTION << GetDirectionString() << '\n';
  m_output << INFO_SPEED << GetSpeed() << '\n';
  m_output << INFO_GEAR << GetGear() << '\n';
  return true;
}

int Car::GetDirection() const
{
  const int currSpeed = GetSpeed();
  return currSpeed > 0 && GetGear() != BACK ? 1 : currSpeed == 0 ? 0
                                                                 : -1;
}

bool Car::ChangeGear(const Broadcast gear)
{
  if (!GetSpeedLimits().has_value())
    return false;

  const std::array<int, 2> LIMITS = GetSpeedLimits().value();
  const int currentSpeed = GetSpeed();
  const bool isBackDirection = GetDirection() == -1;

  if ((isBackDirection && currentSpeed != 0) || LIMITS[1] > currentSpeed || LIMITS[0] < currentSpeed)
  {
    m_output << UNSUITABLE_CURRENT_SPEED;
    return false;
  }

  m_broadcast = gear;
  return true;
}

std::string Car::GetDirectionString() const
{
  switch (GetDirection())
  {
  case 1:
    return FORWARD_DIRECTION;
  case -1:
    return BACKWARD_DIRECTION;
  default:
    return STANDING_DIRECTION;
  }
}

std::optional<std::array<int, 2>> Car::GetSpeedLimits() const
{
  auto it = BROADCASTS.find(GetGear());
  if (it == BROADCASTS.end())
  {
    m_output << INVALID_GEAR;
    return std::nullopt;
  }
  return it->second;
}
