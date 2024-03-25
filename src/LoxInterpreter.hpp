#ifndef LOXINTERPRETER_H
#define LOXINTERPRETER_H
#include<string>
namespace nido {
    class LoxInterpreter {
        public:
            static bool hadError;
            void runFile(char* path);
            void runREPL();
            static void error(int line, std::string message);
        private:
            std::string interpret(std::string sourceCode); 

    };
    bool LoxInterpreter::hadError = false;
}
#endif