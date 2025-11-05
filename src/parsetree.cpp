#include "ParseTree.hpp"
#include <iostream>
using namespace std;

// run all child nodes in sequence
void sequence_node::run() {
    for (auto& child : children) {
        child->run();
    }
}

// move forward or back
move_node::move_node(const string& dir, int amt)
    : direction(dir), amount(amt) {}

void move_node::run() {
    cout << direction << " " << amount << endl;
}

// turn left or right
turn_node::turn_node(const string& dir, int deg)
    : direction(dir), degrees(deg) {}

void turn_node::run() {
    cout << direction << " " << degrees << endl;
}

// lift or drop pen
pen_node::pen_node(const string& s) : state(s) {}

void pen_node::run() {
    cout << "PEN " << state << endl;
}

// set pen color
color_node::color_node(const string& hex_code) : hex(hex_code) {}

void color_node::run() {
    cout << "COLOR " << hex << endl;
}

// repeat a block of instructions
rep_node::rep_node(int t, shared_ptr<node> b)
    : times(t), body(b) {}

void rep_node::run() {
    for (int i = 0; i < times; ++i) {
        body->run();
    }
}
