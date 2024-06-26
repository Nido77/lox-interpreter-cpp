#include <sstream>
#include <iomanip>
#include <limits>
#include "Token.hpp"
#include "TokenType.hpp"
namespace nido {
    std::unordered_map<TokenType, std::string> Token::tokenTypeToStr = {
        {TokenType::LEFT_PAREN, "LEFT_PAREN"},
        {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
        {TokenType::LEFT_BRACE, "LEFT_BRACE"},
        {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
        {TokenType::COMMA, "COMMA"},
        {TokenType::DOT, "DOT"},
        {TokenType::MINUS, "MINUS"},
        {TokenType::PLUS, "PLUS"},
        {TokenType::SEMICOLON, "SEMICOLON"},
        {TokenType::SLASH, "SLASH"},
        {TokenType::STAR, "STAR"},
        {TokenType::COLON, "COLON"},
        {TokenType::BANG, "BANG"},
        {TokenType::BANG_EQUAL, "BANG_EQUAL"},
        {TokenType::EQUAL, "EQUAL"},
        {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
        {TokenType::GREATER, "GREATER"},
        {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
        {TokenType::LESS, "LESS"},
        {TokenType::LESS_EQUAL, "LESS_EQUAL"},
        {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::STRING, "STRING"},
        {TokenType::NUMBER, "NUMBER"},
        {TokenType::AND, "AND"},
        {TokenType::CLASS, "CLASS"},
        {TokenType::ELSE, "ELSE"},
        {TokenType::FALSE, "FALSE"},
        {TokenType::FUN, "FUN"},
        {TokenType::FOR, "FOR"},
        {TokenType::IF, "IF"},
        {TokenType::NIL, "NIL"},
        {TokenType::OR, "OR"},
        {TokenType::PRINT, "PRINT"},
        {TokenType::RETURN, "RETURN"},
        {TokenType::SUPER, "SUPER"},
        {TokenType::THIS, "THIS"},
        {TokenType::TRUE, "TRUE"},
        {TokenType::VAR, "VAR"},
        {TokenType::WHILE, "WHILE"},
        {TokenType::END_OF_FILE, "EOF"}
    };

    std::ostream& operator<<(std::ostream& os, Token& t) {
        if (t.getType() != TokenType::NUMBER && t.getType() != TokenType::STRING){
            os << t.getTypeStr() << " " << t.getLexeme() << " " << "null"; 
        } else {
            os << t.getTypeStr() << " " << t.getLexeme() << " " << t.getLiteral();
        }
        return os;
    }
    std::string Token::getLiteral() {
        if (type == TokenType::NUMBER) {
            double val = std::stod(lexeme);
            std::ostringstream oss;
            oss << std::setprecision(std::numeric_limits<double>::max_digits10) << val;
            std::string s = oss.str();
            return s;
        } else if (type == TokenType::STRING) {
            return lexeme.substr(1, lexeme.length() - 2);
        } else {
            return "null";
        }
    }
}
