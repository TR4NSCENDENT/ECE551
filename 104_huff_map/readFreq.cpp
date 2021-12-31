#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream f (fname);
  if (!f.is_open()) {
    std::cerr << "Unable to open " << fname << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * ans = new uint64_t[257]();
  int c = f.get();
  while (f.good()) {
    ans[c]++;
    c = f.get();
  }
  if (f.eof()) {
    f.close();
    ans[256] = 1;
    return ans;
  }
  else {
    std::cerr << "Unable to open " << fname << std::endl;
    delete[] ans;
    exit(EXIT_FAILURE);
  }
}
