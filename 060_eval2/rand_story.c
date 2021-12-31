#include "rand_story.h"

void giveErr(const char * err_msg, const char * line) {
  if (line != NULL) { fprintf(stderr, "In: %s", line); }
  fprintf(stderr, "%s\n", err_msg);
  exit(EXIT_FAILURE);
}

void * tryMalloc(size_t size) {
  void * res = malloc(size);
  if (res == NULL) { giveErr("Unable to malloc!", NULL); }
  return res;
}

void * tryRealloc(void * p, size_t size) {
  void * res = realloc(p, size);
  if (res == NULL) { giveErr("Unable to realloc!", NULL); }
  return res;
}

char * my_strsep(char ** str, const char c) {
  char * token = *str;
  char * dl = strchr(*str, c); //delimiter
  if (dl == NULL) { return NULL; }
  *dl = '\0';
  *str = dl + 1; //make str point to the remaining part
  return token;
}

char * my_strdup(const char * str) {
  if (str == NULL) { return NULL; }
  return strdup(str);
}

char ** extractor_helper(char * const str, const char c, const int n) {
  char * rem = str; //remaining part of str
  char ** ans = malloc(n * sizeof(*ans));
  for (int i = 0; i < n - 1; i++) {
    if (i > 0 && ans[i-1] == NULL) { //if last extraction get nothing
      ans[i] = NULL; //do not call those functions again
      continue;
    } 
    ans[i] = my_strdup(my_strsep(&rem, c)); //store the part in a new place
  }
  ans[n-1] = my_strdup(rem);
  return ans;
}

char ** extractor(const char * const line, const char c, const int n) {
  char * str = strdup(line);
  char ** parts = extractor_helper(str, c, n);
  if (parts[0] == NULL) { //no delimiter remains
    free(str);
    freeParts(parts, n);
    return NULL;
  } 
  if (parts[n - 1] == NULL) { //the delimiter is not enough
    fprintf(stderr, "In: %s", line);
    fprintf(stderr, "The number of '%c' is less than %d!\n", c, n - 1);
    exit(EXIT_FAILURE);
  }
  free(str);
  return parts;
}

char * constructor(char ** parts, const char * word) {
  size_t total_len = 0;
  for (int i = 0; i < 3; i++) { //only use for templates so hardcode 3
    if (i == 1) { total_len += strlen(word); }
    else { total_len += strlen(parts[i]); }
  }
  //create a space to hold all those parts
  char * ans = tryMalloc(total_len * sizeof(*ans) + 1);  
  ans[0] = '\0'; //initialize ans
  for (int j = 0; j < 3; j++) {
    if (j == 1) { strcat(ans, word); }
    else { strcat(ans, parts[j]); } //append them to construct
  }
  return ans;
}

int isValidInt(char * category) {
  char * endp = category;
  long int index = strtol(category, &endp, 10);
  if (index > 0 && *endp == '\0') { return index; } //exclude decimal point
  return 0; //index = 0 if not valid integer
}

const char * chooseProvious(int index, category_t * usedWord) {
  if (index > usedWord->n_words) { 
    giveErr("Invalid reference detected!", NULL); 
  }
  return usedWord->words[usedWord->n_words - index];
}

void rmWord(const char * new_word, char * category, catarray_t * cats) {
  category_t * p = NULL; //use p to loop over arr
  for (p = cats->arr; p - cats->arr < cats->n; p++) {
    if (strcmp(category, p->name) == 0) { //find its category
      for (int i = 0; i < p->n_words; i++) {
	if (strcmp(new_word, p->words[i]) == 0) { //find its position in words
	  free(p->words[i]);
	  p->words[i] = my_strdup("");
	  return;
	}
      }
    }
  }
}

void checkAvailability(char * category, catarray_t * cats) {
  int count = 0;
  category_t * p = NULL; 
  for (p = cats->arr; p - cats->arr < cats->n; p++) {
    if (strcmp(category, p->name) == 0) { //find its category
      for (int i = 0; i < p->n_words; i++) {
	if (*p->words[i] != '\0') { count++; }
      } //count how many are not empty
      if (count == 0) { giveErr("Run out of words!", category); }
    }
  }
}

const char * chooseBetterWord(char * category, catarray_t * cats, category_t * usedWord) {
  if (cats == NULL) { return chooseWord(category, NULL); } //step 1
  int index = isValidInt(category);
  if (index > 0) { //valid integer
    const char * word = chooseProvious(index, usedWord);
    return word;
  }
  checkAvailability(category, cats); //check if there's still words avaliable
  const char * new_word; 
  do { //if still exist then loop untill we get it
    new_word = chooseWord(category, cats); //chooseWord handles invalid category
  } while (*new_word == '\0');
  return new_word;
}

void addUsedWord(const char * newWord, category_t * usedWord) {
  char ** temp = usedWord->words; //avoid extra long line of code
  temp = tryRealloc(temp, (usedWord->n_words + 1) * sizeof(*temp));
  temp[usedWord->n_words] = my_strdup(newWord);
  usedWord->words = temp;
  usedWord->n_words++;
}

