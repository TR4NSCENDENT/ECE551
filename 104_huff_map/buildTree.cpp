#include "node.h"

Node *  buildTree(uint64_t * counts) {
  priority_queue_t ans;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      ans.push(new Node(i, counts[i]));
    }
  }
  while (ans.size() > 1) {
    Node * fst = ans.top();
    ans.pop();
    Node * snd = ans.top();
    ans.pop();
    ans.push(new Node(fst, snd));
  }
  return ans.top();
}  
