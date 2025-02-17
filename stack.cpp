//
// Stack implementation for LispVM
//

#include "LispVM.h"

// Stack types

// Stack data structures

const int STACK_SIZE = 1000;

static Cell stack[STACK_SIZE];
static Cell* sp;

static Cell* stack_bottom;

// Stack functions

void initStack()
{
    stack_bottom = &stack[STACK_SIZE];
    sp = &stack[STACK_SIZE];
}

void add()
{
    push(pop_int() + pop_int());
}

void drop()
{
    if (sp == stack_bottom) {
        fatal("Stack underflow");
    }
    ++sp;
}

int32_t pop_int()
{
    if (sp == stack_bottom) {
        fatal("Stack underflow");
    }
    if (sp->type != INT_TYPE) {
        fatal("Top of stack is not an integer");
    }
    return((sp++)->int_value);
}

void print()
{
    if (sp == stack_bottom) {
        fatal("Stack underflow");
    }

    switch (sp->type)
    {
        case INT_TYPE:
            std::cout << sp->int_value << '\n';
            break;
        default:
            fatal("Unknown cell type");
            break;
    }
    ++sp;
}

void push(int32_t i)
{
    (--sp)->type = INT_TYPE;
    sp->int_value = i;
}

void push(char ch)
{
    (--sp)->type = CHAR_TYPE;
    sp->char_value = ch;
}

Cell* top()
{
    return(sp);
}
