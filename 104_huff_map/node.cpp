#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  if (sym != NO_SYM) {
    assert(left == right);
    theMap.insert(std::pair<unsigned,BitString>(sym, b));
  }
  else {
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}

