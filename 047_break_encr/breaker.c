#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//find the sum of an array
int sum(int * array, int n) {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += array[i];
  }
  return ans;
}

//modified version from 035_array_max
int arrayMax(int * array, int n) {
  int *p = array;
  for (int i = 1; i < n; i++) {
    if (array[i] > *p) p = array + i;
  }
  return p - array; //return the index 
}

//find the encryption key
int breaker(FILE * file) {
  int i;
  int atoz[27] = {0};
  while ((i = fgetc(file)) != EOF) {
    if (isalpha(i)) {
      i = tolower(i) - 'a';
      atoz[i]++;
    }
  }
  if (sum(atoz, 27) == 0) {
    printf("No letter detected!\n");
    exit(EXIT_FAILURE);
  }
  //find the most frequent letter
  char com_letter = arrayMax(atoz, 27) + 'a';
  int key = (com_letter - 'e' + 26) % 26; //get diff
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Incorrect input!\n");
    return EXIT_FAILURE;
  }
  FILE * file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr,"Unable to open the input file\n");
    return EXIT_FAILURE;
  }
  int c;
  if ((c = fgetc(file)) == EOF) {
    fprintf(stderr,"Empty input file detected!\n");
    return EXIT_FAILURE;
  }
  int key = breaker(file);
  printf("%d\n", key);
  if (fclose(file) != 0) {
    fprintf(stderr,"Unable to close the input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
