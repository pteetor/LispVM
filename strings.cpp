//
//  String heap for LispVM
//

#include <cstring>
#include "LispVM.h"

const int STRINGS_SIZE = 1000;

String strings[STRINGS_SIZE];

String* strings_start;
String* strings_limit;
String* strings_free;
String* strings_tree;

// Forward declarations

static String* find_string(String* node, const char* str, size_t len);
static String* insert_string(String* node, String* p);

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

static String* alloc_string(const char* str, uint len)
{
  auto q = next_string(strings_free, len);

  // This check should never fail because the caller
  // was supposed to check could_alloc_string() before
  // requesting allocation.
  if (q == 0) {
    fatal("String space exhausted");
  }

  auto p = strings_free;
  strings_free = q;

  p->length = len;
  memcpy(string_body(p), str, len);

  p->height = 1;
  p->left = 0;
  p->right = 0;

  return p;
}

// Return true iff sufficient space remains for a new string
static bool could_alloc_string(uint nChar)
{
  return (next_string(strings_free, nChar) != 0);
}

static int max(int a, int b)
{
  return (a > b) ? a : b;
}

static int min(int a, int b)
{
  return (a < b) ? a : b;
}

// Access functions

uint16_t string_length(String* p)
{
  return p->length;
}

char* string_body(String* p)
{
  return p->contents;
}

// String space functions

void initStrings()
{
  strings_start = &strings[0];
  strings_limit = &strings[STRINGS_SIZE];
  strings_free = strings_start;
  strings_tree = nullptr;
}

String* new_string(const char* str)
{
  auto len = strlen(str);
  String* p = find_string(strings_tree, str, len);

  if (p != nullptr)
    return p;

  if (!could_alloc_string(len)) {
    // TODO: Compactify string space
    fatal("String space exhausted, GC not available");

    // After GC ...
    if (!could_alloc_string(len))
      fatal("String space exhausted, even after compactification");
  }

  p = alloc_string(str, len);
  strings_tree = insert_string(strings_tree, p);
  return p;
}

int string_cmp(String *p, const char* q, size_t n)
{
  size_t n0 = min(p->length, n);
  auto cmp = strncmp(string_body(p), q, n0);

  if (cmp != 0) {
    return cmp;
  }

  // Here, cmp == 0, so the initial segment of
  // one string matched the other string entirely.
  // The shorter string is "less than" the longer string.
  if (p->length == n) {
    return 0;
  } else if (p->length < n) {
    return -1;
  } else {    // p->length > n
    return +1;
  }
}

int string_cmp(String *p, String *q)
{
  return string_cmp(p, string_body(q), string_length(q));
}

// AVL tree: Forward declarations

static int height(String *N);
static String* rightRotate(String *y);
static String* leftRotate(String *y);
static int getBalance(String *N);
static String* minValueNode(String* node);

// AVL tree: Search for string

static String* find_string(String* node, const char* str, size_t len)
{
  if (node == nullptr) {
    return nullptr;
  }

  auto cmp = string_cmp(node, str, len);

  if (cmp > 0)
    return find_string(node->left, str, len);
  else if (cmp < 0)
    return find_string(node->right, str, len);
  else
    return node;
}

// AVL tree: Insert into tree

static String* insert_string(String* node, String* p) {

  // Perform the normal BST insertion
  if (node == nullptr)
    return p;

  auto cmp = string_cmp(p, node);

  if (cmp < 0)
    node->left = insert_string(node->left, p);
  else if (cmp > 0)
    node->right = insert_string(node->right, p);
  else
    return node;

  // Update height of this ancestor node
  node->height = 1 + max(height(node->left),
                         height(node->right) );

  // Get the balance factor of this ancestor node
  int balance = getBalance(node);

  // If this node becomes unbalanced,
  // then there are 4 cases

  // Left Left Case
  if (balance > 1 && string_cmp(p, node->left) < 0)   // key < node->left->key
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && string_cmp(p, node->right) > 0)   // key > node->right->key
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && string_cmp(p, node->left) > 0) {   // key > node->left->key
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && string_cmp(p, node->right) < 0) {   // key < node->right->key
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // Return the (unchanged) node pointer
  return node;
}

// AVL tree: Delete from tree

// TODO

// AVL tree: Utility functions

// A utility function to get the height of the tree
static int height(String *N) {
  if (N == nullptr)
    return 0;
  return N->height;
}

// A utility function to right
// rotate subtree rooted with y
static String *rightRotate(String *y) {
  String *x = y->left;
  String *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = 1 + max(height(y->left),
                      height(y->right));
  x->height = 1 + max(height(x->left),
                      height(x->right));

  // Return new root
  return x;
}

// A utility function to left rotate
// subtree rooted with x
static String *leftRotate(String *x) {
  String *y = x->right;
  String *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = 1 + max(height(x->left),
                      height(x->right));
  y->height = 1 + max(height(y->left),
                      height(y->right));

  // Return new root
  return y;
}

// Get balance factor of node N
static int getBalance(String *N) {
  if (N == nullptr)
    return 0;
  return height(N->left) - height(N->right);
}

// Given a non-empty binary search tree,
// return the node with minimum key value
// found in that tree. Note that the entire
// tree does not need to be searched.
static String * minValueNode(String* node) {
  String* current = node;

  // loop down to find the leftmost leaf
  while (current->left != nullptr)
    current = current->left;

  return current;
}

// Support and debugging

static void visit_string_heap(String* node, void visitor(String*))
{
  if (node == nullptr)
    return;
  visit_string_heap(node->left, visitor);
  visitor(node);
  visit_string_heap(node->right, visitor);
}

void visit_string_heap(void vistor(String*))
{
  visit_string_heap(strings_tree, vistor);
}

void dump_string(String* p)
{
  std::cout << "String* " << p << " = [" << p->length << "] <";
  for (int i = 0; i < p->length; ++i)
  {
    std::cout << p->contents[i];
  }
  std::cout << ">\n";
}
