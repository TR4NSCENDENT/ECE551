#include "rand_story.h"
#include "provided.h"

int main(int argc, char const ** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: story-step1 template_file\n");
    exit(EXIT_FAILURE);
  }
  category_t * cat = malloc(sizeof(*cat));
  cat->name = NULL;
  cat->words = NULL;
  cat->n_words = 0;
  readAll(argv[1], cat);
  replaceAll(cat, NULL, NULL, -1);
  printCat(cat);
  freeCat(cat, 1);
  return EXIT_SUCCESS;
}
