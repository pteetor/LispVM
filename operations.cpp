//
//  User-level operations on the LispVM
//

#include <iomanip>

#include "LispVM.h"

void add()
{
  push(pop_int() + pop_int());
}

void atomp()
{
  auto type = pop()->type;
  auto atom_types = CHAR_TYPE | INT_TYPE | DOUBLE_TYPE | INT_TYPE | STRING_TYPE;

  if ((type & atom_types) != 0) {
    push(t_sym);
  } else {
    push(nil_sym);
  }
}

void car()
{
  push(pop_cons()->car);
}

void cdr()
{
  push(pop_cons()->cdr);
}

void cons()
{
  auto cdr = down(0);
  auto car = down(1);
  push(new_cell(car, cdr));
  collapse(3);
}

void consp()
{
  auto type = pop()->type;
  ((type & CONS_TYPE) != 0) ? push(t_sym) : push(nil_sym);
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

void nullp()
{
  auto type = pop()->type;
  if (type == NULL_TYPE) {
    push(t_sym);
  } else {
    push(nil_sym);
  }
}

void print_atom()
{
  auto p = pop();

  switch (p->type)
  {
  case NULL_TYPE:
    std::cout << "nil";
    break;
  case CONS_TYPE:
    fatal("Cannot print_atom() cons cell");
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
