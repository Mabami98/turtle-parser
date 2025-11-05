#pragma once

#include <string>
#include <vector>

enum class TokenType {
    FORWARD, TURN, LEFT, RIGHT, REPEAT,
    NUMBER, LBRACKET, RBRACKET,
    END
};

struct Token {
    TokenType type;
    std::string text;
    int value = 0; // used only for NUMBER tokens
};

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;

    void skip_whitespace();
    char peek() const;
    char advance();
    bool match(const std::string& word);
};
