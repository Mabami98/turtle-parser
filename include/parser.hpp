#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <memory>
#include "Token.hpp"
using namespace std;

// forward declare syntax tree nodes
class node;

class parser {
public:
    parser(const vector<token>& tokens);

    // parse the full input and return a tree (or list of instructions)
    shared_ptr<node> parse();

private:
    const vector<token>& tokens;
    int current = 0;

    // top level entry: list of commands
    shared_ptr<node> parse_program();

    // parse a single command (FORW, BACK, etc.)
    shared_ptr<node> parse_command();

    // parse a REP structure
    shared_ptr<node> parse_rep();

    // helpers
    bool match(const string& type);
    bool check(const string& type);
    token advance();
    bool is_at_end();
    token peek();
    token previous();

    void consume(const string& type, const string& message);
    void error(const token& tok, const string& message);
};

#endif
