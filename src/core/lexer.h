#pragma once
#include <string>
#include <vector>

namespace ec {
    enum class TokenType {
        IDENTIFIER,
        NUMBER,
        STRING,
        KEYWORD,
        OPERATOR,
        PUNCTUATION,
        END_OF_FILE
    };

    struct Token {
        TokenType type;
        std::string value;
        int line;
        int column;
    };

    class Lexer {
    public:
        std::vector<Token> tokenize(const std::string& source);
    private:
        int line = 1;
        int column = 1;
        std::string::const_iterator current;
        std::string::const_iterator end;
        
        Token nextToken();
        Token identifier();
        Token number();
        Token string();
        void skipWhitespace();
    };
}