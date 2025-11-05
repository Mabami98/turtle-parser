// main.cpp
// entry point for turtle interpreter

#include "Turtle.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    string input;

    if (argc > 1) {
        // if a file name is given, read from file
        ifstream file(argv[1]);
        if (!file) {
            cerr << "kunde inte öppna filen: " << argv[1] << endl;
            return 1;
        }

        stringstream buffer;
        buffer << file.rdbuf();
        input = buffer.str();
    } else {
        // read from standard input if no file was given
        cout << "mata in turtle-kod (CTRL+D för att avsluta):" << endl;
        stringstream buffer;
        buffer << cin.rdbuf();
        input = buffer.str();
    }

    turtle t;
    t.run(input);

    return turtle::had_error ? 1 : 0;
}