char * replace(char * str, catarray_t * cats, category_t * usedWord, int signal) {
  char c = '_';
  char ** parts = extractor(str, c, 3); //{left part, blank name, right part}
  if (parts == NULL) { return str; } //base case
  if (*parts[1] == '\0') { giveErr("Empty blank detected!", str); }
  const char * word = chooseBetterWord(parts[1], cats, usedWord);
  if (usedWord != NULL) { addUsedWord(word, usedWord); }
  char * new_str = constructor(parts, word);
  if (signal > 0) { rmWord(word, parts[1], cats); }
  free(str); //never use the old version again
  freeParts(parts, 3);
  return replace(new_str, cats, usedWord, signal); //tail recursion 
}

void replaceAll(category_t * lines,
		catarray_t * cats,
		category_t * usedWord,
		int signal) {
  for (size_t i = 0; i < lines->n_words; i++) {
    lines->words[i] = replace(lines->words[i], cats, usedWord, signal);
  }
}

char ** readAll_helper(FILE * f, size_t * count_p) {
  size_t sz = 0;
  char * curr = NULL;
  char ** ans = NULL;
  *count_p = 0; //ensure *num starts from 0
  while (getline(&curr, &sz, f) >= 0) {
    ans = realloc(ans, (*count_p + 1)*sizeof(*ans));
    ans[*count_p] = curr;
    curr = NULL;
    (*count_p)++;
  }
  free(curr);
  return ans;
}

void readAll(const char * filename, category_t * lines) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    giveErr("Unable to open the file!", filename);
  }
  lines->name = NULL; //we will never use this field in replacement
  lines->words = readAll_helper(f, &(lines->n_words));
  if (fclose(f) != 0) {
    giveErr("Unable to close the file!", filename);
  }
  if (lines->words == NULL) {
    giveErr("Unable to read anything from the file!", filename);
  }
}

void rmNewline(char * line) {
  char * p = strchr(line, '\n'); //'\n' is the last char if it exist
  if (p != NULL) { *p = '\0';} 
}

char ** writeOne_getParts(char * line) {
  rmNewline(line);
  char ** parts = extractor(line, ':', 2); //extract with delimiter ':'
  if (parts == NULL) { 
    giveErr("Missing the delimiter ':'!", line); 
  }
  if (*parts[0] == '\0' || *parts[1] == '\0') {
    giveErr("Missing category name or replacement word!", line);
  }
  return parts; //consists of {category name, replacement word}
}

void writeOne_addWord(category_t * p, char * word) {
  p->words = tryRealloc(p->words, (p->n_words + 1) * sizeof(*p->words));
  p->words[p->n_words] = word;
  p->n_words++;
}

void writeOne_addCat(catarray_t * cats, char ** parts) {
  cats->arr = tryRealloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
  category_t * newCat = &cats->arr[cats->n];
  newCat->name = parts[0]; //store the name
  newCat->words = malloc(sizeof(*newCat->words));
  newCat->words[0] = parts[1]; //store the word
  newCat->n_words = 1;
  cats->n++;
}

void writeOne(catarray_t * cats, char * line) {
  char ** parts = writeOne_getParts(line);
  category_t * p = NULL; //use p to loop over arr
  for (p = cats->arr; p - cats->arr < cats->n; p++) {
    if (strcmp(parts[0], p->name) == 0) { 
      writeOne_addWord(p, parts[1]);
      free(parts[0]);
      free(parts);
      return;
    }
  }//if we cannot find a match, create a new category
  writeOne_addCat(cats, parts);
  free(parts);
}

void writeAll(catarray_t * cats, category_t * lines) {
  for (size_t i = 0; i < lines->n_words; i++) {
    writeOne(cats, lines->words[i]);
  }
  freeCat(lines, 1);
}

void printCat(category_t * cat) {
  for (size_t i = 0; i < cat->n_words; i++) {
    fprintf(stdout, "%s", cat->words[i]);
  }
}

void printCats(catarray_t * cats) {
  category_t * p = NULL; //use p to loop over arr
  for (size_t i = 0; i < cats->n; i++) {
    p = &cats->arr[i];
    fprintf(stdout, "%s:\n", p->name);
    for (int j = 0; j < p->n_words; j++) {
      fprintf(stdout, "  %s\n", p->words[j]);
    }
  }
}

void freeParts(char ** parts, const int n) {
  for (int i = 0; i < n; i++) { 
    free(parts[i]); 
  }
  free(parts);
}

void freeCat(category_t * cat, int freeItself) {
  for (size_t i = 0; i < cat->n_words; i++) {
    free(cat->words[i]);
  }
  free(cat->words);
  free(cat->name);
  if (freeItself) { free(cat); } //as an option
}

void freeCats(catarray_t * cats) {
  category_t * p = NULL; //use p to loop over arr
  for (size_t i = 0; i < cats->n; i++) {
    p = &cats->arr[i];
    freeCat(p, 0); 
  }
  free(cats->arr);
  free(cats);
}
