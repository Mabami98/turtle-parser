#include "lexer.hpp"
#include <cctype>
#include <stdexcept>

TurtleLexer::TurtleLexer(const std::string& input)
    : input(input), pos(0) {}

Token TurtleLexer::next_token() {
    skip_whitespace();

    if (pos >= input.length()) {
        return Token(TokenType::END_OF_FILE, "");
    }

    char ch = input[pos];

    // Check for a number (could be a float)
    if (std::isdigit(ch)) {
        std::string number;
        while (pos < input.length() && (std::isdigit(input[pos]) || input[pos] == '.')) {
            number += input[pos++];
        }
        return Token(TokenType::NUMBER, number);
    }

    // Check for identifiers or keywords
    if (std::isalpha(ch)) {
        std::string word;
        while (pos < input.length() && std::isalpha(input[pos])) {
            word += input[pos++];
        }

        if (word == "forward") return Token(TokenType::FORWARD, word);
        if (word == "right") return Token(TokenType::RIGHT, word);
        if (word == "left") return Token(TokenType::LEFT, word);
        if (word == "repeat") return Token(TokenType::REPEAT, word);

        throw std::runtime_error("Unknown keyword: " + word);
    }

    // Check for special symbols
    if (ch == '[') {
        pos++;
        return Token(TokenType::LBRACKET, "[");
    } else if (ch == ']') {
        pos++;
        return Token(TokenType::RBRACKET, "]");
    }

    throw std::runtime_error(std::string("Unexpected character: ") + ch);
}

void TurtleLexer::skip_whitespace() {
    while (pos < input.length() && std::isspace(input[pos])) {
        pos++;
    }
}
