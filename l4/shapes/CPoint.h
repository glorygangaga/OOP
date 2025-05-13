#ifndef CPOINT_H
#define CPOINT_H

#include <string>
#include "Constants.h"

class CPoint
{
public:
  CPoint(const double x, const double y) : m_x(x), m_y(y) {}

  inline double GetX() const { return m_x; }
  inline double GetY() const { return m_y; }
  inline std::string GetPointsInString() const
  {
    return PRINT_X + std::to_string(GetX()) + ' ' + PRINT_Y + std::to_string(GetY());
  }

private:
  double m_x, m_y;
};

#endif