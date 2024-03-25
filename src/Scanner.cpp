#include "Scanner.hpp"
namespace nido {
    bool Scanner::isAtEnd() {
        return current > sourceCode.length();
    }

    void addToken(TokenType type, std::string lexeme) {
        tokens.push_back(Token(type, lexeme, "", line));
    }

    std::vector<Token> Scanner::scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }
       addToken(TokenType::END_OF_FILE, "");
    }

    std::vector<Token> Scanner::scanToken() {
        // lookahead(1)
        ch c = advance();
        
        while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            if (c == '\n') {
                line++;
            }
            c = advance();
        }
        switch (c) {
            case '(':
                addToken(TokenType::LEFT_PAREN, "(");
                break;
            case ')':
                addToken(TokenType::RIGHT_PAREN, ")");
                break;
            case '{':
                addToken(TokenType::LEFT_BRACE, "{");
                break;
            case '}':
                addToken(TokenType::RIGHT_BRACE, "}");
                break;
            case ',':
                addToken(TokenType::COMMA, ",");
                break;
            case '.':
                addToken(TokenType::DOT, ".");
                break;
            case '-':
                addToken(TokenType::MINUS, "-");
                break;
            case '+':
                addToken(TokenType::PLUS, "+");
                break;
            case ';':
                addToken(TokenType::SEMICOLON, ";");
                break;
            case '*':
                addToken(TokenType::STAR, "*");
                break;

        }
        // lookahead(2)
        
    }
    char Scanner::advance() {
        ++current;
        return sourceCode[current-1];
    }
    char Scanner::getCurrentChar() {
        return sourceCode[current];
    }
    char Scanner::nextChar() {
        return current+1 > sourceCode.length() ? '\0' : sourceCode[current+1];
    }
    void Scanner::goback() {
        --current;
    }
}