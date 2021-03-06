#ifndef _IL_HPP_
#define _IL_HPP_

#include <cstdlib>
class IntList;
void testList(void);
void chkContinuous(const IntList & list);
class IntList {
 private:
  class Node {
   public:
    int data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(int d) : data(d), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  IntList();
  IntList(const IntList & rhs);
  IntList & operator=(const IntList & rhs);
  ~IntList();
  void addFront(const int & item);
  void addBack(const int & item);
  bool remove(const int & item);
  int & operator[](int index);
  const int & operator[](int index) const;
  int find(const int & item);
  int getSize() const;
  friend void testList(void);
  friend void chkContinuous(const IntList & list);
};

#endif
