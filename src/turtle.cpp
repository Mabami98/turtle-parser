// turtle.cpp
// this file has the implementation of the turtle class
// turtle is the main class that runs the source code

#include "Turtle.hpp"
#include "Lexer.hpp"
#include "Token.hpp"

#include <iostream>
using namespace std;

// set initial error status
bool turtle::had_error = false;

// run takes source code and processes it
void turtle::run(const string& source) {
    scan_and_print_tokens(source);
}

// this function turns the source into tokens and prints them
void turtle::scan_and_print_tokens(const string& source) {
    // create a lexer (aka scanner) with the input
    lexer scanner(source);

    // get the list of tokens
    vector<token> tokens = scanner.scan_tokens();

    // print each token line by line
    for (const token& t : tokens) {
        cout << t.to_string() << endl;
    }
}

// error function used to report something wrong on a line
void turtle::error(int line, const string& message) {
    report(line, "", message);
}

// report builds the full error message with location info
void turtle::report(int line, const string& where, const string& message) {
    cerr << "[line " << line << "] error" << where << ": " << message << endl;
    had_error = true;
}
