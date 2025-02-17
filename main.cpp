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

    push(10);
    push(2);
    div();
    print();

    exit(0);
}

// Utility functions ---------------------

void fatal(const char* msg) {
    std::cout << msg << '\n';
    exit(1);
}
