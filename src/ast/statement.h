#pragma once
#include <string>
#include <vector>

namespace ec {
    struct Statement {
        std::string type;
        std::string identifier;
        std::string value;
        std::vector<Statement> block;
        std::vector<std::string> parameters;
        std::vector<std::string> arguments;
    };
}