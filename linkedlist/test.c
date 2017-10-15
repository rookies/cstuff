#include "LinkedList.h"
#include <stdio.h>
#include <cutest/CuTest.h>

void Test_LinkedList_init(CuTest *tc) {
  LinkedList l;
  LinkedList_init(&l);
  CuAssert(tc, "head pointer not null after init", !l.head);
  CuAssert(tc, "tail pointer not null after init", !l.tail);
}

void Test_LinkedList_empty(CuTest *tc) {
  LinkedList l;
  LinkedList_init(&l);
  CuAssert(tc, "list not empty after init", LinkedList_empty(&l));
  LinkedList_push_front(&l, 1);
  CuAssert(tc, "list empty after push", !LinkedList_empty(&l));
}

void Test_LinkedList_size(CuTest *tc) {
  LinkedList l;
  int i;
  LinkedList_init(&l);
  CuAssertIntEquals(tc, 0, LinkedList_size(&l));
  for (i=0; i < 10; ++i) {
    LinkedList_push_front(&l, i);
    CuAssertIntEquals(tc, i+1, LinkedList_size(&l));
  }
}

void Test_LinkedList_pushpopget_front(CuTest *tc) {
  /* Create list & push 10 entries: */
  LinkedList l;
  int i;
  LinkedList_init(&l);
  for (i=0; i < 10; ++i) {
    LinkedList_push_front(&l, i);
  }
  /* Iterate forwards: */
  LinkedListNode *n = l.head;
  for (i=0; i < 10; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, 9-i, n->data);
    n = n->next;
  }
  /* Iterate backwards: */
  n = l.tail;
  for (i=0; i < 10; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, i, n->data);
    n = n->prev;
  }
  /* Test _front() & _pop_front() methods: */
  for (i=0; i < 10; ++i) {
    CuAssertIntEquals(tc, 9-i, LinkedList_front(&l));
    CuAssertIntEquals(tc, 9-i, LinkedList_pop_front(&l));
  }
}

void Test_LinkedList_pushpopget_back(CuTest *tc) {
  /* Create list & push 10 entries: */
  LinkedList l;
  int i;
  LinkedList_init(&l);
  for (i=0; i < 10; ++i) {
    LinkedList_push_back(&l, i);
  }
  /* Iterate forwards: */
  LinkedListNode *n = l.head;
  for (i=0; i < 10; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, i, n->data);
    n = n->next;
  }
  /* Iterate backwards: */
  n = l.tail;
  for (i=0; i < 10; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, 9-i, n->data);
    n = n->prev;
  }
  /* Test _back() & _pop_back() methods: */
  for (i=0; i < 10; ++i) {
    CuAssertIntEquals(tc, 9-i, LinkedList_back(&l));
    CuAssertIntEquals(tc, 9-i, LinkedList_pop_back(&l));
  }
}

void Test_LinkedList_push_mixed(CuTest *tc) {
  /* Create list: */
  LinkedList l;
  int i;
  LinkedList_init(&l);
  /* Push 10..19 using _push_front(): */
  for (i=19; i >= 10; --i) {
    LinkedList_push_front(&l, i);
  }
  /* Push 20..29 using _push_back(): */
  for (i=20; i < 30; ++i) {
    LinkedList_push_back(&l, i);
  }
  /* Push 0..9 using _push_front(): */
  for (i=9; i >= 0; --i) {
    LinkedList_push_front(&l, i);
  }
  /* Push 30..39 using _push_back(): */
  for (i=30; i < 40; ++i) {
    LinkedList_push_back(&l, i);
  }
  /* Iterate forwards: */
  LinkedListNode *n = l.head;
  for (i=0; i < 40; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, i, n->data);
    n = n->next;
  }
  /* Iterate backwards: */
  n = l.tail;
  for (i=0; i < 40; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, 39-i, n->data);
    n = n->prev;
  }
}

void Test_LinkedList_insert(CuTest *tc) { /* TODO */ }

void Test_LinkedList_erase(CuTest *tc) { /* TODO */ }

void Test_LinkedList_clear(CuTest *tc) {
  LinkedList l;
  int i;
  LinkedList_init(&l);
  for (i=0; i < 10; ++i) {
    LinkedList_push_front(&l, i);
  }
  LinkedList_clear(&l);
  CuAssert(tc, "head pointer not null after clear", !l.head);
  CuAssert(tc, "tail pointer not null after clear", !l.tail);
}

int main(void) {
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_LinkedList_init);
  SUITE_ADD_TEST(suite, Test_LinkedList_empty);
  SUITE_ADD_TEST(suite, Test_LinkedList_size);
  SUITE_ADD_TEST(suite, Test_LinkedList_pushpopget_front);
  SUITE_ADD_TEST(suite, Test_LinkedList_pushpopget_back);
  SUITE_ADD_TEST(suite, Test_LinkedList_push_mixed);
  SUITE_ADD_TEST(suite, Test_LinkedList_insert);
  SUITE_ADD_TEST(suite, Test_LinkedList_erase);
  SUITE_ADD_TEST(suite, Test_LinkedList_clear);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
  return 0;
}
