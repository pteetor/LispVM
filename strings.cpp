//
//  String heap for LispVM
//

#include <cstring>
#include "LispVM.h"

struct String {
    uint16_t flags;
    uint16_t length;
};

const int STRINGS_SIZE = 1000;

String strings[STRINGS_SIZE];

String* strings_start;
String* strings_limit;
String* strp;

// Utility functions

static String* next_string(String* p)
{
    uint16_t len = p->length;

    return p + 1 + ((len + sizeof(String) - 1) / sizeof(String));
}

// Access functions

uint16_t string_length(String* p)
{
    return p->length;
}

char* string_body(String* p)
{
    return (char*) p + sizeof(*p);
}

// String space functions

void initStrings()
{
    strings_start = &strings[0];
    strings_limit = &strings[STRINGS_SIZE];
    strp = strings_start;
}

String* new_string(const char* str)
{
    String* p = strp;

    p->length = strlen(str);

    strp = next_string(p);
    if (strp > strings_limit) {
        fatal("String space exhausted");
    }

    memcpy(string_body(p), str, string_length(p));
    return p;
}
