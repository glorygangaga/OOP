#include <iostream>
#include <string>
#include <map>

const char DOUBLE_QUOTE_CHAR = '"';
const char APOSTROPHE_CHAR = '\'';
const char LESS_THAN_SIGN_CHAR = '<';
const char MORE_THAN_SIGN_CHAR = '>';
const char AMPERSAND_CHAR = '&';

const std::string DOUBLE_QUOTE_CODE = "&quot;";
const std::string APOSTROPHE_CODE = "&apos;";
const std::string LESS_THAN_SIGN_CODE = "&lt;";
const std::string MORE_THAN_SIGN_CODE = "&gt;";
const std::string AMPERSAND_CODE = "&amp;";

const std::map<char, std::string> HTML_ENTITIES = {
    {DOUBLE_QUOTE_CHAR, DOUBLE_QUOTE_CODE},
    {APOSTROPHE_CHAR, APOSTROPHE_CODE},
    {LESS_THAN_SIGN_CHAR, LESS_THAN_SIGN_CODE},
    {MORE_THAN_SIGN_CHAR, MORE_THAN_SIGN_CODE},
    {AMPERSAND_CHAR, AMPERSAND_CODE}};

std::string HtmlEncode(std::string const &text)
{
  std::string newText;
  newText.reserve(text.size());
  for (char ch : text)
  {
    auto it = HTML_ENTITIES.find(ch);
    if (it != HTML_ENTITIES.end())
      newText += it->second;
    else
      newText += ch;
  }

  return newText;
}

int main()
{
  std::string str;
  while (getline(std::cin, str))
    std::cout << HtmlEncode(str) << '\n';

  return 0;
}
