#ifndef __PAGE_H__
#define __PAGE_H__
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <set>
#include <iostream>
#include <exception>
#include <limits>

typedef std::pair<unsigned, std::string> choice; //page number and content

class Page {
  std::vector<choice> navigation;
  std::vector<std::string> story;
  int pageState; //-1 for lose, 1 for win, 0 for non-ending
  void read(const char * filename); //parse the content
  void getChoice(const std::string & line); 
public:
  Page() : pageState(0) {}
  Page(const char * filename); 
  std::vector<unsigned> next(); //possible next pages
  void printAll(); 
  int getState();
};

void err(const char * msg);
unsigned long getNumHelper(const std::string & str);
unsigned getNum(const std::string & str);

#endif
