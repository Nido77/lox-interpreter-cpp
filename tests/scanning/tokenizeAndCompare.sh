#!/bin/sh

folderNames=("identifiers" "keywords" "numbers" "punctuators" "strings" "whitespace")

loxsuffix="lox"
anssuffix="ans"
outputSuffix="out"


# trasverse all lox files
for folderName in "${folderNames[@]}"; do
    currentFile="${folderName}\\${folderName}.${loxsuffix}"
    ../../lox-interpreter "${currentFile}" > "${folderName}\\${folderName}.${outputSuffix}"
    echo "{$folderName} lexical anaysisdone"
done


for folderName in "${folderNames[@]}"; do
    ansFile="${folderName}\\${folderName}.${anssuffix}"
    outputFile="${folderName}\\${folderName}.${outputSuffix}"
    FC "$ansFile" "$outputFile";
done

