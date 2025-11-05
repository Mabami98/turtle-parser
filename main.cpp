#include "lexer.hpp"
#include "parser.hpp"
#include "syntax_error.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " <source_file.turtle>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "could not open file: " << argv[1] << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string source_code = buffer.str();

    try {
        Lexer lexer(source_code);
        Parser parser(lexer);
        ParseTree program = parser.parse();
        program.execute();
    } catch (const SyntaxError& e) {
        cerr << "syntax error: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
