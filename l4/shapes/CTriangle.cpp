#include "CTriangle.h"

CPoint CTriangle::GetVertex1() const
{
  return m_v1;
}

CPoint CTriangle::GetVertex2() const
{
  return m_v2;
}

CPoint CTriangle::GetVertex3() const
{
  return m_v3;
}

double CTriangle::GetLineLength(const CPoint &position1, const CPoint &position2) const
{
  const double powX = std::pow(position1.GetX() - position2.GetX(), 2);
  const double powY = std::pow(position1.GetY() - position2.GetY(), 2);
  return std::sqrt(powX + powY);
}

double CTriangle::GetArea() const
{
  const double a = GetVertex1().GetX() * (GetVertex2().GetY() - GetVertex3().GetY());
  const double b = GetVertex2().GetX() * (GetVertex3().GetY() - GetVertex1().GetY());
  const double c = GetVertex3().GetX() * (GetVertex1().GetY() - GetVertex2().GetY());
  return std::abs(a + b + c) * 0.5;
}

double CTriangle::GetPerimeter() const
{
  const double a = GetLineLength(GetVertex1(), GetVertex2()); // "/"
  const double b = GetLineLength(GetVertex1(), GetVertex3()); // "\"
  const double c = GetLineLength(GetVertex2(), GetVertex3()); // "_"
  return a + b + c;
}

uint32_t CTriangle::GetOutlineColor() const
{
  return m_stroke;
}

uint32_t CTriangle::GetFillColor() const
{
  return m_filling;
}

std::string CTriangle::ToString() const
{
  std::stringstream stream;
  stream << std::hex << GetFillColor();

  const std::string INLINE_COLOR = PRINT_INLINE_COLOR + PRINT_HEX_NUMBER + stream.str() + '\n';
  const std::string VERTEX_1 = PRINT_VERTEX_1 + GetVertex1().GetPointsInString() + '\n';
  const std::string VERTEX_2 = PRINT_VERTEX_2 + GetVertex2().GetPointsInString() + '\n';
  const std::string VERTEX_3 = PRINT_VERTEX_3 + GetVertex3().GetPointsInString() + '\n';

  return INLINE_COLOR + VERTEX_1 + VERTEX_2 + VERTEX_3;
}

bool CTriangle::Draw(const CCanvas &canvas) const
{
  canvas.FillPolygon({GetVertex1(), GetVertex2(), GetVertex3()}, GetFillColor());
  canvas.CreateLine(GetVertex1(), GetVertex2(), GetOutlineColor());
  canvas.CreateLine(GetVertex2(), GetVertex3(), GetOutlineColor());
  canvas.CreateLine(GetVertex1(), GetVertex3(), GetOutlineColor());
  return true;
}