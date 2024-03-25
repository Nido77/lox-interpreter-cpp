#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.hpp"
namespace nido {
    class Scanner {
        public:
            Scanner(std::string sourceCode) : sourceCode(sourceCode), currentPos(0), line(1) {}
            std::vector<Token> scanTokens();
            std::vector<Token> scanToken();
        private:
            std::string sourceCode;
            std::vector<Token> tokens;
            inline bool isAtEnd();
            char void advance();
            inline void goback();
            inline char getCurrentChar();
            inline char getNextChar();
            void addToken(TokenType type);

            int currentPos;
            static int line;
    };
}
#endif