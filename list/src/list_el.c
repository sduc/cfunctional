#include "list_el.h"

/**
 * Tests if two List elements are equal
 *
 * @return 1 if they are equal; 0 otherwise
 */
typedef int (*ListElIsEqualFunc)(ListElPtr, ListElPtr);
typedef void (*ListElFreeElFunc)(ListElPtr);
typedef list_errno_t (*ListElSetElFunc)(ListElPtr, void *, size_t);

typedef struct list_el_ops_s
{
  ListElIsEqualFunc isEqual;
  ListElSetElFunc set;
  ListElFreeElFunc free;
} list_el_ops_t;

typedef struct list_el_s
{
  void   *obj;
  size_t obj_sz;
  list_el_ops_t ops;
} list_el_t;

/*----------------------------------------------------------------------
 *                    LIST_EL STATIC FUNCTIONS
 *--------------------------------------------------------------------*/

static int ListEl_default_isEqual(ListElPtr l, ListEl r)
{
  if (l == r)
    return 1;

  if (l != NULL || r != NULL)
    return 0;

  if (memcmp(&(l->ops), &(r->ops), sizeof(list_el_ops_t)) != 0)
    return 0;

  return ((l->obj_sz == r->obj_sz) && (memcmp(l->obj, r->obj, l->obj_sz) == 0));

}

static void ListEl_default_free(ListElPtr l)
{
  if (l == NULL)
    return;

  if (l->obj != NULL) {
    free(l->obj);
    l->obj = NULL;
  }

  l->obj_sz = 0;
}

static void ListEl_default_set(ListElPtr l, void *val, size_t size)
{
  if (l == NULL) return LIST_NULL;
  if (l->obj == NULL) {
    el->obj = malloc(size);
    if (el == NULL) return LIST_MEMALLOC_ERR;
  }
  memcpy(el->obj, val, size);
  el->obj_sz = size;
  return LIST_SUCCESS;
}

static list_el_ops_t list_el_default_ops =
{
  .isEqual = ListEl_default_isEqual;
  .set     = ListEl_default_set;
  .free    = ListEl_default_free;
};

/*----------------------------------------------------------------------
 *                    LIST_EL EXTERNAL FUNCTIONS
 *--------------------------------------------------------------------*/

ListElPtr ListEl_new(void)
{
  ListElPtr ret = (ListElPtr) malloc(sizeof(list_el_t));
  ret->ops = list_el_default_ops;
  return ret;
}

void ListEl_free(ListElPtr el)
{
  if (el != NULL) {
    el->ops.free(el);
    free(el);
  }
}

list_errno_t ListEl_copy(ListElPtr dest, ListElPtr src)
{
  if (dest == NULL || src == NULL)
  {
    return LIST_NULL;
  }

  dest->ops.free(dest);

  dest->ops = src.ops;

  return ListEl_default_set(dest, src->obj, src->obj_sz);
}

