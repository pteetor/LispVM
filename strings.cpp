//
//  String heap for LispVM
//

#include <cstring>
#include "LispVM.h"

struct String {
    uint16_t flags;
    uint16_t length;      // Number of characters (following header)
    uint16_t height;      // Height of AVL tree at this node
    uint16_t _unused16;
    String* left;         // Left branch of AVL tree
    String* right;        // Right branch of AVL tree
    String* fwd;          // Forwarding address for GC
};

const int STRINGS_SIZE = 1000;

String strings[STRINGS_SIZE];

String* strings_start;
String* strings_limit;
String* strings_free;

// Utility functions

static String* next_string(String* p, uint len)
{
  String* q = p + 1 + ((len + sizeof(String) - 1) / sizeof(String));
  if (q < strings_limit) {
    return q;
  } else {
    return (String*) 0;
  }
}

static String* next_string(String* p)
{
  return next_string(p, p->length);
}

static String* alloc_string(uint nChar)
{
  auto q = next_string(strings_free, nChar);
  if (q == 0) {
    // TODO: Compactify the string space; update strings_free; try alloc again
    fatal("String space exhausted");
  }

  auto p = strings_free;
  strings_free = q;

  return p;
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
    strings_free = strings_start;
}

String* new_string(const char* str)
{
    // TODO: Check: Is string already in the AVL tree?

    auto len = strlen(str);
    auto p = alloc_string(len);

    p->length = len;
    memcpy(string_body(p), str, len);

    p->height = 1;
    p->left = 0;
    p->right = 0;

    // TODO: Perform AVL insert

    return p;
}
