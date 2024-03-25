#include <iostream>
#include <string>
#include "LoxInterpreter.hpp"
void nido::LoxInterpreter::runFile(char* path) {
    if (hadError) {
        // todo 
    }
    std::cout << "Running file: " << path << std::endl;
}

void nido::LoxInterpreter::runREPL() {
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line == "quit()") {
            break;
        }
        if (hadError) {
            std::cerr << "Error occurred. Please fix it before proceeding." << std::endl;
            return;
        }
        std::cout << interpret(line) << std::endl;
    }
}

std::string nido::LoxInterpreter::interpret(std::string sourceCode) {
    return sourceCode;
}

void nido::LoxInterpreter::error(int line, std::string message) {
    std::cerr << "Error at line [" << line << "] : " << message << std::endl;
}
