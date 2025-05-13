#ifndef ICANVAS_H
#define ICANVAS_H

#include <vector>
#include <memory>
#include "../shapes/CPoint.h"

class ICanvas
{
public:
  virtual bool CreateLine(const CPoint &from, const CPoint &to, const uint32_t lineColor) const = 0;
  virtual bool FillPolygon(const std::vector<CPoint> &points, const uint32_t fillColor) const = 0;
  virtual bool DrawCirlce(const CPoint &center, const double radius, const uint32_t lineColor) const = 0;
  virtual bool FillCircle(const CPoint &center, const double radius, const uint32_t fillColor) const = 0;
};

#endif