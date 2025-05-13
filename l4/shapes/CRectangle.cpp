#include "CRectangle.h"

CPoint CRectangle::GetLeftTop() const
{
  return m_positions;
}

CPoint CRectangle::GetRightBottom() const
{
  return CPoint(GetLeftTop().GetX() + GetWidth(), GetLeftTop().GetY() + GetHeight());
}

double CRectangle::GetWidth() const
{
  return m_width;
}

double CRectangle::GetHeight() const
{
  return m_height;
}

double CRectangle::GetArea() const
{
  return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
  return 2 * (GetWidth() + GetHeight());
}

uint32_t CRectangle::GetOutlineColor() const
{
  return m_stroke;
}

uint32_t CRectangle::GetFillColor() const
{
  return m_filling;
}

std::string CRectangle::ToString() const
{
  std::stringstream stream;
  stream << std::hex << GetFillColor();

  const std::string INLINE_COLOR = PRINT_INLINE_COLOR + PRINT_HEX_NUMBER + stream.str() + '\n';
  const std::string LEFT_TOP = PRINT_LEFTTOP + GetLeftTop().GetPointsInString() + '\n';
  const std::string RIGHTBOTTOM = PRINT_RIGHTBOTTOM + GetRightBottom().GetPointsInString() + '\n';
  const std::string WIDHT = PRINT_WIDTH + std::to_string(GetWidth()) + '\n';
  const std::string HEIGHT = PRINT_HEIGHT + std::to_string(GetHeight()) + '\n';

  return INLINE_COLOR + LEFT_TOP + RIGHTBOTTOM + WIDHT + HEIGHT;
}

bool CRectangle::Draw(const CCanvas &canvas) const
{
  canvas.FillPolygon(
      {GetLeftTop(),
       CPoint(GetLeftTop().GetX() + GetWidth(), GetLeftTop().GetY()),
       CPoint(GetLeftTop().GetX(), GetLeftTop().GetY() + GetHeight()),
       GetRightBottom()},
      GetFillColor());
  canvas.CreateLine(GetLeftTop(), CPoint(GetLeftTop().GetX() + GetWidth(), GetLeftTop().GetY()), GetOutlineColor());
  canvas.CreateLine(GetLeftTop(), CPoint(GetLeftTop().GetX(), GetLeftTop().GetY() + GetHeight()), GetOutlineColor());
  canvas.CreateLine(GetRightBottom(), CPoint(GetLeftTop().GetX() + GetWidth(), GetLeftTop().GetY()), GetOutlineColor());
  canvas.CreateLine(GetRightBottom(), CPoint(GetLeftTop().GetX(), GetLeftTop().GetY() + GetHeight()), GetOutlineColor());
  return true;
}