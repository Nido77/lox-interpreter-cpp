#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <unordered_map>
#include "TokenType.hpp"
namespace nido {
    class Token {
        public:
            Token(TokenType type, std::string lexeme, std::string literal, int line, int start, int end)
                : type(type), lexeme(lexeme), literal(literal), line(line) {}
            TokenType getType() { return type; }
            std::string getLexeme() { return lexeme; }
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