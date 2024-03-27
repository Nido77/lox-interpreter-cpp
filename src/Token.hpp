#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include <unordered_map>
#include "TokenType.hpp"
// overload << operator
namespace nido {
    class Token {
        public:
            Token(TokenType type, std::string lexeme, int line)
                : type(type), lexeme(lexeme), line(line) {}
            static std::unordered_map<TokenType, std::string> tokenTypeToStr;
            friend std::ostream& operator<<(std::ostream& os, Token& t);
            TokenType getType() const { return type;}
            std::string getLexeme() const{ return lexeme;}
            std::string getTypeStr() const  { return tokenTypeToStr[type];}
            std::string getLiteral();
            int getLine() const { return line; }
        private:
            const TokenType type;
            const std::string lexeme;
            const int line;
    };
}
#endif