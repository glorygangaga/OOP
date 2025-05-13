#!/bin/bash

g++ -o minElement ./minElement.cpp
if [ $? -ne 0 ]; then
  echo "Compilation Error"
  exit 1
fi

check_errors() {
  input="$1"
  expected=$(echo -e "$2" | tr -d '\r' | sed 's/[[:space:]]*$//')
  number="$3"
  type="$4"
  output=$(echo -e "$input" | ./minElement 2>&1 | tr -d '\r' | sed 's/[[:space:]]*$//')

  if [[ "$output" == "$expected" ]]; then
    echo "Test $number passed ($type)"
  else
    echo "Test $number not passed ($type)"
    echo $output
  fi
}

check_errors "5.5" $'30.250\n' 1 "with one number"
check_errors "1 2 3 4 5" $'1.000 2.000 3.000 4.000 5.000\n' 2 "with some numbers"
check_errors "-3 -2 -1 0 1 2 3" $'9.000 6.000 3.000 -0.000 -3.000 -6.000 -9.000\n' 3 "with negative numbers"
check_errors "12 12 abc 10 2" $'ERROR\n' 4 "with incorrect data"
check_errors "0.001 0.002 0.003" $'0.000 0.000 0.000\n' 5 "with a large numbers of decimal places"
check_errors "1000000000 2000000000 3000000000" $'1000000000000000000.000 2000000000000000000.000 3000000000000000000.000\n' 6 "with a large numbers"
check_errors "" $'Error: stream is empty\n' 7 "empty stream"