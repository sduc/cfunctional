#include "stack.h"
#include <assert.h>

#define INIT_STACK_ARRAY_SZ 50;

typedef struct
{
  int *stack_array;
  int *sp;
  size_t alloc_size;
} Stack_t;

Stack_ptr Stack_new(void)
{
  Stack_t *p_s = NULL;

  p_s = (Stack_t *) malloc(sizeof(Stack_t));
  if (p_s == NULL) return p_s;

  p_s->alloc_size = INIT_STACK_ARRAY_SZ;
  p_s->stack_array = (int *) malloc(p_s->alloc_size * sizeof(int));
  if (p_s->stack_array == NULL) {
    free(p_s);
    return NULL;
  }
  p_s->sp = p_s->stack_array;
  return p_s;
}

void Stack_free(Stack_ptr s)
{
  if (s) {
    if (s->stack_array) free(s->stack_array);
    free(s);
  }
}

static stack_errno_t stack_realloc_mem(Stack_ptr s, size_t new_sz)
{
  int *new = NULL;

  ASSERT(s);

  new = (int *) malloc(sizeof(int) * new_sz);
  if (!new)
    return STACK_ALLOC_ERR;

  memcpy(new, s->stack_array, s->alloc_size);

  free(s->stack_array);

  s->stack_array = new;
  s->sp = new + s->alloc_size;
  s->alloc_size = new_sz;

  return STACK_SUCCESS;
}

stack_errno_t Stack_push(Stack_ptr s, int el)
{
  stack_errno_t err = STACK_SUCCESS;

  if (s == NULL)
    return STACK_NULL;

  ++(s->sp);
  if (s->sp - s->stack_arry == s->alloc_size) {
    // TODO CHECK INT OVERFLOW ON MULT
    err = stack_realloc_mem(s, s->alloc_size * 2);
    if (err != STACK_SUCCESS)
      return err;
  }

  *(s->sp) = el;
  return err;
}
