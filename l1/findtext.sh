#!/bin/bash

g++ -o findtext ./findtext.cpp -std=c++17
if [ $? -ne 0 ]; then
  echo "Compilation error"
  exit 1
fi

output=$(./findtext 2>&1)
expected="Usage: findtext.exe <file name> <text to search>"
if [ "$output" == "$expected" ]; then
  echo "Test 1 passed"
else
  echo "Test 1 not passed"
fi

output=$(./findtext notExistFile.txt "text" 2>&1)
expected="Error: Unable to open file 'notExistFile.txt'"
if [ "$output" == "$expected" ]; then
  echo "Test 2 passed"
else
  echo "Test 2 not passed"
fi

echo -e "Hello world\nHello again\nGoodbye world" > testFile.txt
echo -n "" > emptyFile.txt

output=$(./findtext testFile.txt "again")
expected="2"
if [ "$output" == "$expected" ]; then
  echo "Test 3 passed"
else
  echo "Test 3 not passed"
fi

output=$(./findtext testFile.txt "Hello")
expected=$'1\n2'
if [ "$output" == "$expected" ]; then
  echo "Test 4 passed"
else
  echo "Test 4 not passed"
fi

output=$(./findtext testFile.txt "Random text")
expected="Text not found"
if [ "$output" == "$expected" ]; then
  echo "Test 5 passed"
else
  echo "Test 5 not passed"
fi

output=$(./findtext emptyFile.txt "Random text")
expected="Text not found"
if [ "$output" == "$expected" ]; then
  echo "Test 6 passed"
else
  echo "Test 6 not passed"
fi

rm -f testFile.txt emptyFile.txt