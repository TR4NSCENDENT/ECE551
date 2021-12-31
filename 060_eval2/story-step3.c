#include "rand_story.h"
#include "provided.h"


int main(int argc, char const ** argv)
{
  if (argc != 3) {
    fprintf(stderr, "Usage: story-step3 categories/words_file template_file\n");
    exit(EXIT_FAILURE);
  }
  //initialization for categories/words
  category_t * cat_words = malloc(sizeof(*cat_words));
  cat_words->name = NULL;
  cat_words->words = NULL;
  cat_words->n_words = 0;
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  //write categories
  readAll(argv[1], cat_words); 
  writeAll(cats, cat_words);
  //initialization for template
  category_t * template = malloc(sizeof(*template));
  template->name = NULL; //we never use this field
  template->words = NULL;
  template->n_words = 0;
  //initialization for usedWord
  category_t * usedWord = malloc(sizeof(*usedWord));
  usedWord->name = NULL; //we never use this field
  usedWord->words = NULL;
  usedWord->n_words = 0;
  //replace the blank with random words and print
  readAll(argv[2], template);
  replaceAll(template, cats, usedWord, -1);
  printCat(template);
  //free all the alloated space
  freeCat(usedWord, 1);
  //freeCat(cat_words, 1);
  freeCat(template, 1);
  freeCats(cats);
  return EXIT_SUCCESS;
}
