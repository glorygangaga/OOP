#!/bin/bash

g++ -o sameWeekDay ./sameWeekDay.cpp -std=c++17
if [ $? -ne 0 ]; then
  echo "Compilation error"
  exit 1
fi


check_errors() {
  input="$1"
  expected="$2"
  number="$3"
  output=$(echo -e "$input" | ./sameWeekDay 2>&1)
  if [ "$output" == "$expected" ]; then
    echo "Test $number passed"
  else
    echo "Test $number not passed"
  fi
}

check_errors "2025 2\n2025 2 28" "Error: Enter exactly 3 numbers (year month day)" 1
check_errors "1899 2 28\n2025 2 28" "Usage: Invalid year entered (1900 to 9999)" 2
check_errors "2025 13 28\n2025 2 28" "Usage: Invalid month entered (from 1 to 12)" 3
check_errors "2025 2 32\n2025 2 28" "Usage: Invalid day entered (from 1 to 31, depending on the month)" 4
check_errors "2025 2 28\n2024 2 28" "ERROR" 5
check_errors "2025 2 28\n2025 3 7" "Same week day" 6
check_errors "2025 2 28\n2025 3 1" "Different week days" 7
