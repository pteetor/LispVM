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

// Local utility functions

static int stack_depth()
{
  return (stack_start - sp) + 1;
}

// Stack functions

void initStack()
{
    stack_start = &stack[STACK_SIZE];
    stack_limit = &stack[0];

    // Initialize sp to empty-stack condition
    sp = stack_start;
}

Cell* down(int n) {
  if (stack_depth() < n)
    fatal("Stack underflow (down)");
  return sp[n];
}

void collapse(int n)
{
  push(pop(n));
}

void drop(int n)
{
  if (stack_depth() < n)
    fatal("Stack underflow (drop)");
  sp += n;
}

void dup()
{
    push(top());
}

Cell* pop()
{
  if (sp == stack_start) {
    fatal("Stack underflow (pop)");
  }

  return *sp++;
}

Cell* pop(int n)
{
  if (stack_depth() < n)
    fatal("Stack underflow (pop n)");
  auto temp = *sp;
  sp += n;
  return temp;
}

Cell* pop_cons()
{
  auto p = pop();
  if (p->type != CONS_TYPE)
    fatal("Top of stack is not a cons cell");
  return p;
}

int32_t pop_int()
{
  auto p = pop();

  if (p->type != INT_TYPE) {
    fatal("Top of stack is not an integer");
  }

  return p->int_val;
}

void push(Cell* p)
{
    if (sp == stack_limit) {
        fatal("Stack overflow (push)");
    }

    --sp;
    *sp = p;
}

void push(int32_t i)
{
  push(new_cell(i));
}

void push(char ch)
{
  push(new_cell(ch));
}

void push(const char* str)
{
  push(new_cell(str));
}

Cell* top()
{
    if (sp == stack_start) {
        fatal("Empty stack (top)");
    }

    return *sp;
}
