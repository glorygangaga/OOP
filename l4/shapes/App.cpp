#include "App.h"

bool Application::Start()
{
  return ProcessInput();
}

bool Application::ProcessInput()
{
  std::vector<std::shared_ptr<IShape>> shapes;
  std::string line;

  while (m_input >> line)
  {
    auto it = SHAPES_MAP.find(line);
    if (it == SHAPES_MAP.end())
      m_output << UNKNOWN_COMMAND;
    else
      PushNewShape(shapes, Create(it->second));
  }
  m_output << '\n';

  return DrawShapes(shapes);
}

bool Application::DrawShapes(const std::vector<std::shared_ptr<IShape>> &shapes)
{
  int shapesWithoutLinesSize = 0;
  for (const auto &shape : shapes)
  {
    PrintInfo(shape);
    shape->Draw(m_canvas);
    if (!dynamic_cast<const CLineSegment *>(shape.get()))
      shapesWithoutLinesSize++;
  }

  if (!shapesWithoutLinesSize)
    m_output << NO_SHAPES_AVAILABLE;
  else
    ShowExitInfo(shapes);

  if (shapes.size() != 0)
    m_canvas.Draw();

  return true;
}

bool Application::PrintInfo(const std::shared_ptr<IShape> &shape) const
{
  m_output << shape->GetType() << ":\n";
  m_output << PRINT_AREA << shape->GetArea() << '\n';
  m_output << PRINT_PERIMETER << shape->GetPerimeter() << '\n';
  m_output << PRINT_OUTLINE_COLOR << PRINT_HEX_NUMBER << std::hex << shape->GetOutlineColor() << '\n';
  m_output << shape->ToString() << '\n';

  return true;
}

bool Application::PushNewShape(std::vector<std::shared_ptr<IShape>> &shapes, const std::shared_ptr<IShape> &shape) const
{
  if (shape == nullptr)
  {
    m_input.clear();
    m_input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  shapes.push_back(shape);

  return true;
}

std::shared_ptr<IShape> Application::GetMaxArea(const std::vector<std::shared_ptr<IShape>> &shapes) const
{
  if (shapes.empty())
    return nullptr;

  auto it = std::max_element(shapes.begin(), shapes.end(), [](const auto &a, const auto &b)
                             {
    bool isFirstLine = dynamic_cast<const CLineSegment *>(a.get());
    bool isSecondLine = dynamic_cast<const CLineSegment *>(b.get());
    if (isFirstLine || isSecondLine)
      return false;
    return a->GetArea() < b->GetArea(); });

  return (it != shapes.end() ? *it : nullptr);
}

std::shared_ptr<IShape> Application::GetMinPerimeter(const std::vector<std::shared_ptr<IShape>> &shapes) const
{
  if (shapes.empty())
    return nullptr;

  auto it = std::min_element(shapes.begin(), shapes.end(), [](const auto &a, const auto &b)
                             {
    bool isFirstLine = dynamic_cast<const CLineSegment *>(a.get());
    bool isSecondLine = dynamic_cast<const CLineSegment *>(b.get());
    if (isFirstLine || isSecondLine)
      return false;
    return a->GetPerimeter() < b->GetPerimeter(); });

  return (it != shapes.end() ? *it : nullptr);
}

std::shared_ptr<IShape> Application::Create(const SHAPES_TYPE &shapeT) const
{
  switch (shapeT)
  {
  case SHAPES_TYPE::LINE_T:
    return CreateLine();
  case SHAPES_TYPE::CIRCLE_T:
    return CreateCircle();
  case SHAPES_TYPE::RECTANGLE_T:
    return CreateRectangle();
  case SHAPES_TYPE::TRIANGLE_T:
    return CreateTriangle();
  default:
    return nullptr;
  }
}

bool Application::ShowExitInfo(const std::vector<std::shared_ptr<IShape>> &shapes) const
{
  auto maxAreaSahpe = GetMaxArea(shapes);
  m_output << SHAPE_MAX_AREA;
  PrintInfo(maxAreaSahpe);

  auto minPerimeterShape = GetMinPerimeter(shapes);
  m_output << SHAPE_MIN_PERIMETER;
  PrintInfo(minPerimeterShape);

  return true;
}

std::shared_ptr<IShape> Application::CreateRectangle() const
{
  double width, height, x, y;
  uint32_t stroke, filling;

  if (!(m_input >> x >> y >> width >> height >> std::hex >> stroke >> filling))
  {
    m_output << INVALID_COMMAND_ARGUMENT;
    return nullptr;
  }

  return std::make_shared<CRectangle>(CPoint(x, y), width, height, stroke, filling);
}

std::shared_ptr<IShape> Application::CreateTriangle() const
{
  double x, y, x2, y2, x3, y3;
  uint32_t stroke, filling;

  if (!(m_input >> x >> y >> x2 >> y2 >> x3 >> y3 >> std::hex >> stroke >> filling))
  {
    m_output << INVALID_COMMAND_ARGUMENT;
    return nullptr;
  }

  return std::make_shared<CTriangle>(CPoint(x, y), CPoint(x2, y2), CPoint(x3, y3), stroke, filling);
}

std::shared_ptr<IShape> Application::CreateCircle() const
{
  double x, y, radius;
  uint32_t stroke, filling;

  if (!(m_input >> x >> y >> radius >> std::hex >> stroke >> filling))
  {
    m_output << INVALID_COMMAND_ARGUMENT;
    return nullptr;
  }

  return std::make_shared<CCircle>(CPoint(x, y), radius, stroke, filling);
}

std::shared_ptr<IShape> Application::CreateLine() const
{
  double x, y, x2, y2;
  uint32_t stroke, filling;

  if (!(m_input >> x >> y >> x2 >> y2 >> std::hex >> stroke))
  {
    m_output << INVALID_COMMAND_ARGUMENT;
    return nullptr;
  }

  return std::make_shared<CLineSegment>(CPoint(x, y), CPoint(x2, y2), stroke);
}
