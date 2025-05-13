#include "CCircle.h"

CPoint CCircle::GetCenter() const
{
  return m_center;
}

double CCircle::GetRadius() const
{
  return m_radius;
}

double CCircle::GetArea() const
{
  return PI * std::pow(GetRadius(), CONSTANT_OF_CIRCLE);
}

double CCircle::GetPerimeter() const
{
  return CONSTANT_OF_CIRCLE * PI * GetRadius();
}

uint32_t CCircle::GetOutlineColor() const
{
  return m_stroke;
}

uint32_t CCircle::GetFillColor() const
{
  return m_filling;
}

std::string CCircle::ToString() const
{
  std::stringstream stream;
  stream << std::hex << GetFillColor();

  const std::string INLINE_COLOR = PRINT_INLINE_COLOR + PRINT_HEX_NUMBER + stream.str() + '\n';
  const std::string CENTER = PRINT_CENTER + GetCenter().GetPointsInString() + '\n';
  const std::string RADIUS = PRINT_RADIUS + std::to_string(GetRadius()) + '\n';

  return INLINE_COLOR + CENTER + RADIUS;
}

bool CCircle::Draw(const CCanvas &canvas) const
{
  canvas.DrawCirlce(GetCenter(), GetRadius(), GetOutlineColor());
  canvas.FillCircle(GetCenter(), GetRadius(), GetFillColor());

  return true;
}