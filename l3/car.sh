#!/bin/bash

g++ -o car ./main.cpp ./app.cpp ./car.cpp -std=c++17
if [ $? -ne 0 ]; then
  echo "Compilation Error"
  exit 1
fi

check_errors() {
  input="$1"
  expected=$(echo -e "$2" | tr -d '\r' | sed 's/[[:space:]]*$//')
  number="$3"
  type="$4"
  output=$(echo -e "$input" | ./car 2>&1 | tr -d '\r' | sed 's/[[:space:]]*$//')

  if [[ "$output" == "$expected" ]]; then
    echo "Test $number passed ($type)"
  else
    echo "Test $number not passed ($type)"
  fi
}

check_errors "EngineOn\nInfo\n" "Engine: on\nDirection: standing still\nSpeed: 0\nGear: 0\n" 1 "Start Engine"
check_errors "EngineOn\nSetGear 1\nSetSpeed 15\nInfo\n" "Engine: on\nDirection: forward\nSpeed: 15\nGear: 1\n" 2 "Check change speed"
check_errors "EngineOn\nSetGear 1\nSetSpeed 10\nEngineOff\n" "Car must be stopped and in neutral gear\n" 3 "Stop Engine When Moving"
check_errors "EngineOn\nSetGear 1\nSetSpeed 19\nSetGear 2\n" "Unsuitable current speed\n" 4 "Setting the transmission at an inappropriate speed"
check_errors "EngineOn\nSetGear 6\n" "Invalid gear\n" 5 "Set Invalid Gear"
check_errors "EngineOn\nSetGear 1\nSetSpeed 20\nInfo\n" "Engine: on\nDirection: forward\nSpeed: 20\nGear: 1\n" 6 "Set Valid Gear and Speed"
check_errors "EngineOn\nSetGear 1\nSetSpeed 10\nSetGear -1\n" "Cannot reverse while moving\n" 7 "Reverse Gear When Moving"
check_errors "" "" 8 "Empty stream"

