#ifndef LOX_H
#define LOX_H
#include <string>
namespace nido {
    class Lox {
        public:
            static bool hadError;
            void runFile(char* filePath);
            static std::string fileName;
            void runPrompt();
            void run(std::string sourceCode);
            static void error(int line, const std::string message);
        private:
            static void report(int line, const std::string where, const std::string message);
    };
}
#endif
