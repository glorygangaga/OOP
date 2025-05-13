#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
  CTriangle(const CPoint &v1, const CPoint &v2, const CPoint &v3,
            const uint32_t stroke, const uint32_t filling)
      : m_v1(v1), m_v2(v2), m_v3(v3), m_stroke(stroke), m_filling(filling) {};

  CPoint GetVertex1() const;
  CPoint GetVertex2() const;
  CPoint GetVertex3() const;

  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;
  std::string GetType() const override { return m_type; };
  uint32_t GetOutlineColor() const override;
  uint32_t GetFillColor() const override;
  bool Draw(const CCanvas &canvas) const override;

private:
  const std::string m_type = TRIANGLE_TYPE;
  CPoint m_v1, m_v2, m_v3;
  uint32_t m_stroke, m_filling;

  double GetLineLength(const CPoint &position1, const CPoint &position2) const;
};

#endif