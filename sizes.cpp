//
// Print sizes of several LispVM data structures
//

#include <stddef.h>
#include "stdio.h"
#include "stdint.h"

#include "LispVM.h"

int main()
{
  printf("sizeof(Cell) = %d\n", sizeof(Cell));
  printf("sizeof(String) = %d\n", sizeof(String));
}
