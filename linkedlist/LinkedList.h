#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>

typedef int Item;

typedef struct llnode {
  Item data;
  /* Pointers: */
  struct llnode *prev;
  struct llnode *next;
} LinkedListNode;

typedef struct {
  LinkedListNode *head;
  LinkedListNode *tail;
} LinkedList;

/* Initialize the list, O(1) */
void LinkedList_init(LinkedList *l);

/* Test whether the list is empty, O(1) */
int LinkedList_empty(LinkedList *l);

/* Return size, O(n) */
size_t LinkedList_size(LinkedList *l);

/* Access first element, O(1) */
/* WARNING: Undefined behaviour for empty list */
Item LinkedList_front(LinkedList *l);

/* Access last element, O(1) */
/* WARNING: Undefined behaviour for empty list */
Item LinkedList_back(LinkedList *l);

/* Access element at given position, O(n) */
/* WARNING: Undefined behaviour for invalid position */
Item LinkedList_get(LinkedList *l, size_t pos);

/* Insert element at beginning, O(1) */
int LinkedList_push_front(LinkedList *l, Item value);

/* Access first element and delete it, O(1) */
/* WARNING: Undefined behaviour for empty list */
Item LinkedList_pop_front(LinkedList *l);

/* Insert element at the end, O(1) */
int LinkedList_push_back(LinkedList *l, Item value);

/* Access last element and delete it, O(1) */
/* WARNING: Undefined behaviour for empty list */
Item LinkedList_pop_back(LinkedList *l);

/* Insert an element, O(n) */
int LinkedList_insert(LinkedList *l, size_t pos, Item value);

/* Erase an element, O(n) */
int LinkedList_erase(LinkedList *l, size_t pos);

/* Clear content, O(n) */
void LinkedList_clear(LinkedList *l);

/* Dump list content to stderr, O(n) */
void LinkedList_dump(LinkedList *l);

#endif //!_LINKEDLIST_H_
