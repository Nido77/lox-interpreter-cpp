#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.hpp"
#include "TokenType.hpp"
namespace nido {
    class Scanner {
        public:
            Scanner(std::string sourceCode, std::string fileName) : sourceCode(sourceCode), fileName(fileName), currentPos(-1), line(1), linePos(0), hasError(false) {}
            void scanTokens();
            static std::unordered_map<std::string, TokenType> keywords;
            static std::unordered_map<std::string, TokenType> lookahead;
            void printAllTokens();
            std::string getSourceCode() { return sourceCode; }
            std::string fileName;
        private:
            std::string sourceCode;
            std::vector<Token> tokens;
            int currentPos;
            int line;
            int linePos;
            bool hasError;
            inline bool isAtEnd();
            char advance();
            inline void goback();
            inline char getCurrentChar();
            inline char getNextChar();
            void addToken(TokenType type, std::string lexeme, std::string literal);
            void error();
            void scanLookahead();
            bool isLookahead(char ch);
            void scanNums();
            void scanIdentifiersOrKeywords();
            void scanComment();
            void scanString();
    };
}

#endif