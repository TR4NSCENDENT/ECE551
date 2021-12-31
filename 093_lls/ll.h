#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template <typename T> class LinkedList;
typedef LinkedList<int> IntList;

template <typename T> class LinkedList {
private:
  class Node { 
  public: 
    T data;
    Node * next; 
    Node * prev; 
    Node(const T & data_, 
         Node * next_, 
         Node * prev_) : data(data_), next(next_), prev(prev_)  {}
  };
  Node * head;
  Node * tail;
  int size;
public:
// member functions
  LinkedList() : head(NULL), tail(NULL), size(0) {} 
  LinkedList(const LinkedList & rhs) {
    size = 0;
    const Node * p = rhs.head;
    head = NULL;
    tail = NULL;
    while (p != NULL) {
      addBack(p->data);
      p = p->next;
    }
  }
  void nodeSwap(Node * & a, Node * & b) {
    Node * temp = a;
    a = b;
    b = temp;
  }
  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList temp(rhs);
    nodeSwap(head, temp.head);
    nodeSwap(tail, temp.tail);
    size = temp.size;
    return *this;
  }
  ~LinkedList() {
    Node * p = head;
    Node * q = NULL;
    while (p != NULL) {
      q = p;
      p = p->next;
      delete q;
    }
  }
  void addFront (const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) { tail = head; }
    else { head->next->prev = head; }
    size++;
  }
  void addBack (const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) { head = tail; }
    else { tail->prev->next = tail; }
    size++;
  }
  void updateLL(Node * p) {
    if (p->prev != NULL) { p->prev->next = p->next; }
    else { head = p->next; }
    if (p->next != NULL) { p->next->prev = p->prev; }
    else { tail = p->prev; }
  }
  bool remove (const T & item) {
    Node * p = head;
    if (p == NULL) { return false; }
    while (p != NULL) { 
      if (p->data != item) {
	p = p->next;
	continue;
      }
      updateLL(p);
      delete p;
      size--;
      return true;
    }
    return false;
  }
  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw std::exception();
    }
    Node * p = head;
    for (int i = 0; i < index; i++) {
      p = p->next;
    }
    return p->data;
  }
  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw std::exception();
    }
    const Node * p = head;
    for (int i = 0; i < index; i++) {
      p = p->next;
    }
    return p->data;
  }
  int find(const T & item) const {
    if (head == NULL) { return -1; }
    const Node * p = head;
    int count = 0;
    while (p != NULL) {
      if (p->data != item) {
	p = p->next;
	count++;
      }
      else { return count; }
    }
    return -1;
  }
  int getSize() const {
    return size;
  }
  friend void chkContinuous(const IntList & list);
  friend void testList(void);
};


#endif
