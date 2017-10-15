#include "LinkedList.h"
#include <stdio.h>

int main(void) {
  LinkedList list;
  int i;
  LinkedList_init(&list);
  fprintf(stderr, "%lu\n", LinkedList_size(&list));
  fprintf(stderr, "%d\n", LinkedList_empty(&list));
  LinkedList_dump(&list);
  for (i=0; i < 50; ++i) {
    LinkedList_push_front(&list, i);
  }
  fprintf(stderr, "%lu\n", LinkedList_size(&list));
  fprintf(stderr, "%d\n", LinkedList_empty(&list));
  LinkedList_dump(&list);
  for (i=50; i < 100; ++i) {
    LinkedList_push_back(&list, i);
  }
  fprintf(stderr, "%lu\n", LinkedList_size(&list));
  fprintf(stderr, "%d\n", LinkedList_empty(&list));
  LinkedList_dump(&list);
  for (i=0; i < 50; ++i) {
    LinkedList_pop_front(&list);
  }
  fprintf(stderr, "%lu\n", LinkedList_size(&list));
  fprintf(stderr, "%d\n", LinkedList_empty(&list));
  LinkedList_dump(&list);
  for (i=50; i < 100; ++i) {
    LinkedList_pop_back(&list);
  }
  fprintf(stderr, "%lu\n", LinkedList_size(&list));
  fprintf(stderr, "%d\n", LinkedList_empty(&list));
  LinkedList_dump(&list);
  return 0;
}
