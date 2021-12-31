#include "cyoa.hpp"

int main(int argc, const char ** argv) {
  if (argc != 2) {
    err("Usage: cyoa-step1 filename\n");
  }
  Page onePage(argv[1]);
  onePage.printAll();
  return EXIT_SUCCESS;
}