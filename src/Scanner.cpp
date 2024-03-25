#include <iostream>
#include <cctype>
#include "Scanner.hpp"
// #define DEBUG
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
    std::unordered_map<std::string, TokenType> Scanner::lookahead = {
        {"!", TokenType::BANG},
        {"!=", TokenType::BANG_EQUAL},
        {"=", TokenType::EQUAL},
        {"==", TokenType::EQUAL_EQUAL},
        {">", TokenType::GREATER},
        {">=", TokenType::GREATER_EQUAL},
        {"<", TokenType::LESS},
        {"<=", TokenType::LESS_EQUAL},
        {"+", TokenType::PLUS},
        {"-", TokenType::MINUS},
        {"*", TokenType::STAR},
        {"/", TokenType::SLASH},
        {"(", TokenType::LEFT_PAREN},
        {")", TokenType::RIGHT_PAREN},
        {"{", TokenType::LEFT_BRACE},
        {"}", TokenType::RIGHT_BRACE},
        {",", TokenType::COMMA},
        {".", TokenType::DOT},
        {";", TokenType::SEMICOLON},
        {":", TokenType::COLON}
    };

    bool Scanner::isAtEnd() {
        return currentPos >= static_cast<int>(sourceCode.length());
    }

    void Scanner::addToken(TokenType type, std::string lexeme, std::string literal="null") {
        tokens.push_back(Token(type, lexeme, literal, line));
    }

    char Scanner::advance() {
        ++currentPos;
        ++linePos;
        return sourceCode[currentPos];
    }
    
    void Scanner::goback() {
        if (currentPos != 0) {
            --currentPos;
        }
    }

    char Scanner::getCurrentChar() {
        return sourceCode[currentPos];
    }

    char Scanner::getNextChar() {
        return currentPos+1 > sourceCode.length() ? ' ' : sourceCode[currentPos+1];
    }

    bool Scanner::isLookahead(char ch) {
        std::string s(1, ch);
        return lookahead.find(s) != lookahead.end();
    }
    void Scanner::scanLookahead() {
        char ch = getCurrentChar();
        std::string s1(1, ch);
        std::string s2 = s1 + getNextChar();
        if (lookahead.find(s2) != lookahead.end()) {
            addToken(lookahead[s2], s2);
            advance();
        } else {
            addToken(lookahead[s1], s1);
        }
    }

    void Scanner::scanNums() {
        std::string num;
        bool hasDot = false;
        while (isdigit(getCurrentChar())) {
            num += getCurrentChar();
            advance();
        }
        if (getCurrentChar() == '.' && isdigit(getNextChar())) {
            num += getCurrentChar();
            advance();
            hasDot = true;
            while (isdigit(getCurrentChar())) {
                num += getCurrentChar();
                advance();
            }
        } else if (getCurrentChar() == '.' && !isdigit(getNextChar())) {
            addToken(TokenType::NUMBER, num, num+".0");
            goback();
            return;
        }
        if (getCurrentChar() != ' ' && getCurrentChar() != '\n' && getCurrentChar() != '\r' && getCurrentChar() != '\t') {
            error();
        }
        std::string numLiteral = num;
        if (numLiteral[numLiteral.length()-1] == '.') {
            numLiteral += "0";
        }
        if (!hasDot) {
            numLiteral += ".0";
        }
        addToken(TokenType::NUMBER, num, numLiteral);
    }
    void Scanner::scanIdentifiersOrKeywords() {
        std::string id;
        while (isalnum(getCurrentChar()) || getCurrentChar() == '_') {
            id += getCurrentChar();
            advance();
        }
        if (keywords.find(id) != keywords.end()){
            addToken(keywords[id], id);
        } else {
            addToken(TokenType::IDENTIFIER, id);
        }
        goback();
    }
    void Scanner::error() {
        hasError = true;
        std::cerr << "FileName:" << fileName << std::endl;
        std::cerr << "Error at line [" << line << "]" << " at position [" << linePos << "] : " << sourceCode[currentPos] << std::endl;
    }
    void Scanner::scanComment() {
        while (getCurrentChar() != '\n') {
            advance();
        }
        goback();
    }
    void Scanner::scanString() {
        std::string str;
        str += getCurrentChar();
        advance();
        while (getCurrentChar() != '"') {
            str += getCurrentChar();
            advance();
        }
        str += getCurrentChar();
        addToken(TokenType::STRING, str, str.substr(1, str.length()-2));
    }
    void Scanner::scanTokens() {
        while (!isAtEnd() && !hasError) {
            char ch = advance();
            // remove whitespace
            while (((ch == ' ') || (ch == '\n') || ch == '\r' || ch == '\t') && (!isAtEnd())) {
                if (ch == '\n') {
                    ++line;
                    linePos = 0;
                }
                ch = advance();
            }
            if (isAtEnd() || hasError) {
                break;
            }
            if (ch == '/' && getNextChar() == '/'){
                scanComment();
            } else if (isLookahead(ch)) {
                scanLookahead();
            } else if (isdigit(ch)) {
                scanNums();
            } else if (isalpha(ch) || ch == '_') {
                scanIdentifiersOrKeywords();
            } else if (ch == '"') {
                scanString();
            } else {
                error();
            }
        }
       addToken(TokenType::END_OF_FILE, "");
    }
    void Scanner::printAllTokens() {
        for (int i = 0; i < tokens.size(); ++i) {
            std::cout << tokens[i].getTypeStr() <<  " " << tokens[i].getLexeme() << " " << tokens[i].getLiteral();
            if (i != tokens.size()-1) {
                std::cout << std::endl;
            }
        }
    }
}