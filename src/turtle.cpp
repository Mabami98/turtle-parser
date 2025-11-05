#include "Turtle.hpp"
#include "Lexer.hpp"
#include "Token.hpp"
#include "Parser.hpp"
#include "ParseTree.hpp"

#include <iostream>
using namespace std;

bool turtle::had_error = false;

// tokenize, parse, execute
void turtle::run(const string& source) {
    lexer scanner(source);
    vector<token> tokens = scanner.scan_tokens();

    // stop early if lexer found an error
    if (had_error) return;

    parser p(tokens);
    shared_ptr<node> tree;

    try {
        tree = p.parse();
    } catch (const runtime_error&) {
        // syntax error already reported
        return;
    }
    if (had_error) return;

    // run the program (prints actions for now)
    tree->run();
}

// called when something goes wrong during lexing/parsing
void turtle::error(int line, const string& message) {
    report(line, "", message);
}

// print error message with line number
void turtle::report(int line, const string& where, const string& message) {
    cerr << "[line " << line << "] error" << where << ": " << message << endl;
    had_error = true;
}
