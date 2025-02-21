//
// Permanent symbols
//

#include "LispVM.h"

Cell* nil_sym;
Cell* t_sym;

void init_perm_symbols()
{
  nil_sym = new_cell("nil");
  t_sym = new_cell("t");
}
