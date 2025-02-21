//
//  LispVM main program
//

#include <cstdlib>

#include "LispVM.h"

int main(int argc, char** argv) {
    initStack();
    initHeap();
    initStrings();
    init_perm_symbols();

    push(1);
    push(1);
    add();
    print_atom();
    newline();

    push(10);
    push(2);
    div();
    print_atom();
    newline();

    push('h');
    print_atom();
    newline();

    push("hello, world");
    print_atom();
    newline();

    auto hello1 = new_string("hello");
    auto hello2 = new_string("hello");

    newline();
    push("---- String heap dump: ----");
    print_atom();
    newline();
    visit_string_heap(dump_string);
    newline();

    push("Is string an atom?\n");
    print_atom();
    push("moe");
    atomp();
    print_atom();
    newline();

    push("Is string a cons?\n");
    print_atom();
    push("moe");
    consp();
    print_atom();
    newline();

    push("Is cons() an atom?\n");
    print_atom();
    push("moe");
    push("larry");
    cons();
    atomp();
    print_atom();
    newline();

    push("Is cons() a cons?\n");
    print_atom();
    push("moe");
    push("larry");
    cons();
    consp();
    print_atom();
    newline();

    push("What is (car (cons moe larry))?\n");
    print_atom();
    push("moe");
    push("larry");
    cons();
    car();
    print_atom();
    newline();

    push("What is (cdr (cons moe larry))?\n");
    print_atom();
    push("moe");
    push("larry");
    cons();
    cdr();
    print_atom();
    newline();

    // push("moe");
    // push("larry");
    // cons();
    // print_atom();

    exit(0);
}

// Utility functions ---------------------

void newline()
{
    push('\n');
    print_atom();
}

void fatal(const char* msg) {
    std::cout << msg << '\n';
    exit(1);
}
