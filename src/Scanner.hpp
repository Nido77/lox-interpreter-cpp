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
            Scanner(std::string sourceCode) : sourceCode(sourceCode), start(0), current(0), line(1) {}
            std::vector<Token> scanTokens();
            std::string getSourceCode() const{ return sourceCode; }
            std::string fileName;
            int getTokensSize() const { return tokens.size(); }
        private:
            std::string sourceCode;
            std::vector<Token> tokens;
            int start;
            int line;
            int current;
            inline bool isAtEnd();
            void scanToken();
            char advance();
            void addToken(TokenType type);
            bool match(char expected);
            char peek();
            char peekNext();
            void scanString();
            void scanNumber();
            void scanIdentifierOrKeyword();
            bool isAplhaNumber(char c) const {
                return isalpha(c) || isdigit(c) || c == '_';
            };
            static std::unordered_map<std::string, TokenType> keywords;
    };
}

#endif