#include "rand_story.h"
#include "provided.h"
#include <unistd.h>

//a simple generator and initializer for category_t type
category_t * catInit(void) {
  category_t * cat = malloc(sizeof(*cat));
  cat->name = NULL;
  cat->words = NULL;
  cat->n_words = 0;
  return cat;
}

//this function shows the correct usage and exit with failure
void correctUsage(void) {
  fprintf(stderr, "Usage: story-step4 -n(optional) categories/words_file template_file\n");
  exit(EXIT_FAILURE);
}

//this function identifies whether template or categories file go first
void identifier(char ** part_argv, category_t ** cat_words, category_t ** template) {
  category_t * test1 = catInit();
  category_t * test2 = catInit();
  readAll(part_argv[0], test1);
  readAll(part_argv[1], test2);
  char * p1 = strchr(test1->words[0], ':');
  char * p2 = strchr(test2->words[0], '_');
  if (p1 != NULL && p2 != NULL) {
    *cat_words = test1;
    *template = test2;
  }
  else { //if they are NULL due to incorrect format
    *cat_words = test2; //they will be catched during error handling
    *template = test1;
  }
}

int main(int argc, char * argv[]) {
  if ((argc != 3 && argc != 4)) { correctUsage(); }
  int signal = 0;
  char * p1 = NULL;
  char * p2 = NULL;
  char * p[] = {p1, p2};
  int n = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0) { continue; }
    p[n] = argv[i]; //always points to the two file
    n++;
  }
  if (argc == 4) {
    int flag = getopt(argc, argv, "n");
    if (flag == 'n') {
      signal = 1;
    }
    else { correctUsage(); }
  }
  //initialization for categories/words
  category_t * cat_words;
  category_t * template;
  identifier(p, &cat_words, &template);
  category_t * usedWord = catInit();
  //initialization for category array
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  //write the lines from cat_words to cats
  writeAll(cats, cat_words);
  //replace the blank with random words and print
  replaceAll(template, cats, usedWord, signal);
  printCat(template);
  //free all the alloated space
  freeCat(usedWord, 1);
  //cat_words freed elsewhere
  freeCat(template, 1);
  freeCats(cats);
  return EXIT_SUCCESS;
}
