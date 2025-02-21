//
//  LispVM main program
//

#include <cstdlib>

#include "LispVM.h"

int main(int argc, char** argv) {
    initStack();
    initHeap();
    initStrings();

    push(1);
    push(1);
    add();
    print();
    newline();

    push(10);
    push(2);
    div();
    print();
    newline();

    push('h');
    print();
    newline();

    push("hello, world");
    print();
    newline();

    auto hello1 = new_string("hello");
    auto hello2 = new_string("hello");

    newline();
    push("---- String heap dump: ----");
    print();
    newline();
    visit_string_heap(dump_string);
    newline();

    exit(0);
}

// Utility functions ---------------------

void newline()
{
    push('\n');
    print();
}

void fatal(const char* msg) {
    std::cout << msg << '\n';
    exit(1);
}
