#define TYPE int
#include "LinkedList.h"
#include <stdio.h>
#include <cutest/CuTest.h>

void Test_LinkedList_int_init(CuTest *tc) {
  LinkedList_int l;
  LinkedList_int_init(&l);
  CuAssert(tc, "head pointer not null after init", !l.head);
  CuAssert(tc, "tail pointer not null after init", !l.tail);
}

void Test_LinkedList_int_empty(CuTest *tc) {
  LinkedList_int l;
  LinkedList_int_init(&l);
  CuAssert(tc, "list not empty after init", LinkedList_int_empty(&l));
  LinkedList_int_push_front(&l, 1);
  CuAssert(tc, "list empty after push", !LinkedList_int_empty(&l));
}

void Test_LinkedList_int_size(CuTest *tc) {
  LinkedList_int l;
  int i;
  LinkedList_int_init(&l);
  CuAssertIntEquals(tc, 0, LinkedList_int_size(&l));
  for (i=0; i < 10; ++i) {
    LinkedList_int_push_front(&l, i);
    CuAssertIntEquals(tc, i+1, LinkedList_int_size(&l));
  }
}

void Test_LinkedList_int_pushpopget_front(CuTest *tc) {
  /* Create list & push 10 entries: */
  LinkedList_int l;
  int i;
  LinkedList_int_init(&l);
  for (i=0; i < 10; ++i) {
    LinkedList_int_push_front(&l, i);
  }
  /* Iterate forwards: */
  LinkedList_int_Node *n = l.head;
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
  /* Test _get() method: */
  for (i=0; i < 10; ++i) {
    CuAssertIntEquals(tc, 9-i, LinkedList_int_get(&l, i));
  }
  /* Test _front() & _pop_front() methods: */
  for (i=0; i < 10; ++i) {
    CuAssertIntEquals(tc, 9-i, LinkedList_int_front(&l));
    CuAssertIntEquals(tc, 9-i, LinkedList_int_pop_front(&l));
  }
}

void Test_LinkedList_int_pushpopget_back(CuTest *tc) {
  /* Create list & push 10 entries: */
  LinkedList_int l;
  int i;
  LinkedList_int_init(&l);
  for (i=0; i < 10; ++i) {
    LinkedList_int_push_back(&l, i);
  }
  /* Iterate forwards: */
  LinkedList_int_Node *n = l.head;
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
  /* Test _get() method: */
  for (i=0; i < 10; ++i) {
    CuAssertIntEquals(tc, i, LinkedList_int_get(&l, i));
  }
  /* Test _back() & _pop_back() methods: */
  for (i=0; i < 10; ++i) {
    CuAssertIntEquals(tc, 9-i, LinkedList_int_back(&l));
    CuAssertIntEquals(tc, 9-i, LinkedList_int_pop_back(&l));
  }
}

