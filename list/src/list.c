#include "list.h"
#include "list_el.h"

typedef ListPtr ListIterator;

struct List_t
{
  ListElPtr node;
  ListPtr   next;
};

/*----------------------------------------------------------------------
 *                    ITERATOR FUNCTIONS
 *--------------------------------------------------------------------*/

ListIterator List_get_iterator(ListPtr l)
{
  return l;
}

ListIterator ListIterator_next(ListIterator it)
{
  ListIterator next = it->next;
}

int ListIterator_is_end(ListIterator it)
{
  return it == NULL;
}

ListElPtr List_get_iterator_el(ListPtr l, ListIterator it)
{
  return it->node;
}

/*----------------------------------------------------------------------
 *                    LIST FUNCTIONS
 *--------------------------------------------------------------------*/

ListPtr List_new(void)
{
  List l = NIL;

  l = (ListPtr) malloc(sizeof(struct List_el_t));
  if (l != NULL) {
    l->node = NULL;
    l->next = NIL;
  }
  return l;
}

void List_delete(ListPtr l)
{
  List next;

  while (l != NIL) {
    next = l->next;
    if (l->node != NULL) {
      ListEl_free(l->node);
      l->node = NULL;
    }
    free(l);
    l = next;
  };
}

List_errno_t List_append(ListPtr l, const ListElPtr el)
{
  ListPtr it = l;
  if (l == NULL) {
    return LIST_NULL;
  }

  if (l->node == NULL) {
    l->node = ListEl_new();
    ListEl_copy(l->node, el);
  }

  while(it->next != NIL)
  {
    it = it->next;
  }
  
  it->next = List_new(); 
  if (it->next == NIL) {
    return LIST_MEMALLOC_ERR;
  }

  it = it->next;

  it->node = ListEl_new();
  if (it->node == NULL) {
    return LIST_MEMALLOC_ERR;
  }

  return ListEl_copy(it->node, el);
}

List_errno_t List_remove_el(ListPtr l, ListElPtr rm_el)
{
  ListPtr it = l;
  ListElPtr el;
  if (l == NULL) {
    return LIST_NULL;
  }

  do {
    el = it->node;
    if (el->ops.isEqual(el, rm_el)) {
    }
  } while (it->next != NIL);
}
