#ifndef __BOOK_H__
#define __BOOK_H__
#include "cyoa.hpp"

class Book {
protected:
  std::vector<Page *> pages;
  void getPage(const char * dir, const unsigned pageNum);
public:
  Book(const char * dir);
  int showPage(unsigned pageNum);
  void checkBook();
  std::vector<unsigned> getNext(unsigned pageNum);
  ~Book() {
    std::vector<Page *>::iterator it;
    for (it = pages.begin(); it != pages.end(); ++it) {
      delete *it;
    }
  }
};

void run_story(Book & b, unsigned pageNum);

#endif