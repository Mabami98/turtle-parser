// turtle.hpp
// this file contains the declaration of the turtle class
// it used to be called leona in java

#ifndef TURTLE_HPP
#define TURTLE_HPP

#include <string>
#include <vector>
using namespace std;

// forward declaration for token
class token;

// turtle is the main interpreter or runner class
class turtle {
public:
    // run some source code
    void run(const string& source);

    // keep track of error status
    static bool had_error;

private:
    // scan the input into tokens
    void scan_and_print_tokens(const string& source);

    // report an error at a specific line
    static void error(int line, const string& message);

    // helper to format the error message
    static void report(int line, const string& where, const string& message);
};

#endif
