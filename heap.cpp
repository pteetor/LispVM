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

static Cell* alloc()
{
    if (hp == heap_limit) {
        fatal("Heap exhausted");
        // TODO: Do garbage collection
    }
    return(hp++);
}

Cell* alloc(char char_val)
{
    Cell* p = alloc();
    p->type = CHAR_TYPE;
    p->char_val = char_val;
    return(p);
}

Cell* alloc(int32_t int_val)
{
    Cell* p = alloc();
    p->type = INT_TYPE;
    p->int_val = int_val;
    return(p);
}