void Test_LinkedList_int_push_mixed(CuTest *tc) {
  /* Create list: */
  LinkedList_int l;
  int i;
  LinkedList_int_init(&l);
  /* Push 10..19 using _push_front(): */
  for (i=19; i >= 10; --i) {
    LinkedList_int_push_front(&l, i);
  }
  /* Push 20..29 using _push_back(): */
  for (i=20; i < 30; ++i) {
    LinkedList_int_push_back(&l, i);
  }
  /* Push 0..9 using _push_front(): */
  for (i=9; i >= 0; --i) {
    LinkedList_int_push_front(&l, i);
  }
  /* Push 30..39 using _push_back(): */
  for (i=30; i < 40; ++i) {
    LinkedList_int_push_back(&l, i);
  }
  /* Iterate forwards: */
  LinkedList_int_Node *n = l.head;
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

void Test_LinkedList_int_insert(CuTest *tc) {
  LinkedList_int l;
  LinkedList_int_init(&l);
  CuAssert(tc, "insert(0) failed", LinkedList_int_insert(&l, 0, 21) == 0);
  CuAssert(tc, "insert(1) failed", LinkedList_int_insert(&l, 1, 42) == 0);
  CuAssert(tc, "insert(5) should fail", LinkedList_int_insert(&l, 5, 73) != 0);
  /* fwd: */
  CuAssertPtrNotNull(tc, l.head);
  CuAssertIntEquals(tc, 21, l.head->data);
  CuAssertPtrNotNull(tc, l.head->next);
  CuAssertIntEquals(tc, 42, l.head->next->data);
  CuAssertPtrEquals(tc, NULL, l.head->next->next);
  /* bwd: */
  CuAssertPtrNotNull(tc, l.tail);
  CuAssertIntEquals(tc, 42, l.tail->data);
  CuAssertPtrNotNull(tc, l.tail->prev);
  CuAssertIntEquals(tc, 21, l.tail->prev->data);
  CuAssertPtrEquals(tc, NULL, l.tail->prev->prev);
}

void Test_LinkedList_int_erase(CuTest *tc) {
  /* Create & fill list: */
  LinkedList_int l;
  int i;
  LinkedList_int_init(&l);
  for (i=0; i < 3; ++i) {
    LinkedList_int_push_back(&l, i);
  }
  /* Erase item #0: */
  CuAssert(tc, "erase(0) failed", LinkedList_int_erase(&l, 0) == 0);
  LinkedList_int_Node *n = l.head;
  for (i=1; i < 3; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, i, n->data);
    n = n->next;
  }
  n = l.tail;
  for (i=2; i >= 1; --i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, i, n->data);
    n = n->prev;
  }
  /* Erase item #2: */
  CuAssert(tc, "erase(2) should fail", LinkedList_int_erase(&l, 2) != 0);
  return;
  n = l.head;
  for (i=1; i < 3; ++i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, i, n->data);
    n = n->next;
  }
  n = l.tail;
  for (i=2; i >= 1; --i) {
    CuAssertPtrNotNull(tc, n);
    CuAssertIntEquals(tc, i, n->data);
    n = n->prev;
  }
  /* Erase item #0: */
  CuAssert(tc, "erase(0) failed", LinkedList_int_erase(&l, 0) == 0);
  CuAssertPtrNotNull(tc, l.head);
  CuAssertIntEquals(tc, 1, l.head->data);
  CuAssertPtrNotNull(tc, l.head->next);
  CuAssertIntEquals(tc, 2, l.head->next->data);
  CuAssertPtrEquals(tc, NULL, l.head->next->next);
  CuAssertPtrNotNull(tc, l.tail);
  CuAssertIntEquals(tc, 2, l.tail->data);
  CuAssertPtrNotNull(tc, l.tail->prev);
  CuAssertIntEquals(tc, 1, l.tail->prev->data);
  CuAssertPtrEquals(tc, NULL, l.tail->prev->prev);
  /* Erase item #0: */
  CuAssert(tc, "erase(0) failed", LinkedList_int_erase(&l, 0) == 0);
  CuAssertPtrNotNull(tc, l.head);
  CuAssertIntEquals(tc, 2, l.head->data);
  CuAssertPtrEquals(tc, NULL, l.head->next);
  CuAssertPtrNotNull(tc, l.tail);
  CuAssertIntEquals(tc, 2, l.tail->data);
  CuAssertPtrEquals(tc, NULL, l.tail->prev);
  /* Erase item #0: */
  CuAssert(tc, "erase(0) failed", LinkedList_int_erase(&l, 0) == 0);
  CuAssertPtrEquals(tc, NULL, l.head);
  CuAssertPtrEquals(tc, NULL, l.tail);
}

void Test_LinkedList_int_clear(CuTest *tc) {
  LinkedList_int l;
  int i;
  LinkedList_int_init(&l);
  for (i=0; i < 10; ++i) {
    LinkedList_int_push_front(&l, i);
  }
  LinkedList_int_clear(&l);
  CuAssert(tc, "head pointer not null after clear", !l.head);
  CuAssert(tc, "tail pointer not null after clear", !l.tail);
}

int main(void) {
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, Test_LinkedList_int_init);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_empty);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_size);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_pushpopget_front);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_pushpopget_back);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_push_mixed);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_insert);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_erase);
  SUITE_ADD_TEST(suite, Test_LinkedList_int_clear);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
  return 0;
}
