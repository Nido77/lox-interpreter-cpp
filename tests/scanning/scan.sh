#!/bin/sh

prefixes=("identifiers" "keywords" "numbers" "punctuators" "strings" "whitespace")

loxsuffix="lox"
outputSuffix="out"

# trasverse all lox files
for prefix in "${prefixes[@]}"; do
    currentFile="${prefix}.${loxsuffix}"
    ../../lox-interpreter "${currentFile}" > "${prefix}.${outputSuffix}"
    echo "done"
done
