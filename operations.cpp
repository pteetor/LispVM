//
//  User-level operations on the LispVM
//

#include "LispVM.h"

void add()
{
    push(pop_int() + pop_int());
}

void div()
{
    auto y = pop_int();
    auto x = pop_int();
    push(x / y);
}

void mult()
{
    push(pop_int() * pop_int());
}

void sub()
{
    auto y = pop_int();
    auto x = pop_int();
    push(x - y);
}
