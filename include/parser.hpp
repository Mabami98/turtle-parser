#pragma once

#include "token.hpp"
#include "parse_tree.hpp"
#include "syntax_error.hpp"

#include <vector>
#include <memory>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);

    std::unique_ptr<ParseTree> parse();

private:
    const std::vector<Token>& tokens;
    size_t current;

    // entry point of grammar
    std::unique_ptr<ParseTree> parse_program();
    std::unique_ptr<ParseTree> parse_command();

    Token consume(TokenType type, const std::string& message);
    bool match(TokenType type);
    bool check(TokenType type);
    Token advance();
    bool is_at_end() const;
    Token peek() const;
    Token previous() const;
};
