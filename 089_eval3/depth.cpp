#include "depth.hpp"

Depth::Depth(const char * dir) : Book(dir) {}

void Depth::getDepthAndPathHelper(unsigned pageNum, 
                                  std::set<unsigned> visited, 
                                  unsigned depth,
                                  std::vector<std::pair<unsigned, unsigned> > path) {
  if (visited.count(pageNum)) { return; } 
  visited.insert(pageNum); //record this visit
  unsigned state = pages[pageNum-1]->getState();
  if (state == 0) { 
    std::vector<unsigned> nextPages = pages[pageNum-1]->next();
    std::vector<unsigned>::iterator it;
    for (it = nextPages.begin(); it != nextPages.end(); ++it) {
      theMap.insert(std::pair<unsigned, unsigned>(*it, depth+1));
    } //make depth breadth-first
    it = nextPages.begin();
    for (size_t i = 0; i < nextPages.size(); i++) {
      path.push_back(std::pair<unsigned, unsigned>(pageNum, i+1));
      getDepthAndPathHelper(*it, visited, depth+1, path);
      path.pop_back();
      ++it;
    }
  }
  else if (state == 1) {
    path.push_back(std::pair<unsigned, unsigned>(pageNum, 0));
    paths.push_back(path);
  }
  
}

void Depth::getDepthAndPath() {
  std::set<unsigned> visited;
  theMap.insert(std::pair<unsigned, unsigned>(1, 0));
  std::vector<std::pair<unsigned, unsigned> > basePath;
  getDepthAndPathHelper(1, visited, 0, basePath);
}

void Depth::printDepth() {
  std::map<unsigned, unsigned>::iterator it;
  for (unsigned i = 1; i <= pages.size(); i++) {
    it = theMap.find(i);
    if (it != theMap.end()) {
      std::cout << "Page " << it->first << ':' << it->second << std::endl;
    }
    else {
      std::cout << "Page " << i << " is not reachable" << std::endl;
    }
  }
}

void Depth::printPath() {
  if (paths.empty()) {
    std::cout << "This story is unwinnable!" << std::endl;
    return;
  }
  paths_t::const_iterator it_path;
  std::vector<std::pair<unsigned, unsigned> >::const_iterator it_step;
  for (it_path = paths.begin(); it_path != paths.end(); ++it_path) {
    for (it_step = (*it_path).begin(); it_step != (*it_path).end(); ++it_step) {
      if ((*it_step).second == 0) {
        std::cout << (*it_step).first << "(win)" << std::endl;
      }
      else {
        std::cout << (*it_step).first << '(' << (*it_step).second << "),";
      }
    }
  }
}