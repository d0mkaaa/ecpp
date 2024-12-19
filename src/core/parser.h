#pragma once
#include <memory>
#include <vector>
#include "lexer.h"
#include "ast.h"
#include "statement.h"
#include "runtime.h"

namespace ec {
    class Parser {
    public:
        std::unique_ptr<Program> parse(const std::vector<Token>& tokens);

    private:
        std::vector<Token>::const_iterator current;
        std::vector<Token>::const_iterator end;
        Runtime runtime;
        
        Statement parseStatement();
        Statement parseExpression();
        Statement parseBlock();
        bool match(TokenType type);
        bool match(const std::string& value);
        void advance();
        Token peek();
        bool isIdentifier(const std::string& value);
        bool isKeyword(const std::string& value);
        Statement parseFunctionDeclaration();
        Statement parseFunctionCall();
        Statement parseVarDeclaration();
        Statement parseIfStatement();
        Statement parsePrintStatement();
        std::vector<std::string> parseParameters();
        std::vector<std::string> parseArguments();
        std::string parseExpressionValue();
    };
}