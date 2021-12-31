#include "depth.hpp"

int main(int argc, const char ** argv) {
  if (argc != 2) {
    err("Usage: cyoa-step3 directory\n");
  }
  Depth aBook(argv[1]);
  aBook.checkBook();
  aBook.getDepthAndPath();
  aBook.printDepth();
  return EXIT_SUCCESS;
}