#include <assert.h>
#include <exception>
#include "il.hpp"

void chkContinuous(const IntList & list) {
  IntList::Node * p = list.head;
  IntList::Node * q = list.tail;
  while (p->next != NULL) {
    p = p->next;
  }
  while (q->prev != NULL) {
    q = q->prev;
  }
  assert(p == list.tail);
  assert(q == list.head);
}

void testList(void) {
  IntList list1;
  assert(list1.head == NULL && list1.tail == NULL);
  for (int i = 0; i < 10; i++) {
    assert(list1.getSize() == i);
    list1.addFront(i);
    for (int j = 0; j < i; j++) {
      assert(list1[list1.find(j)] == j);
    }
    assert(list1.head->data == i && list1.tail->data == 0);
  }
  assert(list1.tail->next == NULL);
  IntList list2(list1);
  IntList list3;
  list3 = list1;
  assert(list1.head != list2.head);
  assert(list1.head->next != list2.head->next);
  assert(list1.tail != list3.tail);
  assert(list1.head->next != list3.head->next);
  try {
    int temp = list1[1000];
  }
  catch(std::exception & e) {}
  IntList list4;
  for (int i = 0; i < 10; i++) {
    assert(list4.getSize() == i);
    list4.addBack(i);
    for (int j = 0; j < i; j++) {
      assert(list4[j] == j);
    }
    assert(list4.head->data == 0 && list4.tail->data == i);
  }
  const int x = 99;
  list4.addFront(x);
  list4.addBack(x);
  assert(list4[0] == 99);
  assert(list1.find(-1) == -1);
  list4[3] = -1;
  assert(list4.remove(99));
  assert(!(list4.remove(98)));
  assert(list4.tail->data == 99);
  list1.remove(0);
  list1.remove(9);
  list2.remove(4);
  assert(list2.getSize() == 9);
  assert(list3.remove(100) == false);
  assert(list3.remove(9));
  assert(list3[8] == 0);
  chkContinuous(list1);
  chkContinuous(list2);
  chkContinuous(list3);
  chkContinuous(list4);
  IntList list5;
  assert(list5.remove(1) == false);
  try {
    int temp = list5[2];
  }
  catch(std::exception & e) {}
  assert(list5.find(1) == -1);
  list2 = list5;
  list1 = list3;
}

int main(int argc, char const *argv[])
{
  testList();
  return EXIT_SUCCESS;
}
