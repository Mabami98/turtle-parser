# Turtle Graphics Interpreter (In Progress)

A C++ implementation of a simple turtle graphics language interpreter (inspired by Logo), built using a recursive descent parser — **currently in progress**.

**Note:** This project is not fully functional yet, the interpreter **parses and prints** commands, but **does not yet generate output or graphical drawing**. 

---

## 💡 What It Does (So Far)

It reads a Turtle (Leona) language program with commands like:

FORW 100.

LEFT 90.

REP 4 "FORW 50. RIGHT 90."

COLOR #00FF00.

DOWN

and then **builds a syntax tree** representing the sequence of instructions.

Execution currently just prints each command, graphics or line segment generation is **not implemented yet**.

---
