#include "parser.hpp"
#include "syntax_error.hpp"

#include <iostream>

using namespace std;

// constructor takes the lexer and pulls the first token
Parser::Parser(Lexer& lexer) : lexer(lexer) {
    advance();
}

// advance to the next token
void Parser::advance() {
    current = lexer.next_token();
}

// check if the current token matches expected type
bool Parser::match(TokenType expected) {
    if (current.type == expected) {
        advance();
        return true;
    }
    return false;
}

// if token doesn't match, throw a syntax error
void Parser::expect(TokenType expected, const string& message) {
    if (!match(expected)) {
        throw SyntaxError(message);
    }
}

ParseTree Parser::parse() {
    // entry point, currently just parses a full program
    return program();
}

ParseTree Parser::program() {
    ParseTree tree("Program");
    while (current.type != TokenType::EOF_TOKEN) {
        tree.children.push_back(statement());
    }
    return tree;
}

ParseTree Parser::statement() {
    // there could be multiple kinds of statements
    if (current.type == TokenType::FORWARD ||
        current.type == TokenType::LEFT ||
        current.type == TokenType::RIGHT) {
        return command();
    } else if (current.type == TokenType::REPEAT) {
        return repeat();
    } else {
        throw SyntaxError("Expected a command or repeat statement");
    }
}

ParseTree Parser::command() {
    ParseTree tree("Command: " + current.lexeme);
    TokenType cmd_type = current.type;
    advance();

    if (current.type != TokenType::NUMBER) {
        throw SyntaxError("Expected number after command");
    }
    tree.children.emplace_back("Value: " + current.lexeme);
    advance();

    return tree;
}

ParseTree Parser::repeat() {
    ParseTree tree("Repeat");
    advance();

    if (current.type != TokenType::NUMBER) {
        throw SyntaxError("Expected number after repeat");
    }
    tree.children.emplace_back("Times: " + current.lexeme);
    advance();

    expect(TokenType::LBRACKET, "Expected '[' after repeat count");

    while (current.type != TokenType::RBRACKET && current.type != TokenType::EOF_TOKEN) {
        tree.children.push_back(statement());
    }

    expect(TokenType::RBRACKET, "Expected ']' to close repeat block");
    return tree;
}
