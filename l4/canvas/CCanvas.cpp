#include "CCanvas.h"

bool CCanvas::CreateLine(const CPoint &from, const CPoint &to, uint32_t lineColor) const
{
  sf::Vector2f start(from.GetX(), from.GetY());
  sf::Vector2f end(to.GetX(), to.GetY());
  sf::Vector2f direction = end - start;
  float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

  auto line = std::make_unique<sf::RectangleShape>();
  line->setSize(sf::Vector2f(length, THICKNESS));
  line->setPosition(start);
  line->setFillColor(Uint32ToColor(lineColor));
  float angle = std::atan2(direction.y, direction.x) * CHANGE_ANGLE / PI;
  line->setRotation(angle);

  const_cast<CCanvas *>(this)->m_shapes.push_back(std::move(line));
  return true;
}

bool CCanvas::FillPolygon(const std::vector<CPoint> &points, uint32_t fillColor) const
{
  const size_t pointsCount = points.size();
  if (pointsCount == RECTANGLE_POINTS)
  {
    auto shape = std::make_unique<sf::VertexArray>(sf::Triangles, POINTS_OF_RECTANGLES);
    auto &vertices = *shape;
    for (size_t i = 0; i < POINTS_OF_RECTANGLES; i++)
    {
      int idx = INDICES[i];
      vertices[i].position = sf::Vector2f(points[idx].GetX(), points[idx].GetY());
      vertices[i].color = Uint32ToColor(fillColor);
    }
    const_cast<CCanvas *>(this)->m_shapes.push_back(std::move(shape));
  }
  else
  {
    auto shape = std::make_unique<sf::VertexArray>(sf::Triangles, pointsCount);
    auto &vertices = *shape;

    for (size_t i = 0; i < pointsCount; i++)
    {
      vertices[i].position = sf::Vector2f(points[i].GetX(), points[i].GetY());
      vertices[i].color = Uint32ToColor(fillColor);
    }
    const_cast<CCanvas *>(this)->m_shapes.push_back(std::move(shape));
  }
  return true;
}

bool CCanvas::DrawCirlce(const CPoint &center, double radius, uint32_t lineColor) const
{
  auto shape = std::make_unique<sf::CircleShape>();
  shape->setRadius(radius);
  shape->setPosition(center.GetX() + radius, center.GetY() + radius);
  shape->setOutlineColor(Uint32ToColor(lineColor));
  shape->setOutlineThickness(THICKNESS);
  const_cast<CCanvas *>(this)->m_shapes.push_back(std::move(shape));
  return true;
}

bool CCanvas::FillCircle(const CPoint &center, double radius, uint32_t fillColor) const
{
  auto shape = std::make_unique<sf::CircleShape>();
  shape->setRadius(radius);
  shape->setPosition(center.GetX() + radius, center.GetY() + radius);
  shape->setFillColor(Uint32ToColor(fillColor));
  const_cast<CCanvas *>(this)->m_shapes.push_back(std::move(shape));
  return true;
}

sf::Color CCanvas::Uint32ToColor(uint32_t color) const
{
  uint8_t red = (color >> SIZE_OF_RED_COLOR) & GET_SIZE_COLOR;
  uint8_t green = (color >> SIZE_OF_GREEN_COLOR) & GET_SIZE_COLOR;
  uint8_t blue = color & GET_SIZE_COLOR;
  return sf::Color(red, green, blue, GET_SIZE_COLOR);
}

bool CCanvas::HandleEvents()
{
  sf::Event event;
  while (m_window->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      m_window->close();
  }

  return true;
}

bool CCanvas::Render()
{
  m_window->clear(sf::Color::White);
  for (const auto &shape : m_shapes)
    m_window->draw(*shape);
  m_window->display();

  return true;
}

bool CCanvas::Draw()
{
  if (!m_window)
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), m_title);

  while (IsOpen())
  {
    HandleEvents();
    Render();
  }

  return true;
}