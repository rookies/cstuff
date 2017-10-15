#include <stdio.h>
#include "LinkedList.h"

void LinkedList_init(LinkedList *l) {
  l->head = NULL;
  l->tail = NULL;
}

int LinkedList_empty(LinkedList *l) {
  return (l->head == NULL);
}

size_t LinkedList_size(LinkedList *l) {
  size_t res = 0;
  LinkedListNode *p = l->head;
  while (p) {
    p = p->next;
    ++res;
  }
  return res;
}

Item LinkedList_front(LinkedList *l) {
  return l->head->data;
}

Item LinkedList_back(LinkedList *l) {
  return l->tail->data;
}

Item LinkedList_get(LinkedList *l, size_t pos) {
  size_t i;
  LinkedListNode *n = l->head;
  for (i=0; i < pos; ++i) {
    n = n->next;
  }
  return n->data;
}

int LinkedList_push_front(LinkedList *l, Item value) {
  LinkedListNode *n = malloc(sizeof(LinkedListNode));
  if (!n) return 0;
  n->data = value;
  n->prev = NULL;
  n->next = l->head;
  if (l->head) l->head->prev = n;
  l->head = n;
  if (!l->tail) l->tail = n;
  return 1;
}

Item LinkedList_pop_front(LinkedList *l) {
  LinkedListNode *n = l->head;
  Item i = n->data;
  l->head = n->next;
  if (n->next) n->next->prev = NULL;
  if (!l->head) l->tail = NULL;
  free(n);
  return i;
}

int LinkedList_push_back(LinkedList *l, Item value) {
  LinkedListNode *n = malloc(sizeof(LinkedListNode));
  if (!n) return 0;
  n->data = value;
  n->prev = l->tail;
  n->next = NULL;
  if (l->tail) l->tail->next = n;
  l->tail = n;
  if (!l->head) l->head = n;
  return 1;
}

Item LinkedList_pop_back(LinkedList *l) {
  LinkedListNode *n = l->tail;
  Item i = n->data;
  l->tail = n->prev;
  if (n->prev) n->prev->next = NULL;
  if (!l->tail) l->head = NULL;
  free(n);
  return i;
}

int LinkedList_insert(LinkedList *l, size_t pos, Item value) {
  /* TODO */
}

int LinkedList_erase(LinkedList *l, size_t pos) {
  /* TODO */
}

void LinkedList_clear(LinkedList *l) {
  LinkedListNode *p = l->head;
  LinkedListNode *q;
  while (p) {
    q = p;
    p = p->next;
    free(q);
  }
  l->head = NULL;
  l->tail = NULL;
}

void LinkedList_dump(LinkedList *l) {
  fprintf(stderr, "fwd: ");
  LinkedListNode *n = l->head;
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
