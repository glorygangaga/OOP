#!/bin/bash

g++ -o frequence frequence.cpp
if [ $? -ne 0 ]; then
  echo "Compilation Error"
  exit 1
fi

check_errors() {
  input="$1"
  expected="$2"
  number="$3"
  type="$4"
  output=$(echo -e "$input" | ./frequence | sed '/^$/d')
  if [[ "$output" == "$expected" ]]; then
    echo "Test $number passed ($type)"
  else
    echo "Test $number not passed ($type)"
  fi
}

check_errors "hello world" $'hello → 1\nworld → 1' 1 "Two different words"
check_errors "Hello hello HELLO" $'hello → 3' 2 "Case insensitivity"
check_errors "one one one two two three" $'one → 3\nthree → 1\ntwo → 2' 3 "Multiple repetitions"
check_errors "a a A a A" $'a → 5' 4 "Single character case insensitivity"
check_errors "123 123 abc ABC abc" $'123 → 2\nabc → 3' 5 "Mixed numbers and letters"
check_errors "Hello, world! Hello." $'hello, → 1\nhello. → 1\nworld! → 1' 6 "Words with punctuation"
check_errors "" "" 7 "Empty input"
check_errors "Word" $'word → 1' 8 "Single word"
check_errors "   multiple   spaces    between    words   " $'between → 1\nmultiple → 1\nspaces → 1\nwords → 1' 9 "Multiple spaces"
check_errors "one two two three three three" $'one → 1\nthree → 3\ntwo → 2' 10 "Words with different frequencies"
check_errors "" "" 11 "Empty stream"