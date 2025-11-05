

#include "Token.hpp"
#include <sstream>

token::token(const string& type, const string& lexeme, const string& literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

// return a string representation like:
// FORW "FORW"  [line 1]
string token::to_string() const {
    ostringstream out;
    out << type << " \"" << lexeme << "\"";
    if (!literal.empty()) {
        out << " (" << literal << ")";
    }
    out << " [line " << line << "]";
    return out.str();
}
