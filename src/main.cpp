#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "lexer.h"
#include "parser.h"
#include "compiler.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ecpp <filename.ec>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    ec::Lexer lexer;
    ec::Parser parser;
    ec::Compiler compiler;

    try {
        auto tokens = lexer.tokenize(source);
        auto ast = parser.parse(tokens);
        compiler.compile(ast);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}