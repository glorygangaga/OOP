#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <unordered_map>

const std::string TRIANGLE = "triangle";
const std::string RECTANGLE = "rectangle";
const std::string CIRCLE = "circle";
const std::string LINE_SEGMENT = "line";

const std::string PRINT_AREA = "Area: ";
const std::string PRINT_PERIMETER = "Perimeter: ";
const std::string PRINT_OUTLINE_COLOR = "Outline color: ";
const std::string PRINT_INLINE_COLOR = "Fill color: ";
const std::string PRINT_VERTEX_1 = "Vertex 1: ";
const std::string PRINT_VERTEX_2 = "Vertex 2: ";
const std::string PRINT_VERTEX_3 = "Vertex 3: ";
const std::string PRINT_LEFTTOP = "Left top: ";
const std::string PRINT_RIGHTBOTTOM = "Right bottom: ";
const std::string PRINT_WIDTH = "Width: ";
const std::string PRINT_HEIGHT = "Height: ";
const std::string PRINT_CENTER = "Center: ";
const std::string PRINT_RADIUS = "Radius: ";
const std::string PRINT_X = "x: ";
const std::string PRINT_Y = "y: ";
const std::string PRINT_START_POINT = "Start point: ";
const std::string PRINT_END_POINT = "End point: ";
const std::string PRINT_HEX_NUMBER = "0x";

const std::string UNKNOWN_COMMAND = "Unknown command\n";
const std::string INVALID_COMMAND_ARGUMENT = "Invalid command argument\n";
const std::string INVALID_CORNER_VALUE = "Invalid corner value\n";
const std::string ERROR_CANT_CREATE_WINDOW = "Failed to create window\n";

const std::string NO_SHAPES_AVAILABLE = "No shapes available\n";
const std::string SHAPE_MAX_AREA = "Shape with max area:\n";
const std::string SHAPE_MIN_PERIMETER = "Shape with min perimeter:\n";

const std::string TRIANGLE_TYPE = "Triangle";
const std::string RECTANGLE_TYPE = "Rectangle";
const std::string CIRCLE_TYPE = "Circle";
const std::string LINE_SEGMENT_TYPE = "Line";

const double PI = 3.141592653589793238463;
const int CHANGE_ANGLE = 180;
const double THICKNESS = 2.0;

const int WINDOW_SIZE = 500;
const std::string WINDOW_NAME = "Draw window";

const short CONSTANT_OF_CIRCLE = 2;
const short POINTS_OF_RECTANGLES = 6;
const size_t RECTANGLE_POINTS = 4;
const unsigned short INDICES[] = {0, 1, 2, 1, 2, 3};

const short SIZE_OF_RED_COLOR = 16;
const short SIZE_OF_GREEN_COLOR = 8;
const short GET_SIZE_COLOR = 0xFF;

enum class SHAPES_TYPE
{
  LINE_T = 0,
  CIRCLE_T,
  RECTANGLE_T,
  TRIANGLE_T
};

const std::unordered_map<std::string, SHAPES_TYPE> SHAPES_MAP = {
    {TRIANGLE, SHAPES_TYPE::TRIANGLE_T},
    {RECTANGLE, SHAPES_TYPE::RECTANGLE_T},
    {LINE_SEGMENT, SHAPES_TYPE::LINE_T},
    {CIRCLE, SHAPES_TYPE::CIRCLE_T}};

#endif