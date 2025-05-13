#ifndef CCANVAS_H
#define CCANVAS_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
  CCanvas(const unsigned int width, const unsigned int height, const std::string &titleName)
      : m_width(width), m_height(height), m_title(titleName) {};

  bool CreateLine(const CPoint &from, const CPoint &to, const uint32_t lineColor) const override;
  bool FillPolygon(const std::vector<CPoint> &points, const uint32_t fillColor) const override;
  bool DrawCirlce(const CPoint &center, const double radius, const uint32_t lineColor) const override;
  bool FillCircle(const CPoint &center, const double radius, const uint32_t fillColor) const override;

  bool Draw();
  bool IsOpen() const { return m_window && m_window->isOpen(); };

private:
  std::unique_ptr<sf::RenderWindow> m_window;
  unsigned int m_width, m_height;
  std::string m_title;
  std::vector<std::shared_ptr<sf::Drawable>> m_shapes;

  sf::Color Uint32ToColor(const uint32_t color) const;
  bool HandleEvents();
  bool Render();
};

#endif