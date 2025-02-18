//
//  LispVM header file
//

#include <cstdint>
#include <iostream>

// Forward declarations

struct Cell;
struct String;

// Cell types

const short int NULL_TYPE = 1 << 0;
const short int CONS_TYPE = 1 << 1;
const short int CHAR_TYPE = 1 << 2;
const short int INT_TYPE =  1 << 3;
const short int DOUBLE_TYPE =  1 << 4;
const short int STRING_TYPE =  1 << 5;

// Cell structure

struct Cell {
  uint16_t flags;
  uint16_t type;

  union {
    Cell* car;
    char char_val;
    int32_t int_val;
    double double_val;
    String* stringp;
  };
  Cell* cdr;
};

// Stack functions

void initStack();
void drop();
Cell* pop();
int32_t pop_int();
void push(Cell* p);
void push(int32_t i);
void push(char ch);
void push(const char* str);
Cell* top();

// Heap functions

void initHeap();
Cell* new_cell(char char_val);
Cell* new_cell(int32_t int_val);
Cell* new_cell(const char* str);

// String functions

void initStrings();
String* new_string(const char* str);

uint16_t string_length(String* p);
char* string_body(String* p);

// User-level operations
void add();
void div();
void mult();
void print();
void sub();

// Utility functions

void newline();
void fatal(const char* msg);
