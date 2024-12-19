#include "lexer.h"
#include <iostream>

namespace ec {
    std::vector<Token> Lexer::tokenize(const std::string& source) {
        std::vector<Token> tokens;
        current = source.begin();
        end = source.end();
        
        while (current != end) {
            skipWhitespace();
            if (current == end) break;
            
            if (*current == '/' && (current + 1) != end && *(current + 1) == '/') {
                while (current != end && *current != '\n') {
                    ++current;
                }
                continue;
            }
            
            if (isalpha(*current)) {
                auto token = identifier();
                tokens.push_back(token);
            }
            else if (isdigit(*current)) {
                auto token = number();
                tokens.push_back(token);
            }
            else if (*current == '"') {
                auto token = string();
                tokens.push_back(token);
            }
            else {
                std::string op(1, *current);
                tokens.push_back(Token{TokenType::OPERATOR, op, line, column});
                ++current;
            }
        }
        
        return tokens;
    }

    void Lexer::skipWhitespace() {
        while (current != end && (isspace(*current) || (*current == '\r'))) {
            if (*current == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            ++current;
        }
    }

    Token Lexer::identifier() {
        std::string value;
        while (current != end && (isalnum(*current) || *current == '_')) {
            value += *current;
            ++current;
        }
        return Token{TokenType::IDENTIFIER, value, line, column};
    }

    Token Lexer::number() {
        std::string value;
        while (current != end && isdigit(*current)) {
            value += *current;
            ++current;
        }
        return Token{TokenType::NUMBER, value, line, column};
    }

    Token Lexer::string() {
        std::string value;
        ++current;
        while (current != end && *current != '"') {
            value += *current;
            ++current;
        }
        if (current != end) ++current;
        return Token{TokenType::STRING, value, line, column};
    }
}