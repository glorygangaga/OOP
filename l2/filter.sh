#!/bin/bash

g++ -o filter filter.cpp
if [ $? -ne 0 ]; then
  echo "Compilation Error"
  exit 1
fi

check_errors() {
  input="$1"
  expected=$(echo -e "$2" | tr -d '\r' | sed 's/[[:space:]]*$//')
  number="$3"
  type="$4"
  output=$(echo -e "$input" | ./filter | tr -d '\r' | sed 's/[[:space:]]*$//' | sed '/^$/d')

  if [[ "$output" == "$expected" ]]; then
    echo "Test $number passed ($type)"
  else
    echo "Test $number not passed ($type)"
    echo $output | cat -A
  fi
}

check_errors $'bad\nThis is a bad word.' $'This is a word.' 1 "One rude word"
check_errors $'bad rude\nThis is a bad and rude sentence.' $'This is a and sentence.' 2 "Multiple rude words"
check_errors $'bad\nBad BAD bad word.' $'word.' 3 "Case insensitivity"
check_errors $'apple banana\nI like apples and bananas.' $'I like apples and bananas.' 4 "No rude words"
check_errors $'\nThis is a clean sentence.' $'This is a clean sentence.' 5 "No rude words list"
check_errors $'foo bar\nfoo bar baz foo bar' $'baz' 6 "All words are rude except one"
check_errors $'bad\nbad bad bad' $'' 7 "All words are rude"
check_errors $'bad\nThis is a bad sentence.\nAnother bad line.' $'This is a sentence.\nAnother line.' 8 "Multiple lines"
check_errors $'bad\n \nThis is a bad sentence.\n \nAnother bad line.' $'This is a sentence.\nAnother line.' 9 "Empty lines"
check_errors $'rude bad\nThis is a very rude and bad example.\nRude and bad indeed.' $'This is a very and example.\nand indeed.' 10 "Complex case"
check_errors "" "" 11 "Empty stream"