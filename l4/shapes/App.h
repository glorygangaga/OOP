#ifndef APP_H
#define APP_H

#include <iostream>
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CLineSegment.h"

class Application
{
public:
  Application(std::istream &input, std::ostream &output) : m_input(input), m_output(output), m_canvas(WINDOW_SIZE, WINDOW_SIZE, WINDOW_NAME) {};
  bool Start();

private:
  CCanvas m_canvas;
  std::istream &m_input;
  std::ostream &m_output;

  bool DrawShapes(const std::vector<std::shared_ptr<IShape>> &shapes);
  bool ShowExitInfo(const std::vector<std::shared_ptr<IShape>> &shapes) const;
  bool PrintInfo(const std::shared_ptr<IShape> &shape) const;
  bool PushNewShape(std::vector<std::shared_ptr<IShape>> &shapes, const std::shared_ptr<IShape> &shape) const;
  bool ProcessInput();

  std::shared_ptr<IShape> GetMaxArea(const std::vector<std::shared_ptr<IShape>> &shapes) const;
  std::shared_ptr<IShape> GetMinPerimeter(const std::vector<std::shared_ptr<IShape>> &shapes) const;
  std::shared_ptr<IShape> Create(const SHAPES_TYPE &shape) const;

  std::shared_ptr<IShape> CreateRectangle() const;
  std::shared_ptr<IShape> CreateTriangle() const;
  std::shared_ptr<IShape> CreateCircle() const;
  std::shared_ptr<IShape> CreateLine() const;
};

#endif