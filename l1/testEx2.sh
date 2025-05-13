#!/bin/bash

handle_error() {
  echo "Program testing failed"
  exit 1
}

output = $(./ex2)

echo $output