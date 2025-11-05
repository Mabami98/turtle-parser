// lexer.hpp
#pragma once

#include <string>
#include <vector>

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    COMMAND,
    LBRACKET,
    RBRACKET,
    EOF_TOKEN,
    INVALID
};

struct Token {
    TokenType type;
    std::string value;
    int position;
};

class Lexer {
public:
    Lexer(const std::string& input);

    std::vector<Token> tokenize();

private:
    std::string input;
    int pos;
    int length;

    char peek() const;
    char get();
    bool is_at_end() const;

    void skip_whitespace();
    Token identifier();
    Token number();
};
