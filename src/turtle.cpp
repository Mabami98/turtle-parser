// turtle.cpp
// this file has the implementation of the turtle class
// turtle is the main class that runs the turtle language

#include "Turtle.hpp"
#include "Lexer.hpp"
#include "Token.hpp"
// #include "Parser.hpp" // <- you'll include this once parsing is ready
// #include "ParseTree.hpp" // <- and this when building/using the syntax tree

#include <iostream>
using namespace std;

// static variable to track if any error occurred
bool turtle::had_error = false;

// run is the main entry point — it will eventually do everything
void turtle::run(const string& source) {
    scan_and_print_tokens(source); // for now, just lex and show tokens

    // TODO: phase 2 – parse tokens into syntax tree
    // parser p(tokens);
    // auto tree = p.parse();

    // TODO: phase 3 – interpret and execute the program
    // tree->execute();
}

// turn source into tokens and print them
void turtle::scan_and_print_tokens(const string& source) {
    lexer scanner(source);
    vector<token> tokens = scanner.scan_tokens();

    for (const token& t : tokens) {
        cout << t.to_string() << endl;
    }
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
