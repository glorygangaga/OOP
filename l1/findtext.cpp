#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <vector>
#include <variant>

const std::string USAGE_ERROR_FILE = "Usage: findtext.exe <file name> <text to search>\n";
const std::string ERROR_UNABLE_FILE = "Error: Unable to open file ";
const std::string ERROR_READ_FILE = "Error: Failed to read the file ";
const std::string TEXT_NOT_FOUND = "Text not found\n";

struct Args
{
  std::string inputFileName, searchText;
};

struct Error
{
  std::string message;
};

std::optional<Args> ParseArgs(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << USAGE_ERROR_FILE;
    return std::nullopt;
  }

  Args args;
  args.inputFileName = argv[1];
  args.searchText = argv[2];

  return args;
}

std::optional<std::variant<std::vector<int>, Error>> FindTextFromInputFile(const std::string &fileName, const std::string &searchText)
{
  std::ifstream input(fileName);
  if (!input.is_open())
    return Error{ERROR_UNABLE_FILE + fileName + '\n'};

  std::vector<int> lineNumbers;
  std::string line;
  int lineNumber = 0;

  while (getline(input, line))
  {
    lineNumber++;
    if (line.find(searchText) != std::string::npos)
      lineNumbers.push_back(lineNumber);
  }

  if (input.bad())
    return Error{ERROR_READ_FILE + fileName + '\n'};

  if (lineNumbers.size() == 0)
    return std::nullopt;
  return lineNumbers;
}

int main(int argc, char *argv[])
{
  auto args = ParseArgs(argc, argv);

  if (!args)
    return 1;

  auto lineNumbers = FindTextFromInputFile(args->inputFileName, args->searchText);

  if (lineNumbers.has_value())
  {
    if (std::holds_alternative<std::vector<int>>(*lineNumbers))
      for (auto &lineNumber : std::get<std::vector<int>>(*lineNumbers))
        std::cout << lineNumber << '\n';
    else
    {
      std::cerr << std::get<Error>(*lineNumbers).message;
      return 1;
    }
  }
  else
  {
    std::cout << TEXT_NOT_FOUND;
    return 1;
  }

  return 0;
}
