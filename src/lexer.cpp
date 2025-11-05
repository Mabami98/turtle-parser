// turns the turtle code into a list of tokens

#include "Lexer.hpp"
#include "Token.hpp"
#include "Turtle.hpp"

#include <iostream>
#include <cctype>   // for isdigit, isalpha, etc.
#include <algorithm> // for transform
using namespace std;

// constructor: store the input source code
lexer::lexer(const string& source_code) : source(source_code) {}

// main function: tokenize the source input
vector<token> lexer::scan_tokens() {
    while (!is_at_end()) {
        start = current;
        scan_token();
    }

    tokens.push_back(token("EOF", "", line)); // end of file
    return tokens;
}

// process one token from input
void lexer::scan_token() {
    char c = advance();

    switch (c) {
        case '.':
            add_token("PERIOD");
            break;
        case '"':
            add_token("QUOTE");
            break;
        case '%':
            skip_comment(); // skip rest of line
            break;
        case '#':
            hex_color();
            break;
        case ' ':
        case '\r':
        case '\t':
            // skip whitespace
            break;
        case '\n':
            line++;
            break;
        default:
            if (isdigit(c)) {
                number();
            } else if (isalpha(c)) {
                match_keyword_or_error();
            } else {
                turtle::error(line, "ogiltigt tecken"); // invalid character
                tokens.push_back(token("ERROR", string(1, c), line));
            }
            break;
    }
}

// check if we ar at the end of input
bool lexer::is_at_end() {
    return current >= source.length();
}

// consume one character and move forward
char lexer::advance() {
    return source[current++];
}

// look at current character without consuming
char lexer::peek() {
    if (is_at_end()) return '\0';
    return source[current];
}

// look at the next character
char lexer::peek_next() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

// skip over comment until end of line
void lexer::skip_comment() {
    while (peek() != '\n' && !is_at_end()) advance();
}

// check if a word is a known command like FORW or REP
void lexer::match_keyword_or_error() {
    while (isalpha(peek())) advance();

    string text = source.substr(start, current - start);

    // make it uppercase to ignore case
    string upper_text = text;
    transform(upper_text.begin(), upper_text.end(), upper_text.begin(), ::toupper);

    // list of valid command words
    if (upper_text == "FORW" || upper_text == "BACK" ||
        upper_text == "LEFT" || upper_text == "RIGHT" ||
        upper_text == "DOWN" || upper_text == "UP" ||
        upper_text == "COLOR" || upper_text == "REP") {
        
        add_token(upper_text);
    } else {
        turtle::error(line, "okänt kommando: " + text);
        tokens.push_back(token("ERROR", text, line));
    }
}

// handles positive integer values
void lexer::number() {
    while (isdigit(peek())) advance();

    string value = source.substr(start, current - start);
    add_token("DECIMAL", value);
}

// handles hex colors like #FFA500
void lexer::hex_color() {
    while (isxdigit(peek())) advance();

    string value = source.substr(start, current - start);

    // simple validation: must have at least 1 digit after #
    if (value.length() < 2) {
        turtle::error(line, "ogiltig färgkod");
        tokens.push_back(token("ERROR", value, line));
    } else {
        add_token("HEX", value);
    }
}

// add a basic token without literal
void lexer::add_token(const string& type) {
    add_token(type, "");
}

// add a token with a value (for DECIMAL, HEX)
void lexer::add_token(const string& type, const string& value) {
    string text = source.substr(start, current - start);
    tokens.push_back(token(type, text, value, line));
}
