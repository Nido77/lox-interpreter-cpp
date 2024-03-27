#include <iostream>
#include <cctype>
#include "Scanner.hpp"
#include "Lox.hpp"
namespace nido {
    std::unordered_map<std::string, TokenType> Scanner::keywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}
    };


    bool Scanner::isAtEnd() {
        unsigned int currentLength = static_cast<unsigned int>(current);
        unsigned int sourceLength = sourceCode.length();
        return currentLength >= sourceLength;
    }

    char Scanner::advance() {
        current++;
        return sourceCode[current - 1];
    }

    void Scanner::addToken(TokenType type) {
        std::string text = sourceCode.substr(start, current - start);
        tokens.push_back(Token(type, text, line));
    }

    // void Scanner::addToken(TokenType type, std::string lexeme) {
    //     std::string text = sourceCode.substr(start, current - start);
    //     tokens.push_back(Token(type, text, literal, line));
    // }

    bool Scanner::match(char expected) {
        if (isAtEnd()) {
            return false;
        }
        if (sourceCode[current] != expected) {
            return false;
        } else {
            current++;
            return true;
        }
    }

    char Scanner::peek() {
        if (isAtEnd()) {
            return '\0';
        }
        return sourceCode[current];
    }

    char Scanner::peekNext() {
        if (current + 1 >= sourceCode.length()) {
            return '\0';
        }
        return sourceCode[current + 1];
    }

    void Scanner::scanString() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') {
                line++;
            }
            advance();
        }
        if (isAtEnd()) {
            Lox::error(line, "Unterminated string.");
            return;
        }
        advance();
        addToken(TokenType::STRING);
    }

    void Scanner::scanNumber() {
        while (isdigit(peek())) {
            advance();
        }
        if (peek() == '.' && isdigit(peekNext())) {
            advance();
            while (isdigit(peek())) {
                advance();
            }
        }
        addToken(TokenType::NUMBER);
    }
    
    void Scanner::scanIdentifierOrKeyword() {
        while (isAplhaNumber(peek())) {
            advance();
        }
        std::string text = sourceCode.substr(start, current - start);
        auto it = keywords.find(text);
        TokenType type = TokenType::IDENTIFIER;
        if (it != keywords.end()) {
            addToken(it->second);
        } else {
            addToken(type);
        }
    }

    std::vector<Token> Scanner::scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }
       tokens.push_back(Token(TokenType::END_OF_FILE, "", line));
       return tokens;
    }
    void Scanner::scanToken() {
        char c = advance();
        switch (c) {
           case '(':
                addToken(TokenType::LEFT_PAREN);
                break;
            case ')':
                addToken(TokenType::RIGHT_PAREN);
                break;
            case '{':
                addToken(TokenType::LEFT_BRACE);
                break;
            case '}':
                addToken(TokenType::RIGHT_BRACE);
                break;
            case ',':
                addToken(TokenType::COMMA);
                break;
            case '.':
                addToken(TokenType::DOT);
                break;
            case '-':
                addToken(TokenType::MINUS);
                break;
            case '+':
                addToken(TokenType::PLUS);
                break;
            case ';':
                addToken(TokenType::SEMICOLON);
                break;
            case '*':
                addToken(TokenType::STAR);
                break;
            case '!':
                addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
                break;
            case '=':
                addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
                break;
            case '<':
                addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
                break;
            case '>':
                addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
                break;
            case '/':
                if (match('/')) {
                    while (peek() != '\n' && !isAtEnd()) {
                        advance();
                    }
                } else {
                    addToken(TokenType::SLASH);
                }
                break;
            // ignore whitespace
            case ' ':
            case '\r':
            case '\t':
                break;
            
            case '\n':
                line++;
                break;
            case '"':
                Scanner::scanString();
                break;
            default:
                if (isdigit(c)) {
                    scanNumber();
                } else if (isAplhaNumber(c)) {
                    scanIdentifierOrKeyword();
                } else {
                    Lox::error(line, "Unexpected character." + Lox::fileName + " " + c);
                }
                break;
        }
    }
}