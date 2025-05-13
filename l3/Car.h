#ifndef CAR_H
#define CAR_H

#include <optional>
#include "Constants.h"

class Car
{
public:
  Car(std::ostream &output) : m_output(output) {};
  bool TurnOnEngine();
  bool TurnOffEngine();
  bool SetGear(const int gear);
  bool SetSpeed(const int speed);
  bool DisplayInfo() const;

private:
  bool m_isRunning = false;
  int m_speed = 0;
  Broadcast m_broadcast = ZERO;
  std::ostream &m_output;

  Broadcast GetGear() const;
  int GetSpeed() const;
  bool IsTurnedOn() const;
  int GetDirection() const;
  bool ChangeGear(const Broadcast gear);
  std::string GetDirectionString() const;
  std::optional<std::array<int, 2>> GetSpeedLimits() const;
};

#endif
