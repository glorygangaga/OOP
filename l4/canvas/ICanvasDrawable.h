#ifndef ICANVASDRAWABLE_H
#define ICANVASDRAWABLE_H

#include "CCanvas.h"

class ICanvasDrawable
{
public:
  virtual bool Draw(const CCanvas &canvas) const = 0;
};

#endif