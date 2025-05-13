#ifndef CLINESEGMENT_H
#define CLINESEGMENT_H

#include "IShape.h"

class CLineSegment : public IShape
{
public:
  CLineSegment(const CPoint &v1, const CPoint &v2, const uint32_t stroke)
      : m_v1(v1), m_v2(v2), m_stroke(stroke) {};
  CPoint GetStartPoint() const;
  CPoint GetEndPoint() const;

  constexpr double GetArea() const override { return 0; };
  constexpr double GetPerimeter() const override { return 0; };
  std::string GetType() const override { return m_type; };
  std::string ToString() const override;
  uint32_t GetOutlineColor() const override;
  bool Draw(const CCanvas &canvas) const override;

private:
  const std::string m_type = LINE_SEGMENT_TYPE;
  CPoint m_v1, m_v2;
  uint32_t m_stroke;
};

#endif