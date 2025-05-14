#ifndef APP_H
#define APP_H

#include "CHttpUrl.h"

class Application
{
public:
  Application(std::istream &input, std::ostream &output) : m_input(input), m_output(output) {};
  bool Start();

private:
  std::istream &m_input;
  std::ostream &m_output;
};

#endif