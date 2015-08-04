#ifndef LIST_H
#define LIST_H

typedef List_t* ListPtr;
typedef List_el_t* ListElPtr;

typedef enum
{
  LIST_SUCCESS      =  0,
  LIST_ERROR        = -1,
  LIST_NULL         = -2,
  LIST_MEMALLOC_ERR = -3,
  LIST_INVAL_SIZE   = -4,
} list_errno_t;

#define NIL NULL

ListPtr List_new(void);
void List_delete(ListPtr);

list_errno_t List_append(
    ListPtr         l,
    const ListElPtr el
);

list_errno_t List_remove_el(
    ListPtr     l,
    ListElPtr   rm_el
);

list_errno_t List_remove_all_el(
    ListPtr     l,
    ListElPtr   rm_el
);

size_t List_size(
    ListPtr   l,
);

int List_empty(
    ListPtr   l
);

#endif
