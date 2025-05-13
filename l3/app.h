#ifndef APP_H
#define APP_H

#include <iostream>
#include "Car.h"

class Application
{
public:
  Application(std::istream &input, std::ostream &output) : m_input(input), m_output(output), m_car(output) {};
  bool Start();

private:
  Car m_car;
  std::istream &m_input;
  std::ostream &m_output;

  bool Actions(const COMMANDS &action);
  bool ActionEngineOn();
  bool ActionEngineOff();
  bool ActionInfo();
  bool ActionSetGear();
  bool ActionSetSpeed();
};

#endif