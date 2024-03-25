#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <unordered_map>
#include "TokenType.hpp"
namespace nido {
    class Token {
        public:
            Token(TokenType type, std::string lexeme, std::string literal, int line)
                : type(type), lexeme(lexeme), literal(literal), line(line) {}
            static std::unordered_map<TokenType, std::string> tokenTypeToStr;
            TokenType getType() { return type; }
            std::string getLexeme() { return lexeme; }
            std::string getTypeStr() { return tokenTypeToStr[type];}
            std::string getLiteral() { return literal; }
            int getLine() { return line; }
        private:
            TokenType type;
            std::string lexeme;
            std::string literal;
            int line;
    };
}
#endif