//
// Stack implementation for LispVM
//

#include "LispVM.h"

// Stack types

// Stack data structures

const int STACK_SIZE = 1000;

// This stack grows from high addresses to low.
// That is, from stack[STACK_SIZE] to stack[0].
// That way, indexing into stack frames can use positive indexes,
// which is much less confusing that negative indexes.
static Cell* stack[STACK_SIZE];
static Cell** sp;

static Cell** stack_start;
static Cell** stack_limit;

// Stack functions

void initStack()
{
    stack_start = &stack[STACK_SIZE];
    stack_limit = &stack[0];

    // Initialize sp to indicate empty-stack condition
    sp = stack_start;
}

void drop()
{
    if (sp == stack_start) {
        fatal("Stack underflow");
    }
    ++sp;
}

void dup()
{
    push(top());
}

int32_t pop_int()
{
    if (sp == stack_start) {
        fatal("Stack underflow");
    }
    if ((*sp)->type != INT_TYPE) {
        fatal("Top of stack is not an integer");
    }
    return((*sp++)->int_val);
}

void print()
{
    if (sp == stack_start) {
        fatal("Stack underflow");
    }

    switch (top()->type)
    {
        case NULL_TYPE:
            std::cout << "nil";
            break;
        case CONS_TYPE:
            fatal("Cannot print() cons cell");
            break;
        case CHAR_TYPE:
            std::cout << top()->char_val;
            break;
        case INT_TYPE:
            std::cout << top()->int_val;
            break;
        default:
            fatal("Unknown cell type");
            break;
    }
    ++sp;
}

void push(Cell* p)
{
    if (sp == stack_limit) {
        fatal("Stack overflow");
    }

    --sp;
    *sp = p;
}

void push(int32_t i)
{
    if (sp == stack_limit) {
        fatal("Stack overflow");
    }

    --sp;
    *sp = new_cell(i);
}

void push(char ch)
{
    if (sp == stack_limit) {
        fatal("Stack overflow");
    }

    --sp;
    *sp = new_cell(ch);
}

Cell* top()
{
    if (sp == stack_start) {
        fatal("Empty stack");
    }

    return(*sp);
}
