#ifndef ISHAPE_H
#define ISHAPE_H

#include <string>
#include "CPoint.h"
#include "Constants.h"
#include "../canvas/ICanvasDrawable.h"
#include "IShapeType.h"

class IShape : public IShapeType, public ICanvasDrawable
{
public:
  virtual double GetArea() const = 0;
  virtual double GetPerimeter() const = 0;
  virtual std::string ToString() const = 0;
  virtual uint32_t GetOutlineColor() const = 0;
};

#endif