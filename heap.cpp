#include "LispVM.h"

const int HEAP_SIZE = 1000;

static Cell heap[HEAP_SIZE];
static Cell* heap_start;
static Cell* heap_limit;
static Cell* hp;

void initHeap()
{
    heap_start = &heap[0];
    heap_limit = &heap[HEAP_SIZE];
    hp = &heap[0];
}

static Cell* new_cell()
{
    if (hp == heap_limit) {
        fatal("Heap exhausted");
        // TODO: Do garbage collection
    }
    return(hp++);
}

Cell* new_cell(char char_val)
{
    Cell* p = new_cell();
    p->type = CHAR_TYPE;
    p->char_val = char_val;
    return(p);
}

Cell* new_cell(int32_t int_val)
{
    Cell* p = new_cell();
    p->type = INT_TYPE;
    p->int_val = int_val;
    return(p);
}

Cell* new_cell(const char* str)
{
  Cell* p = new_cell();
  p->type = STRING_TYPE;
  p->stringp = new_string(str);
  return p;
}

Cell* new_cell(Cell* car, Cell* cdr)
{
  Cell* p = new_cell();
  p->type = CONS_TYPE;
  p->car = car;
  p->cdr = cdr;
  return p;
}
