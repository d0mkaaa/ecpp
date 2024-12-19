#pragma once
#include <map>
#include <string>
#include <functional>

namespace ec {
    class Runtime {
    private:
        std::map<std::string, std::string> variables;
        std::map<std::string, std::function<void()>> functions;
        int evaluateTerm(const std::string& term);

    public:
        void setVar(const std::string& name, const std::string& value);
        std::string getVar(const std::string& name);
        bool hasVar(const std::string& name);
        int getIntVar(const std::string& name);
        int evaluateExpression(const std::string& expr);
        void registerFunction(const std::string& name, std::function<void()> func);
        bool hasFunction(const std::string& name);
        void callFunction(const std::string& name);
    };
}