#include <iostream>
#include <string>
#include <sstream>

const int REQUIRED_DATES = 2;
const std::string USAGE_INVALID_YEAR = "Usage: Invalid year entered (1900 to 9999)\n";
const std::string USAGE_INVALID_MONTH = "Usage: Invalid month entered (from 1 to 12)\n";
const std::string USAGE_INVALID_DAY = "Usage: Invalid day entered (from 1 to 31, depending on the month)\n";
const std::string ERROR_INVALID_INPUT = "Error: Enter exactly 3 numbers (year month day)\n";
const std::string ERROR_MESSAGE = "ERROR\n";
const std::string SAME_WEEK_DAY = "Same week day\n";
const std::string DIFFERENT_WEEK_DAY = "Different week days\n";

struct Date
{
  int year;
  int month;
  int day;
};

bool isValidInput(const std::string &input, Date &date)
{
  std::istringstream iss(input);
  if (iss >> date.year >> date.month >> date.day)
  {
    std::string extra;
    if (!(iss >> extra))
    {
      return true;
    }
  }
  return false;
}

bool isLeapYear(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const Date &date)
{
  if (date.year < 1900 || date.year > 9999)
  {
    std::cerr << USAGE_INVALID_YEAR;
    return false;
  }
  if (date.month < 1 || date.month > 12)
  {
    std::cerr << USAGE_INVALID_MONTH;
    return false;
  }
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (date.month == 2 && isLeapYear(date.year))
  {
    daysInMonth[1] = 29;
  }
  if (date.day < 1 || date.day > daysInMonth[date.month - 1])
  {
    std::cerr << USAGE_INVALID_DAY;
    return false;
  }
  return true;
}

// алгоритм Целлера
int getWeekDay(const Date &date)
{
  int year = date.year;
  int month = date.month;
  int day = date.day;
  if (month < 3)
  {
    month += 12;
    year -= 1;
  }
  int k = year % 100;
  int j = year / 100;
  int dayOfWeek = (day + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j)) % 7;
  return (dayOfWeek + 5) % 7;
}

int insertDate(Date &date)
{
  std::string input;
  std::getline(std::cin, input);
  if (!isValidInput(input, date))
  {
    std::cerr << ERROR_INVALID_INPUT;
    return 1;
  }
  if (!isValidDate(date))
    return 1;

  return 0;
}

int main()
{
  Date date1;
  Date date2;

  if (insertDate(date1) || insertDate(date2))
    return 1;

  if (date1.year != date2.year)
  {
    std::cerr << ERROR_MESSAGE;
    return 1;
  }

  bool isSameWeekDay = getWeekDay(date1) == getWeekDay(date2);
  if (isSameWeekDay)
    std::cout << SAME_WEEK_DAY;
  else
    std::cout << DIFFERENT_WEEK_DAY;

  return 0;
}
