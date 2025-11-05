// token.hpp
// a token is one piece of the input — like a word, number, or symbol

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
using namespace std;

class token {
public:
    // create a token with type, text, optional value, and line number
    token(const string& type, const string& lexeme, const string& literal, int line);

    // get a string version of this token (for printing/debugging)
    string to_string() const;

    // token type: like FORW, DECIMAL, etc.
    string type;

    // actual text from the source code
    string lexeme;

    // value for things like numbers or colors (optional)
    string literal;

    // line number where the token appeared
    int line;
};

#endif
