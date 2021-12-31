#include "book.hpp"

int main(int argc, const char ** argv) {
  if (argc != 2) {
    err("Usage: cyoa-step2 directory\n");
  }
  Book oneBook(argv[1]);
  oneBook.checkBook();
  run_story(oneBook, 0);
  return EXIT_SUCCESS;
}