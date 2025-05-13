#include <iostream>
#include <map>
#include <string>
#include <algorithm>

const std::string ARROW = " → ";

std::string ToLowerCase(std::string str)
{
  std::string strLower;
  strLower.reserve(str.size());
  for (const unsigned char ch : str)
    strLower += std::tolower(ch);
  return strLower;
}

int main()
{
  std::map<std::string, int> map;
  std::string str;
  while (std::cin >> str)
  {
    std::string word = ToLowerCase(str);
    map[word]++;
  }

  std::cout << '\n';
  for (const auto &pair : map)
    std::cout << pair.first << ARROW << pair.second << '\n';

  return 0;
}