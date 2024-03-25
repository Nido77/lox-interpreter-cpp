#include <iostream>
#include "src/Loxinterpreter.hpp"
int main(int argc, char** argv) {
    nido::LoxInterpreter interpreter;
    if (argc > 2) {
        std::cout << "Usage: ./lox-interpreter [script] \
                      \n       ./lox-interpreter to run REPL" << std::endl;
        return 1;
    } else if (argc == 2) {
        interpreter.runFile(argv[1]);
    } else {
        interpreter.runREPL();
    }
}