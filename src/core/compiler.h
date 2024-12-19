#pragma once
#include <memory>
#include <string>
#include "parser.h"
#include "ast.h"
#include "statement.h"

namespace ec {
    class Compiler {
    public:
        void compile(const std::unique_ptr<Program>& ast);
    private:
        void compileNode(const ASTNode* node);
        void generateInstruction(const std::string& instruction);
        void executeStatement(const Statement& stmt);
        bool evaluateCondition(const std::string& condition);
    };
}