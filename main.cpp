//
//  LispVM main program
//

#include <cstdlib>

#include "LispVM.h"

int main(int argc, char** argv) {
    initStack();
    initHeap();

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
