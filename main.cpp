#include <iostream>
#include "src/Lox.hpp"

int main(int argc, char** argv) {
    // in cpp argv[0] is the programme name
    nido::Lox loxInterpreter;
    if (argc > 2) {
        std::cout << "Usage: cpplox [filePath]" << std::endl;
    } else if (argc == 2) {
        loxInterpreter.runFile(argv[1]);
    } else if (argc == 1) {
        loxInterpreter.runPrompt();
    }
}