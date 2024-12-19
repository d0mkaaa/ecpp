#include "runtime.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace ec {
    void Runtime::setVar(const std::string& name, const std::string& value) {
        variables[name] = value;
    }

    std::string Runtime::getVar(const std::string& name) {
        return variables[name];
    }

    bool Runtime::hasVar(const std::string& name) {
        return variables.find(name) != variables.end();
    }

    int Runtime::getIntVar(const std::string& name) {
        try {
            return std::stoi(variables[name]);
        } catch(...) {
            return 0;
        }
    }

    void Runtime::registerFunction(const std::string& name, std::function<void()> func) {
        functions[name] = func;
    }

    bool Runtime::hasFunction(const std::string& name) {
        return functions.find(name) != functions.end();
    }

    void Runtime::callFunction(const std::string& name) {
        if (hasFunction(name)) {
            functions[name]();
        }
    }

    int Runtime::evaluateExpression(const std::string& expr) {
        std::string trimmed = expr;
        trimmed.erase(std::remove_if(trimmed.begin(), trimmed.end(),
            [](unsigned char c) { return std::isspace(c); }), 
            trimmed.end());

        size_t pos;
        std::string left, right;

        pos = trimmed.find('+');
        if (pos != std::string::npos) {
            left = trimmed.substr(0, pos);
            right = trimmed.substr(pos + 1);
            return evaluateTerm(left) + evaluateTerm(right);
        }

        pos = trimmed.find('-');
        if (pos != std::string::npos) {
            left = trimmed.substr(0, pos);
            right = trimmed.substr(pos + 1);
            return evaluateTerm(left) - evaluateTerm(right);
        }

        return evaluateTerm(trimmed);
    }

    int Runtime::evaluateTerm(const std::string& term) {
        if (hasVar(term)) {
            return getIntVar(term);
        }
        try {
            return std::stoi(term);
        } catch(...) {
            throw std::runtime_error("Invalid term: " + term);
        }
    }
}