//
//  LispVM header file
//

#include <cstdint>
#include <iostream>

// Cell structure

struct Cell {
    uint16_t type;
    uint16_t flags;
    union {
        char char_val;
        int32_t int_val;
        Cell* car;
    };
    Cell* cdr;
};

// Cell types

const short int NULL_TYPE = 0x01;
const short int CONS_TYPE = 0x02;
const short int CHAR_TYPE = 0x04;
const short int INT_TYPE =  0x08;

// Stack functions
void initStack();
void drop();
void print();
int32_t pop_int();
void push(Cell* p);
void push(int32_t i);
void push(char ch);

Cell* top();

// Cell heap functions

void initHeap();
Cell* alloc(char char_val);
Cell* alloc(int32_t int_val);

// User-level operations
void add();
void div();
void mult();
void sub();

// Utility functions

void fatal(const char* msg);
