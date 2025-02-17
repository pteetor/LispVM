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
        int32_t int_value;
        char char_value;
        Cell* car;
    };
    Cell* cdr;
};

// Cell types

const short int CONS_TYPE = 0x01;
const short int INT_TYPE =  0x02;
const short int CHAR_TYPE = 0x04;

// Stack functions
void initStack();

void add();
void drop();
void print();

int32_t pop_int();

void push(int32_t i);
void push(char ch);

Cell* top();

// Utility functions

void fatal(const char* msg);
