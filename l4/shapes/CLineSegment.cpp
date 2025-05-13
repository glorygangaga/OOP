#include "CLineSegment.h"

uint32_t CLineSegment::GetOutlineColor() const
{
  return m_stroke;
}

CPoint CLineSegment::GetStartPoint() const
{
  return m_v1;
}

CPoint CLineSegment::GetEndPoint() const
{
  return m_v2;
}

std::string CLineSegment::ToString() const
{
  const std::string STARTPOINT = PRINT_START_POINT + GetStartPoint().GetPointsInString() + '\n';
  const std::string ENDPOINT = PRINT_END_POINT + GetEndPoint().GetPointsInString() + '\n';
  return STARTPOINT + ENDPOINT;
}

bool CLineSegment::Draw(const CCanvas &canvas) const
{
  canvas.CreateLine(GetStartPoint(), GetEndPoint(), GetOutlineColor());
  return true;
}