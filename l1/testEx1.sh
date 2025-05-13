#!/bin/bash

handle_error() {
  echo "Program testing failed"
  exit 1
}

check_args() {
  if [ $args_count -ne 2 ]; then
    echo "Error: findtext.exe <file name> <text to search>"
    handle_error
  fi
}

args_count="$#"
check_args

input="$1"
searchText="$2"
output=$(./ex1 "$input" "$searchText")

check_fileWork() {
  if [ ! -e "$input" ]; then
    echo "Error: Unable to open file '$input'"
    handle_error
  fi

  if [ ! -r "$input" ]; then
    echo "Error: Failed to read the file '$input'"
    handle_error
  fi
}

compare_outputs() {
  out=$(grep -n $searchText $input | cut -d: -f1)

  if [ ! "$out" == "$output" ]; then
    echo "Error: Outputs are different"
    echo $out
    echo $output
    handle_error
  fi
}

check_fileWork
compare_outputs

echo "All tests passed!"
