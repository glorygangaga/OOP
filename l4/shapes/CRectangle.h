#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
  CRectangle(const CPoint &positions,
             const double width, const double height,
             const uint32_t stroke, const uint32_t filling)
      : m_positions(positions), m_width(width), m_height(height), m_stroke(stroke), m_filling(filling) {};

  CPoint GetLeftTop() const;
  CPoint GetRightBottom() const;
  double GetWidth() const;
  double GetHeight() const;

  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;
  std::string GetType() const override { return m_type; };
  uint32_t GetOutlineColor() const override;
  uint32_t GetFillColor() const override;
  bool Draw(const CCanvas &canvas) const override;

private:
  const std::string m_type = RECTANGLE_TYPE;
  CPoint m_positions;
  double m_width, m_height;
  uint32_t m_stroke, m_filling;
};

#endif