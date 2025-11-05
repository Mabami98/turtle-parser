// lexer.hpp
// the lexer reads characters and turns them into tokens

#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
using namespace std;

class token; // forward declaration
enum class token_type; // forward declaration

class lexer {
public:
    lexer(const string& source_code);

    // turn the input source into a list of tokens
    vector<token> scan_tokens();

private:
    string source;        // the input text
    vector<token> tokens; // list of tokens found

    int start = 0;   // start of current lexeme
    int current = 0; // current character index
    int line = 1;    // line number in the file

    // scan one token and add it to the list
    void scan_token();

    // check if we've reached the end of input
    bool is_at_end();

    // read the next character and move forward
    char advance();

    // add a token of a given type with no literal
    void add_token(token_type type);

    // add a token with literal string value
    void add_token(token_type type, const string& literal);

    // helper to match a specific next character
    bool match(char expected);

    // look ahead without consuming the character
    char peek();

    // look ahead two characters
    char peek_next();

    // string literal parser
    void string_literal();

    // number parser
    void number();

    // identifier or keyword
    void identifier();

    // check if a char is a digit
    bool is_digit(char c);

    // check if a char is a letter or underscore
    bool is_alpha(char c);

    // check if a char is alphanumeric
    bool is_alphanumeric(char c);
};

#endif
