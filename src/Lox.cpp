#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Token.hpp"
#include "Lox.hpp"
#include "Scanner.hpp"
namespace nido {
    bool Lox::hadError = false;
    std::string Lox::fileName = "";
    
    void Lox::runFile(char* filePath) {
        std::ifstream inputFile(filePath);
        fileName = filePath;
        if (!inputFile) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }
        std::ostringstream contentStream;
        contentStream << inputFile.rdbuf();
        run(contentStream.str());
        if (hadError) {
            exit(65);
        }
    }

    void Lox::runPrompt() {
        for (;;) {
            std::cout << "> ";
            std::string line;
            std::getline(std::cin, line);
            // if (line =="") {
            //     break;
            // }
            run(line);
            hadError = false;
        }
    }

    void Lox::run(std::string sourceCode) {
        Scanner scanner(sourceCode);
        std::vector<Token> tokens = scanner.scanTokens();

        for (auto token : tokens) {
            std::cout << token << std::endl;
        }
    }

    void Lox::error(int line, const std::string message) {
        report(line, "", message);
    }

    void Lox::report(int line, const std::string where, const std::string message) {
        std::cerr << "[line " << line << "] Error" << where << ":" << message << std::endl; 
        hadError = true; 
    }
}