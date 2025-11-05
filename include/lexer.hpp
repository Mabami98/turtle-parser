#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
using namespace std;

class token;

class lexer {
public:
    lexer(const string& source_code);

    // returns a list of tokens for the given turtle source code
    vector<token> scan_tokens();

private:
    string source;        // original input
    vector<token> tokens; // tokens that get built

    int start = 0;        // where current token begins
    int current = 0;      // current character being checked
    int line = 1;         // line number (for errors)

    void scan_token();    // scans a single token

    bool is_at_end();     // have we reached the end?

    char advance();       // get current char and move ahead

    void add_token(const string& type);                  // simple token (like UP or DOT)
    void add_token(const string& type, const string& value); // token with literal (like number or color)

    char peek();          // look at current char without moving
    char peek_next();     // look ahead one more

    void skip_comment();  // handles % comments

    void match_keyword_or_error(); // checks for commands like FORW, BACK, etc.
    void number();                 // parses a decimal number
    void hex_color();             // parses #HEX values
};

#endif
