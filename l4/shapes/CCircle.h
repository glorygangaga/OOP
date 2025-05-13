#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
  CCircle(const CPoint &center, const double radius,
          const uint32_t stroke, const uint32_t filling)
      : m_center(center), m_radius(radius), m_stroke(stroke), m_filling(filling) {};

  CPoint GetCenter() const;
  double GetRadius() const;

  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;
  std::string GetType() const override { return m_type; };
  uint32_t GetOutlineColor() const override;
  uint32_t GetFillColor() const override;
  bool Draw(const CCanvas &canvas) const override;

private:
  const std::string m_type = CIRCLE_TYPE;
  CPoint m_center;
  double m_radius;
  uint32_t m_stroke, m_filling;
};

#endif