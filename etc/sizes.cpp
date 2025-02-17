#include "stdio.h"
#include "stdint.h"

typedef struct ConsCell {
    uint16_t type;
    uint16_t flags;
    struct ConsCell* car;
    struct ConsCell* cdr;
} ConsCell;

int main()
{
    printf("sizeof(int) = %d\n", sizeof(int));
    printf("sizeof(long int) = %d\n", sizeof(long int));
    printf("sizeof(uint8_t) = %d\n", sizeof(uint8_t));
    printf("sizeof(uint16_t) = %d\n", sizeof(uint16_t));
    printf("sizeof(uint32_t) = %d\n", sizeof(uint32_t));
    printf("sizeof(uint64_t) = %d\n", sizeof(uint64_t));
    printf("\n");
    printf("sizeof(float) = %d\n", sizeof(float));
    printf("sizeof(double) = %d\n", sizeof(double));
    printf("sizeof(long double) = %d\n", sizeof(long double));
    printf("\n");
    printf("sizeof(char*) = %d\n", sizeof(char*));
    printf("\n");
    printf("sizeof(ConsCell) = %d\n", sizeof(ConsCell));
}
