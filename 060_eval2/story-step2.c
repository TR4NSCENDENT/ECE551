#include "rand_story.h"
#include "provided.h"

int main(int argc, char const ** argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: story-step2 words_file\n");
    exit(EXIT_FAILURE);
  }
  category_t * lines = malloc(sizeof(*lines));
  lines->name = NULL;
  lines->words = NULL;
  lines->n_words = 0;
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  readAll(argv[1], lines);
  writeAll(cats, lines);
  printCats(cats);
  freeCats(cats);
  return EXIT_SUCCESS;
}
