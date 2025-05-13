#!/bin/bash

g++ -o multmatrix ./multmatrix.cpp -std=c++17
if [ $? -ne 0 ]; then
  echo "Compilation error"
  exit 1
fi

# READ FROM FILE TESTS

emptyText=""
rightText="1.15 2.64 10.14\n12.14a 6.42 1\n64.53 31.53 75.5"
rightText2="10.41 1.3 0\n12 7.53 53.75\n342.6 1.01 132"
errorText1="1 2 3\n4 4 6\n7 8 NOT_DOUBLE"
errorText2="1 2 3\n4 6\n7 8 0"
errorText3="1 2 3\n4 5 6\n7 8 1 1"
errorText4="1 2 3\n4 4 6\n7 8 9\n1"

echo -e "$emptyText" > emptyInput.txt
echo -e "$rightText" > rightInput1.txt
echo -e "$rightText2" > rightInput2.txt
echo -e "$errorText1" > errorInput1.txt
echo -e "$errorText2" > errorInput2.txt
echo -e "$errorText3" > errorInput3.txt
echo -e "$errorText4" > errorInput4.txt

echo "FILE TESTS:"

output=$(./multmatrix rightInput1.txt notExsistFile.txt 2>&1)
expected="Error: Unable to open file notExsistFile.txt"
if [ "$output" == "$expected" ];then 
  echo "Test 1 passed (Unable to open file)"
else
  echo "Test not 1 passed (Unable to open file)"
fi

output=$(./multmatrix rightInput1.txt errorInput1.txt 2>&1)
expected=$'ERROR\nError: Incorrect data entered'
if [ "$output" == "$expected" ];then 
  echo "Test 2 passed (Incorrect data - char not double)"
else
  echo "Test not 2 passed (Incorrect data)"
fi

output=$(./multmatrix rightInput1.txt errorInput2.txt 2>&1)
expected=$'ERROR\nError: Incorrect data entered'
if [ "$output" == "$expected" ];then 
  echo "Test 3 passed (Incorrect data type - not enough numbers)"
else
  echo "Test not 3 passed (Incorrect data type - 2)"
fi


output=$(./multmatrix rightInput1.txt errorInput3.txt 2>&1)
expected=$'ERROR\nError: Enter exactly 3 numbers'
if [ "$output" == "$expected" ];then 
  echo "Test 4 passed (Incorrect numbers in line)"
else
  echo "Test not 4 passed (Incorrect numbers in line)"
fi

output=$(./multmatrix rightInput1.txt errorInput4.txt 2>&1)
expected=$'ERROR\nError: incorrect input values in file'
if [ "$output" == "$expected" ];then 
  echo "Test 5 passed (Incorrect input values)"
else
  echo "Test not 5 passed (Incorrect input values)"
fi

output=$(./multmatrix rightInput1.txt rightInput2.txt 2>&1)
expected=$'3517.616 31.616 1480.380 \n546.017 65.135 477.075 \n26916.417 397.565 11660.737 '
if [ "$output" == "$expected" ];then 
  echo "Test 6 passed (Correct numbers)"
else
  echo "Test not 6 passed (Correct numbers)"
fi

output=$(./multmatrix emptyInput.txt emptyInput.txt 2>&1)
expected=$'ERROR\nError: Incorrect data entered'
if [ "$output" == "$expected" ];then 
  echo "Test 7 passed (Empty input)"
else
  echo "Test not 7 passed (Empty input file)"
fi

output=$(./multmatrix notExistFile notExistFile2 2>&1)
expected=$'Error: Unable to open file notExistFile'
if [ "$output" == "$expected" ];then 
  echo "Test 8 passed (Not exist file)"
else
  echo "Test not 8 passed (Not exist file)"
  echo $output
fi

rm -f rightInput1.txt rightInput2.txt errorInput1.txt errorInput2.txt errorInput3.txt errorInput4.txt emptyInput.txt
echo
# READ FROM STREAM TESTS

check_errors() {
  input="$1"
  expected=$(echo "$2" | tr -s ' ' | tr -d '\n')
  number="$3"
  type="$4"

  output=$(echo -e "$input" | ./multmatrix 2>&1 | tr -s ' ' | tr -d '\n')
  if [[ "$output" == "$expected" ]]; then
    echo "Test $number passed ($type)"
  else
    echo "Test $number not passed ($type)"
  fi
}

echo "STREAM TESTS:"
check_errors "$rightText\n$errorText1" $'ERROR\nError: Incorrect data entered' 1 "Incorrect data - char not double"
check_errors "$rightText\n$errorText2" $'ERROR\nError: Incorrect data entered' 2 "Incorrect data - not enough numbers"
check_errors "$rightText\n$errorText3" $'ERROR\nError: Enter exactly 3 numbers' 3 "Incorrect numbers in line"
check_errors "$rightText\n$rightText2" $'3517.616 31.616 1480.380 \n546.017 65.135 477.075 \n26916.417 397.565 11660.737 ' 4 "Correct numbers"
check_errors "" $'ERROR\nError: Incorrect data entered' 5 "Empty input"