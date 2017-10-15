#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>
#include <stdio.h>

#define TOKENPASTE(x,y,z) x##y##z
#define TOKENPASTE2(x,y) x##y
#define LINKEDLIST(T,m) TOKENPASTE(LinkedList_,T,m)
#define LINKEDLIST2(T) TOKENPASTE2(LinkedList_,T)

typedef struct LINKEDLIST(TYPE,_Node) {
  TYPE data;
  /* Pointers: */
  struct LINKEDLIST(TYPE,_Node) *prev;
  struct LINKEDLIST(TYPE,_Node) *next;
} LINKEDLIST(TYPE,_Node);

typedef struct {
  LINKEDLIST(TYPE,_Node) *head;
  LINKEDLIST(TYPE,_Node) *tail;
} LINKEDLIST2(TYPE);

/* Initialize the list, O(1) */
void LINKEDLIST(TYPE,_init)(LINKEDLIST2(TYPE) *l) {
  l->head = NULL;
  l->tail = NULL;
}

/* Test whether the list is empty, O(1) */
int LINKEDLIST(TYPE,_empty)(LINKEDLIST2(TYPE) *l) {
  return (l->head == NULL);
}

/* Return size, O(n) */
size_t LINKEDLIST(TYPE,_size)(LINKEDLIST2(TYPE) *l) {
  size_t res = 0;
  LINKEDLIST(TYPE,_Node) *p = l->head;
  while (p) {
    p = p->next;
    ++res;
  }
  return res;
}

/* Access first element, O(1) */
/* WARNING: Undefined behaviour for empty list */
TYPE LINKEDLIST(TYPE,_front)(LINKEDLIST2(TYPE) *l) {
  return l->head->data;
}

/* Access last element, O(1) */
/* WARNING: Undefined behaviour for empty list */
TYPE LINKEDLIST(TYPE,_back)(LINKEDLIST2(TYPE) *l) {
  return l->tail->data;
}

/* Access element at given position, O(n) */
/* WARNING: Undefined behaviour for invalid position */
TYPE LINKEDLIST(TYPE,_get)(LINKEDLIST2(TYPE) *l, size_t pos) {
  size_t i;
  LINKEDLIST(TYPE,_Node) *n = l->head;
  for (i=0; i < pos; ++i) {
    n = n->next;
  }
  return n->data;
}

/* Insert element at beginning, O(1) */
int LINKEDLIST(TYPE,_push_front)(LINKEDLIST2(TYPE) *l, TYPE value) {
  LINKEDLIST(TYPE,_Node) *n = malloc(sizeof(LINKEDLIST(TYPE,_Node)));
  if (!n) return 0;
  n->data = value;
  n->prev = NULL;
  n->next = l->head;
  if (l->head) l->head->prev = n;
  l->head = n;
  if (!l->tail) l->tail = n;
  return 1;
}

/* Access first element and delete it, O(1) */
/* WARNING: Undefined behaviour for empty list */
TYPE LINKEDLIST(TYPE,_pop_front)(LINKEDLIST2(TYPE) *l) {
  LINKEDLIST(TYPE,_Node) *n = l->head;
  TYPE i = n->data;
  l->head = n->next;
  if (n->next) n->next->prev = NULL;
  if (!l->head) l->tail = NULL;
  free(n);
  return i;
}

/* Insert element at the end, O(1) */
int LINKEDLIST(TYPE,_push_back)(LINKEDLIST2(TYPE) *l, TYPE value) {
  LINKEDLIST(TYPE,_Node) *n = malloc(sizeof(LINKEDLIST(TYPE,_Node)));
  if (!n) return 0;
  n->data = value;
  n->prev = l->tail;
  n->next = NULL;
  if (l->tail) l->tail->next = n;
  l->tail = n;
  if (!l->head) l->head = n;
  return 1;
}

/* Access last element and delete it, O(1) */
/* WARNING: Undefined behaviour for empty list */
TYPE LINKEDLIST(TYPE,_pop_back)(LINKEDLIST2(TYPE) *l) {
  LINKEDLIST(TYPE,_Node) *n = l->tail;
  TYPE i = n->data;
  l->tail = n->prev;
  if (n->prev) n->prev->next = NULL;
  if (!l->tail) l->head = NULL;
  free(n);
  return i;
}

/* Insert an element, O(n) */
int LINKEDLIST(TYPE,_insert)(LINKEDLIST2(TYPE) *l, size_t pos, TYPE value) {
  size_t i;
  LINKEDLIST(TYPE,_Node) *n = l->head;
  LINKEDLIST(TYPE,_Node) *prev = NULL;
  for (i=0; i < pos; ++i) {
    if (!n) return 1;
    prev = n;
    n = n->next;
  }
  LINKEDLIST(TYPE,_Node) *new = malloc(sizeof(LINKEDLIST(TYPE,_Node)));
  new->data = value;
  new->prev = prev;
  new->next = n;
  if (prev) {
    prev->next = new;
  } else {
    l->head = new;
  };
  if (!n) {
    l->tail = new;
  };
  return 0;
}

/* Erase an element, O(n) */
int LINKEDLIST(TYPE,_erase)(LINKEDLIST2(TYPE) *l, size_t pos) {
  size_t i;
  LINKEDLIST(TYPE,_Node) *n = l->head;
  LINKEDLIST(TYPE,_Node) *prev = NULL;
  for (i=0; i < pos; ++i) {
    if (!n || !n->next) return 1;
    prev = n;
    n = n->next;
  }
  if (prev) {
    prev->next = n->next;
  } else {
    l->head = n->next;
  };
  if (!n->next) {
    l->tail = prev;
  };
  free(n);
  return 0;
}

/* Clear content, O(n) */
void LINKEDLIST(TYPE,_clear)(LINKEDLIST2(TYPE) *l) {
  LINKEDLIST(TYPE,_Node) *p = l->head;
  LINKEDLIST(TYPE,_Node) *q;
  while (p) {
    q = p;
    p = p->next;
    free(q);
  }
  l->head = NULL;
  l->tail = NULL;
}

/* Dump list content to stderr, O(n) */
void LINKEDLIST(TYPE,_dump)(LINKEDLIST2(TYPE) *l) {
  fprintf(stderr, "fwd: ");
  LINKEDLIST(TYPE,_Node) *n = l->head;
  while (n) {
    fprintf(stderr, "%d ", n->data);
    n = n->next;
  }
  fprintf(stderr, "\nbwd: ");
  n = l->tail;
  while (n) {
    fprintf(stderr, "%d ", n->data);
    n = n->prev;
  }
  fprintf(stderr, "\n");
}

#endif //!_LINKEDLIST_H_
