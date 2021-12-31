#ifndef __DEPTH_H__
#define __DEPTH_H__
#include <map>
#include "book.hpp"


typedef std::vector<std::vector<std::pair<unsigned, unsigned> > > paths_t;

class Depth : public Book {
  std::map<unsigned, unsigned> theMap;
  paths_t paths;
public:
  Depth(const char * dir);
  void getDepthAndPathHelper(unsigned pageNum, 
                             std::set<unsigned> visited, 
                             unsigned depth,
                             std::vector<std::pair<unsigned, unsigned> > path);
  void getDepthAndPath();
  void printDepth();
  void printPath();
  ~Depth() {}
};

#endif
