#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

template <typename T>
bool FindMax(std::vector<T> const &arr, T &maxValue)
{
  if (arr.empty())
    return false;

  maxValue = *std::max_element(arr.begin(), arr.end());
  return true;
}

template <>
bool FindMax<const char *>(std::vector<const char *> const &arr, const char *&maxValue)
{
  if (arr.empty())
    return false;

  maxValue = *std::max_element(arr.begin(), arr.end(), [](const char *a, const char *b)
                               { return std::strcmp(a, b) < 0; });

  return true;
}

int main()
{
  std::vector<int> vec = {5, 6, 2, 7, 10, 132};
  std::vector<std::string> vec2 = {"", "fwefw", "fwe", "sdffew", "fw", "zrgujeurj", "s"};
  std::vector<double> vec3 = {4.312, 423.64, 42.75, 666.66, 1.999999};
  std::vector<const char *> vec4 = {"", "fwefw", "fwe", "sdffew", "fw", "zrgujeurj", "s"};

  int maxVal;
  std::string stringVal;
  double maxValD;
  const char *ArrStringVal;

  FindMax(vec, maxVal);
  FindMax(vec2, stringVal);
  FindMax(vec3, maxValD);
  FindMax(vec4, ArrStringVal);

  std::cout << maxVal << '\n';
  std::cout << stringVal << '\n';
  std::cout << maxValD << '\n';
  std::cout << ArrStringVal << '\n';

  return 0;
}