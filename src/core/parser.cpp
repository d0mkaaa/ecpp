#include "parser.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

namespace ec {
    std::unique_ptr<Program> Parser::parse(const std::vector<Token>& tokens) {
        auto program = std::make_unique<Program>();
        current = tokens.begin();
        end = tokens.end();
        
        while (current != end) {
            program->statements.push_back(
                std::make_unique<ExpressionNode>(parseStatement())
            );
        }
        return program;
    }

    Statement Parser::parseStatement() {
        if (current == end) return Statement{};
        
        auto token = *current;
        
        if (token.value == "func") return parseFunctionDeclaration();
        if (token.value == "var") return parseVarDeclaration();
        if (token.value == "if") return parseIfStatement();
        if (token.value == "print") return parsePrintStatement();
        
        if (isIdentifier(token.value)) {
            auto next = peek();
            if (next.value == "(") {

                if (token.value == "main") {
                    Statement stmt;
                    stmt.type = "func";
                    stmt.identifier = token.value;
                    advance(); 

                    if (match("(")) {
                        advance();
                        stmt.parameters = parseParameters();
                        if (match(")")) advance();
                    }
                    
                    stmt.block = parseBlock().block;
                    return stmt;
                }
                return parseFunctionCall();
            }
        }
        
        advance();
        return Statement{};
    }

    Statement Parser::parseFunctionDeclaration() {
        Statement stmt;
        stmt.type = "func";
        advance();

        if (current != end) {
            stmt.identifier = current->value;
            advance();

            if (match("(")) {
                advance();
                stmt.parameters = parseParameters();
                if (match(")")) advance();
            }

            stmt.block = parseBlock().block;
        }

        return stmt;
    }

    Statement Parser::parseFunctionCall() {
        Statement stmt;
        stmt.type = "call";
        stmt.identifier = current->value;
        advance();

        if (match("(")) {
            advance(); 
            stmt.arguments = parseArguments();
            if (match(")")) advance(); 
        }

        return stmt;
    }

    Statement Parser::parseVarDeclaration() {
        Statement stmt;
        stmt.type = "var";
        advance();

        if (current != end) {
            stmt.identifier = current->value;
            advance(); 

            if (match("=")) {
                advance(); 
                if (current != end) {
                    stmt.value = current->value;
                    advance();
                }
            }
        }

        return stmt;
    }

    Statement Parser::parseIfStatement() {
        Statement stmt;
        stmt.type = "if";
        advance();

        if (match("(")) {
            advance();
            std::string condition;
            while (current != end && !match(")")) {
                condition += current->value;
                advance();
            }
            stmt.value = condition;
            if (match(")")) advance();
            stmt.block = parseBlock().block;
        }

        return stmt;
    }

    Statement Parser::parsePrintStatement() {
        Statement stmt;
        stmt.type = "print";
        advance();

        if (match("(")) {
            advance(); 
            if (current != end) {
                if (current->type == TokenType::STRING) {
                    stmt.value = "\"" + current->value + "\""; 
                    advance();
                } else {
                    stmt.value = parseExpressionValue();
                }
                if (match(")")) advance();
            }
        }

        return stmt;
    }

    Statement Parser::parseBlock() {
        Statement block;
        if (match("{")) {
            advance();
            while (current != end && !match("}")) {
                auto stmt = parseStatement();
                if (!stmt.type.empty()) {
                    block.block.push_back(stmt);
                }
            }
            if (match("}")) advance();
        }
        return block;
    }

    std::string Parser::parseExpressionValue() {
        std::string expression;
        while (current != end && !match(")") && !match(";")) {
            if (!expression.empty() && !isspace(expression.back())) {
                expression += " ";
            }
            expression += current->value;
            advance();
        }
        return expression;
    }

    std::vector<std::string> Parser::parseParameters() {
        std::vector<std::string> params;
        while (current != end && !match(")")) {
            if (isIdentifier(current->value)) {
                params.push_back(current->value);
                advance();
                if (match(",")) advance();
            }
        }
        return params;
    }

    std::vector<std::string> Parser::parseArguments() {
        std::vector<std::string> args;
        while (current != end && !match(")")) {
            args.push_back(current->value);
            advance();
            if (match(",")) advance();
        }
        return args;
    }

    bool Parser::match(TokenType type) {
        return current != end && current->type == type;
    }

    bool Parser::match(const std::string& value) {
        return current != end && current->value == value;
    }

    void Parser::advance() {
        if (current != end) ++current;
    }

    Token Parser::peek() {
        auto next = current;
        if (next != end) ++next;
        return next != end ? *next : Token{TokenType::END_OF_FILE, "", 0, 0};
    }

    bool Parser::isIdentifier(const std::string& value) {
        return !value.empty() && isalpha(value[0]);
    }

    bool Parser::isKeyword(const std::string& value) {
        static const std::vector<std::string> keywords = {
            "func", "var", "if", "print", "return", "while", "for"
        };
        return std::find(keywords.begin(), keywords.end(), value) != keywords.end();
    }
}