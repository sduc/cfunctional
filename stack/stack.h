#ifndef STACK_H
#define STACK_H

typedef enum
{
  STACK_SUCCESS   = 0,
  STACK_ERROR     = 1,
  STACK_NULL      = 2,
  STACK_ALLOC_ERR = 3,
} stack_errno_t;

typedef Stack_t *Stack_ptr;

Stack_ptr Stack_new(void);
void Stack_free(Stack_ptr s);

stack_errno_t Stack_push(Stack_ptr s, int el);
stack_errno_t Stack_pop(Stack_ptr s, int *el);

#endif
