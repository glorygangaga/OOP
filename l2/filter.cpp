#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

std::string ToLowerCase(const std::string &str)
{
  std::string lowerStr;
  lowerStr.reserve(str.size());

  for (const unsigned char ch : str)
    lowerStr += std::tolower(ch);
  return lowerStr;
}

void ReadRudeWords(std::set<std::string> &set)
{
  std::string rudeWords, rudeWord;
  getline(std::cin, rudeWords);
  std::istringstream stream(rudeWords);
  while (stream >> rudeWord)
    set.insert(ToLowerCase(rudeWord));
}

void ReadText(std::vector<std::vector<std::string>> &obscene, const std::set<std::string> &set)
{
  std::string line;
  while (getline(std::cin, line))
  {
    obscene.push_back({});
    std::string word;
    std::istringstream stream(line);
    while (stream >> word)
      if (set.find(ToLowerCase(word)) == set.end())
        obscene.back().push_back(word);
  }
}

void PrintFilteredText(std::vector<std::vector<std::string>> &obscene)
{
  for (const auto &lineObscene : obscene)
  {
    for (const auto &wordObscene : lineObscene)
      std::cout << wordObscene << ' ';
    std::cout << '\n';
  }
}

int main()
{
  std::set<std::string> set;
  std::vector<std::vector<std::string>> obscene;

  ReadRudeWords(set);
  ReadText(obscene, set);
  PrintFilteredText(obscene);

  return 0;
}
