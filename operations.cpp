//
//  User-level operations on the LispVM
//

#include <iomanip>

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

void print()
{
  auto p = pop();

  switch (p->type)
  {
  case NULL_TYPE:
    std::cout << "nil";
    break;
  case CONS_TYPE:
    fatal("Cannot print() cons cell");
    break;
  case CHAR_TYPE:
    std::cout << p->char_val;
    break;
  case INT_TYPE:
    std::cout << p->int_val;
    break;
  case STRING_TYPE:
  {
    auto s = p->stringp;
    std::cout << std::setw(string_length(s)) << string_body(s);
    // WAS: printf("%*s", string_length(p->stringp), string_body(p->stringp));
    break;
  }
  default:
    fatal("Unknown cell type");
  break;
  }
}

void sub()
{
  auto y = pop_int();
  auto x = pop_int();
  push(x - y);
}
