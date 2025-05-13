#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

const std::string ERROR_EMPTY_STREAM = "Error: stream is empty\n";
const std::string ERROR_MESSAGE = "ERROR\n";

bool IsDouble(const std::string element)
{
  try
  {
    std::stod(element);
    return true;
  }
  catch (...)
  {
    return false;
  }
}

int ReadNumbers(std::vector<double> &elements)
{
  std::string line, word;
  getline(std::cin, line);
  if (line.size() == 0)
  {
    std::cout << ERROR_EMPTY_STREAM;
    return 1;
  }

  std::istringstream stream(line);

  while (stream >> line)
    if (IsDouble(line))
      elements.push_back(std::stod(line));
    else
    {
      std::cerr << ERROR_MESSAGE;
      return 1;
    }

  return 0;
}

int ProcessNumbers(std::vector<double> &elements)
{
  const double min_element = *std::min_element(elements.begin(), elements.end());
  for (int i = 0; i < elements.size(); i++)
    elements[i] *= min_element;

  return 0;
}

int PrintSortedNumbers(std::vector<double> &elements)
{
  for (auto number : elements)
    std::cout << std::fixed << std::setprecision(3) << number << ' ';
  std::cout << '\n';

  return 0;
}

int main()
{
  std::vector<double> elements;
  if (ReadNumbers(elements) || ProcessNumbers(elements) || PrintSortedNumbers(elements))
    return 1;

  return 0;
}
