#include "lexer.hpp"
#include <cctype>
#include <sstream>

using namespace std;

Lexer::Lexer(const string& input) : src(input), pos(0) {}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;

    while (pos < src.length()) {
        char current = src[pos];

        if (isspace(current)) {
            pos++; // skip whitespace
            continue;
        }

        if (isalpha(current)) {
            string ident = read_identifier();
            tokens.push_back(Token("IDENT", ident));
            continue;
        }

        if (isdigit(current)) {
            string number = read_number();
            tokens.push_back(Token("NUMBER", number));
            continue;
        }

        switch (current) {
            case '+': tokens.push_back(Token("PLUS", "+")); break;
            case '-': tokens.push_back(Token("MINUS", "-")); break;
            case '*': tokens.push_back(Token("MUL", "*")); break;
            case '/': tokens.push_back(Token("DIV", "/")); break;
            case '(': tokens.push_back(Token("LPAREN", "(")); break;
            case ')': tokens.push_back(Token("RPAREN", ")")); break;
            case ';': tokens.push_back(Token("SEMICOLON", ";")); break;
            default:
                throw SyntaxError("Unknown character: " + string(1, current));
        }
        pos++;
    }

    tokens.push_back(Token("EOF", "")); // end of input marker
    return tokens;
}

string Lexer::read_identifier() {
    int start = pos;
    while (pos < src.length() && isalnum(src[pos])) {
        pos++;
    }
    return src.substr(start, pos - start);
}

string Lexer::read_number() {
    int start = pos;
    while (pos < src.length() && isdigit(src[pos])) {
        pos++;
    }
    return src.substr(start, pos - start);
}
