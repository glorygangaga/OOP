#!/bin/bash

g++ -c main.cpp shapes/App.cpp shapes/CCircle.cpp shapes/CLineSegment.cpp shapes/CRectangle.cpp shapes/CTriangle.cpp canvas/CCanvas.cpp && g++ main.o App.o CCanvas.o CCircle.o CLineSegment.o CRectangle.o CTriangle.o -o shape -lsfml-graphics -lsfml-window -lsfml-system
if [ $? -ne 0 ]; then
  echo "Compilation Error"
  exit 1
fi
rm -f main.o App.o CCanvas.o CCircle.o CLineSegment.o CRectangle.o CTriangle.o

check_errors() {
  number="$1"
  type="$2"
  input=$(cat "test/input/test$number.txt")
  expectedText=$(cat "test/output/test$number.txt")

  expected=$(echo -e $expectedText | tr -d '\r' | tr '\n' ' ' | sed 's/[[:space:]]\+/ /g' | sed 's/[[:space:]]*$//')
  output=$(echo -e "$input" | ./shape 2>&1 | sed 's/Setting vertical sync not supported //' | tr -d '\r' | tr '\n' ' ' | sed 's/[[:space:]]\+/ /g' | sed 's/[[:space:]]*$//')
  if [[ "$output" == "$expected" ]]; then
    echo "Test $number passed ($type)"
  else
    echo "Test $number not passed ($type)"
    diff <(echo "$output") <(echo "$expected")
  fi
}

check_errors 1 "Empty stream"
check_errors 2 "Rectangle"
check_errors 3 "Triangle"
check_errors 4 "Circle"
check_errors 5 "Line"
check_errors 6 "A lot of shapes"
check_errors 7 "Trash data"
check_errors 8 "Invalid arguments"
