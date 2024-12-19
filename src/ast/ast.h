#pragma once
#include <memory>
#include <string>
#include <vector>
#include "statement.h"

namespace ec {
    class ASTNode {
    public:
        virtual ~ASTNode() = default;
    };

    class ExpressionNode : public ASTNode {
    public:
        Statement statement;
        ExpressionNode(const Statement& stmt) : statement(stmt) {}
    };

    class Program {
    public:
        std::vector<std::unique_ptr<ASTNode>> statements;
    };
}