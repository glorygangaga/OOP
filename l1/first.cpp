#include <iostream>
#include <fstream>
#include <optional>
#include <string>
// #include <cstdlib>
#include "first.h"

struct Args
{
  std::string intputFileName;
  std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cout << "Invalid arguments count\n";
    std::cout << "Usage: copyfile.exe ...\n";
    return std::nullopt;
  }

  Args args;
  args.intputFileName = argv[1];
  args.outputFileName = argv[2];

  return args;
}

void copyStreams(std::fstream &input, std::ofstream &output)
{
  char ch;
  while (input.get(ch))
  {
    if (!output.put(ch))
      break;
  }
}

int main(int argc, char *argv[])
{
  auto args = ParseArgs(argc, argv);

  if (!args)
    return 1;

  std::fstream input;
  input.open(args->intputFileName);
  if (!input.is_open())
  {
    std::cout << "File " << args->intputFileName << " can't to be open.";
    return 1;
  }

  std::ofstream output;
  output.open(args->outputFileName);
  if (!output.is_open())
  {
    std::cout << "File " << args->outputFileName << " can't to be open.";
    return 1;
  }

  copyStreams(input, output);

  if (input.bad())
  {
    std::cout << "Failed to read ...";
    return 1;
  }

  if (!output.flush())
  {
    std::cout << "Failed to write...";
    return 1;
  }

  // system("./tests.sh");
  return 0;
}
