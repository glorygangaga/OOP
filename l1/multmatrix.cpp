#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

const int MATRICES_SIZE = 2;
const int MATRIX_SIZE = 3;
const int MATRIX_ELEMENTS = MATRIX_SIZE * MATRIX_SIZE;
const int NUMBERS_AFTER_ZERO = 3;
const int READ_FROM_STREAM = 4;

const std::string ERROR_MESSAGE = "ERROR\n";
const std::string ERROR_INCORRECT_DATA = "Error: Incorrect data entered\n";
const std::string ERROR_UNREAD_FILE = "Error: Failed to read file ";
const std::string ERROR_UNABLE_FILE = "Error: Unable to open file ";
const std::string ERROR_INCOEERCT_FILE_INPUT = "Error: incorrect input values in file\n";
const std::string ERROR_INCORRECT_NUMBER_COUNT = "Error: Enter exactly 3 numbers\n";

struct Args
{
  std::string firstInputFileName, secondInputFileName;
};

std::optional<Args> ParseArgs(int argc, char *argv[])
{
  if (argc != 3)
    return std::nullopt;
  Args args;
  args.firstInputFileName = argv[1];
  args.secondInputFileName = argv[2];
  return args;
}

bool IsDouble(const std::string &str)
{
  try
  {
    std::stod(str);
    return true;
  }
  catch (...)
  {
    return false;
  }
}

int CheckMatrixErrors(std::string elements[4], const std::string input)
{
  std::istringstream iss(input);

  if (!(iss >> elements[0] >> elements[1] >> elements[2]) || !IsDouble(elements[0]) || !IsDouble(elements[1]) || !IsDouble(elements[2]))
  {
    std::cout << ERROR_MESSAGE;
    std::cerr << ERROR_INCORRECT_DATA;
    return 1;
  }

  if (iss >> elements[3])
  {
    std::cout << ERROR_MESSAGE;
    std::cerr << ERROR_INCORRECT_NUMBER_COUNT;
    return 1;
  }

  return 0;
}

int ReadMatrixFromFile(const std::string &filename, double matrix[MATRIX_ELEMENTS])
{
  std::fstream inputFile(filename);

  if (!inputFile.is_open())
  {
    std::cerr << ERROR_UNABLE_FILE << filename << '\n';
    return 1;
  }
  std::string input;
  int count = 0;

  while (getline(inputFile, input))
  {
    std::string elements[READ_FROM_STREAM];

    if (count > 2)
    {
      std::cout << ERROR_MESSAGE;
      std::cerr << ERROR_INCOEERCT_FILE_INPUT;
      return 1;
    }
    if (CheckMatrixErrors(elements, input))
      return 1;

    for (size_t i = 0; i < MATRIX_SIZE; i++)
      matrix[i + MATRIX_SIZE * count] = std::stod(elements[i]);
    count++;
  }

  if (inputFile.bad())
  {
    std::cerr << ERROR_UNREAD_FILE << filename << "\n";
    return 1;
  }

  return 0;
}

int ReadMatrixFromStream(double matrix[MATRIX_ELEMENTS])
{
  for (size_t j = 0; j < MATRIX_SIZE; j++)
  {
    std::string elements[READ_FROM_STREAM];
    std::string input;
    std::getline(std::cin, input);

    if (CheckMatrixErrors(elements, input))
      return 1;

    size_t rowIndex = j * MATRIX_SIZE;

    for (size_t k = 0; k < MATRIX_SIZE; k++)
      matrix[rowIndex + k] = std::stod(elements[k]);
  }
  std::cout << '\n';
  return 0;
}

int MultiplyMatrices(double firstMatrix[MATRIX_ELEMENTS], double secondMatrix[MATRIX_ELEMENTS])
{
  for (size_t i = 0; i < MATRIX_SIZE; i++)
  {
    size_t rowIndex = i * MATRIX_SIZE;

    for (size_t j = 0; j < MATRIX_SIZE; j++)
    {
      double sum = 0;
      size_t colIndex = j;

      for (size_t k = 0; k < MATRIX_SIZE; k++)
        sum += firstMatrix[rowIndex + k] * secondMatrix[colIndex + MATRIX_SIZE * k];

      std::cout << std::fixed << std::setprecision(NUMBERS_AFTER_ZERO) << sum << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}

int main(int argc, char *argv[])
{
  auto args = ParseArgs(argc, argv);
  double matrices[MATRICES_SIZE][MATRIX_ELEMENTS];
  if (!args)
  {
    if (ReadMatrixFromStream(matrices[0]) || ReadMatrixFromStream(matrices[1]))
      return 1;
  }
  else if (ReadMatrixFromFile(args->firstInputFileName, matrices[0]) || ReadMatrixFromFile(args->secondInputFileName, matrices[1]))
    return 1;

  MultiplyMatrices(matrices[0], matrices[1]);

  return 0;
}
