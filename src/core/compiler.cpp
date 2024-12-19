#include "compiler.h"
#include "runtime.h"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype> 

namespace ec {
    static Runtime runtime;
    static std::map<std::string, Statement> functionStore;

    void Compiler::compile(const std::unique_ptr<Program>& ast) {
        for (const auto& statement : ast->statements) {
            if (auto expr = dynamic_cast<const ExpressionNode*>(statement.get())) {
                if (expr->statement.type == "func") {
                    functionStore[expr->statement.identifier] = expr->statement;
                }
            }
        }

        auto mainFunc = functionStore.find("main");
        if (mainFunc != functionStore.end()) {
            for (const auto& stmt : mainFunc->second.block) {
                executeStatement(stmt);
            }
        } else {
            std::cout << "Error: No main function found" << std::endl;
        }
    }

    void Compiler::executeStatement(const Statement& stmt) {

        if (stmt.type == "func") {
            functionStore[stmt.identifier] = stmt;
        }
        else if (stmt.type == "call") {
            auto it = functionStore.find(stmt.identifier);
            if (it != functionStore.end()) {
                for (const auto& s : it->second.block) {
                    executeStatement(s);
                }
            } else {
                std::cout << "Error: Function not found: " << stmt.identifier << std::endl;
            }
        }
        else if (stmt.type == "print") {
            std::string output = stmt.value;
            std::string result;

            if (!output.empty() && output.front() == '"' && output.back() == '"') {
                result = output.substr(1, output.length() - 2);
            }
            else {
                try {
                    output.erase(std::remove_if(output.begin(), output.end(), 
                        [](unsigned char c) { return std::isspace(c); }), 
                        output.end());
                    int value = runtime.evaluateExpression(output);
                    result = std::to_string(value);
                } catch (const std::exception& e) {
                    std::cout << "Error evaluating expression: " << e.what() << std::endl;
                    if (runtime.hasVar(output)) {
                        result = runtime.getVar(output);
                    } else {
                        result = output;
                    }
                }
            }
            std::cout << result << std::endl;
        }
        else if (stmt.type == "var") {
            runtime.setVar(stmt.identifier, stmt.value);
        }
    }

    bool Compiler::evaluateCondition(const std::string& condition) {
        size_t pos = condition.find('<');
        if (pos != std::string::npos) {
            std::string left = condition.substr(0, pos);
            std::string right = condition.substr(pos + 1);
            
            left.erase(0, left.find_first_not_of(" "));
            left.erase(left.find_last_not_of(" ") + 1);
            right.erase(0, right.find_first_not_of(" "));
            right.erase(right.find_last_not_of(" ") + 1);

            int leftVal = runtime.hasVar(left) ? runtime.getIntVar(left) : std::stoi(left);
            int rightVal = runtime.hasVar(right) ? runtime.getIntVar(right) : std::stoi(right);
            
            return leftVal < rightVal;
        }
        return false;
    }
}