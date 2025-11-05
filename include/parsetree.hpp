#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include <string>
#include <vector>
#include <memory>
using namespace std;

// base class for all tree nodes
class node {
public:
    virtual ~node() = default;

    // run executes this node (to be defined later)
    virtual void run() = 0;
};

// a list of instructions (used for full programs and inside REP)
class sequence_node : public node {
public:
    vector<shared_ptr<node>> children;

    void run() override;
};

// FORW and BACK
class move_node : public node {
public:
    string direction; // "FORW" or "BACK"
    int amount;

    move_node(const string& dir, int amt);
    void run() override;
};

// LEFT and RIGHT
class turn_node : public node {
public:
    string direction; // "LEFT" or "RIGHT"
    int degrees;

    turn_node(const string& dir, int deg);
    void run() override;
};

// UP and DOWN
class pen_node : public node {
public:
    string state; // "UP" or "DOWN"

    pen_node(const string& s);
    void run() override;
};

// COLOR
class color_node : public node {
public:
    string hex;

    color_node(const string& hex_code);
    void run() override;
};

// REP
class rep_node : public node {
public:
    int times;
    shared_ptr<node> body; // usually a sequence_node

    rep_node(int t, shared_ptr<node> b);
    void run() override;
};

#endif
