#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "LoxInterpreter.hpp"
namespace nido {
    bool LoxInterpreter::hadError = false;
    void LoxInterpreter::runFile(char* path) {
        if (hadError) {
            std::cerr << "Error occurred. Please fix it before proceeding." << std::endl;
        }
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }

        std::ostringstream contentStream;
        contentStream << inputFile.rdbuf();
        Scanner scanner = Scanner(contentStream.str(), path);
        scanner.scanTokens();
        scanner.printAllTokens();
    }

    void LoxInterpreter::runREPL() {
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

    // Todo
    std::string LoxInterpreter::interpret(std::string sourceCode) {
        return sourceCode;
    }

    void LoxInterpreter::error(int line, std::string message) {
        std::cerr << "Error at line [" << line << "] : " << message << std::endl;
    }
}