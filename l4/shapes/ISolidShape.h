#ifndef ISOLIDSHAPE_H
#define ISOLIDSHAPE_H

#include "IShape.h"
#include <memory>
#include <cmath>
#include <iomanip>

class ISolidShape : public IShape
{
public:
  virtual uint32_t GetFillColor() const = 0;
};

#endif