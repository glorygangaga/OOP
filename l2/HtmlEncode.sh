#!/bin/bash

g++ -o HtmlEncode ./HtmlEncode.cpp
if [ $? -ne 0 ]; then
  echo "Compilation Error"
  exit 1
fi

check_errors() {
  input="$1"
  expected="$2"
  number="$3"
  type="$4"
  
  output=$(echo -e "$input" | ./HtmlEncode)
  
  if [[ "$output" == "$expected" ]]; then
    echo "Test $number passed ($type)"
  else
    echo "Test $number not passed ($type)"
  fi
}

check_errors "\"" "&quot;" 1 "Double quote"
check_errors "'" "&apos;" 2 "Apostrophe"
check_errors "<" "&lt;" 3 "Less than sign"
check_errors ">" "&gt;" 4 "More than sign"
check_errors "&" "&amp;" 5 "Ampersand"
check_errors "Hello, World!" "Hello, World!" 6 "No special characters"
check_errors "5 > 3" "5 &gt; 3" 7 "Greater than comparison"
check_errors "x < y && y > z" "x &lt; y &amp;&amp; y &gt; z" 8 "Multiple entities"
check_errors "\"<script>alert('XSS')</script>\"" "&quot;&lt;script&gt;alert(&apos;XSS&apos;)&lt;/script&gt;&quot;" 9 "XSS script example"
check_errors "Rock & Roll" "Rock &amp; Roll" 10 "Ampersand in text"
check_errors "" "" 11 "Empty stream"