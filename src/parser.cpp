// parser.cpp
// builds a tree of turtle instructions using recursive descent

#include "Parser.hpp"
#include "ParseTree.hpp"
#include "Turtle.hpp"

#include <iostream>
#include <stdexcept>

parser::parser(const vector<token>& tokens) : tokens(tokens) {}

// entry point: parse the whole program
shared_ptr<node> parser::parse() {
    return parse_program();
}

// parses a list of commands (whole program or inside a REP)
shared_ptr<node> parser::parse_program() {
    auto sequence = make_shared<sequence_node>();

    while (!is_at_end()) {
        // stop if we see closing quote (for REP bodies)
        if (check("QUOTE")) break;

        auto cmd = parse_command();
        if (cmd) sequence->children.push_back(cmd);
    }

    return sequence;
}

// parses a single command: FORW 100. or REP 4 " ... "
shared_ptr<node> parser::parse_command() {
    if (match("FORW")) {
        auto amount = advance();
        consume("DECIMAL", "förväntade heltal efter FORW");
        consume("PERIOD", "saknar punkt efter FORW-kommandot");
        return make_shared<move_node>("FORW", stoi(amount.literal));
    }

    if (match("BACK")) {
        auto amount = advance();
        consume("DECIMAL", "förväntade heltal efter BACK");
        consume("PERIOD", "saknar punkt efter BACK-kommandot");
        return make_shared<move_node>("BACK", stoi(amount.literal));
    }

    if (match("LEFT")) {
        auto amount = advance();
        consume("DECIMAL", "förväntade heltal efter LEFT");
        consume("PERIOD", "saknar punkt efter LEFT-kommandot");
        return make_shared<turn_node>("LEFT", stoi(amount.literal));
    }

    if (match("RIGHT")) {
        auto amount = advance();
        consume("DECIMAL", "förväntade heltal efter RIGHT");
        consume("PERIOD", "saknar punkt efter RIGHT-kommandot");
        return make_shared<turn_node>("RIGHT", stoi(amount.literal));
    }

    if (match("UP")) {
        consume("PERIOD", "saknar punkt efter UP-kommandot");
        return make_shared<pen_node>("UP");
    }

    if (match("DOWN")) {
        consume("PERIOD", "saknar punkt efter DOWN-kommandot");
        return make_shared<pen_node>("DOWN");
    }

    if (match("COLOR")) {
        auto color = advance();
        consume("HEX", "förväntade färgkod (#RRGGBB) efter COLOR");
        consume("PERIOD", "saknar punkt efter COLOR-kommandot");
        return make_shared<color_node>(color.lexeme);
    }

    if (match("REP")) {
        auto times = advance();
        consume("DECIMAL", "förväntade heltal efter REP");
        consume("QUOTE", "förväntade \" efter REP-räknare");

        auto body = parse_program();

        consume("QUOTE", "förväntade avslutande \" efter REP-kropp");

        return make_shared<rep_node>(stoi(times.literal), body);
    }

    // if we get here, we hit an unknown or misplaced token
    error(peek(), "okänt kommando");
    advance(); // skip to avoid infinite loop
    return nullptr;
}

// helper: check and consume a required token
void parser::consume(const string& type, const string& message) {
    if (check(type)) {
        advance();
    } else {
        error(peek(), message);
        throw runtime_error("syntax error");
    }
}

// returns true if current token matches and moves forward
bool parser::match(const string& type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

// check if current token has a given type
bool parser::check(const string& type) {
    if (is_at_end()) return false;
    return peek().type == type;
}

// move to the next token
token parser::advance() {
    if (!is_at_end()) current++;
    return previous();
}

// check if we've consumed all tokens
bool parser::is_at_end() {
    return peek().type == "EOF";
}

// look at current token
token parser::peek() {
    return tokens[current];
}

// look at last consumed token
token parser::previous() {
    return tokens[current - 1];
}

// report a parser error
void parser::error(const token& tok, const string& message) {
    turtle::error(tok.line, message);
}
