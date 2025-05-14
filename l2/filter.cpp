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

std::set<std::string> ReadRudeWords()
{
  std::set<std::string> set;
  std::string rudeWords, rudeWord;
  getline(std::cin, rudeWords);
  std::istringstream stream(rudeWords);

  while (stream >> rudeWord)
    set.insert(ToLowerCase(rudeWord));

  return set;
}

std::vector<std::vector<std::string>> ReadText(const std::set<std::string> &set)
{
  std::vector<std::vector<std::string>> obscene;
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

  return obscene;
}

int PrintFilteredText(std::vector<std::vector<std::string>> &obscene)
{
  if (!obscene.size())
    return 1;

  for (const auto &lineObscene : obscene)
  {
    for (const auto &wordObscene : lineObscene)
      std::cout << wordObscene << ' ';
    std::cout << '\n';
  }

  return 0;
}

int main()
{
  std::vector<std::vector<std::string>> obscene = ReadText(ReadRudeWords());
  PrintFilteredText(obscene);

  return 0;
}
