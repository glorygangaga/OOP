#include "app.h"

bool Application::Start()
{
  std::string action;
  while (m_input >> action)
  {
    auto it = commandHandlers.find(action);
    if (it == commandHandlers.end())
      m_output << UNKNOWN_COMMAND;
    else
      Actions(it->second);
  }

  return true;
}

bool Application::Actions(const COMMANDS &action)
{
  switch (action)
  {
  case COMMANDS::ENGINE_ON_E:
    return ActionEngineOn();
  case COMMANDS::ENGINE_OFF_E:
    return ActionEngineOff();
  case COMMANDS::INFO_E:
    return ActionInfo();
  case COMMANDS::SET_GEAR_E:
    return ActionSetGear();
  case COMMANDS::SET_SPEED_E:
    return ActionSetSpeed();
  default:
    return false;
  }
}

bool Application::ActionEngineOn()
{
  m_car.TurnOnEngine();
  return true;
}

bool Application::ActionEngineOff()
{
  if (!m_car.TurnOffEngine())
  {
    m_output << INVALID_TURNOFF_ENGUINE;
    return false;
  }
  return true;
}

bool Application::ActionInfo()
{
  m_car.DisplayInfo();
  return true;
}

bool Application::ActionSetGear()
{
  int value;
  if (!(m_input >> value))
  {
    m_output << INVALID_COMMAND_ARGUMENT;
    return false;
  }
  else
    m_car.SetGear(value);
  return true;
}

bool Application::ActionSetSpeed()
{
  int value;
  if (!(m_input >> value))
  {
    m_output << INVALID_COMMAND_ARGUMENT;
    return false;
  }
  else
    m_car.SetSpeed(value);
  return true;
}
