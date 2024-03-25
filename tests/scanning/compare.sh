#!/bin/sh
#windows

identifiers="identifiers"
file1="$identifiers.ans"
file2="$identifiers.out"

if FC "$file1" "$file2" > /dev/null; then
  echo "The files are identical."
else
  echo "The files are different."
fi