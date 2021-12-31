#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getMatrix(char matrix[10][10], FILE * inputFile) {
  char c;
  char * p;
  for (int i = 0; i < 10; i++) {
    p = fgets(matrix[i], 11, inputFile);
    if (p == NULL) {
      fprintf(stderr, "Unable to read row %d!\n!", i+1);
      exit(EXIT_FAILURE);
    }
    if (strchr(matrix[i], '\n') != NULL) {
      fprintf(stderr, "Row %d is too short!\n", i+1);
      exit(EXIT_FAILURE);
    }
    if ((c = fgetc(inputFile)) != '\n') {
      printf("%c\n", c);
      fprintf(stderr, "Row %d is too long!\n", i+1);
      exit(EXIT_FAILURE);
    }
  }
  if ((c = fgetc(inputFile)) != EOF) {
    fprintf(stderr, "Too many rows!\n");
    exit(EXIT_FAILURE);
  }
}


void rotate(char matrix[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", matrix[9-j][i]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFile\n");
    exit(EXIT_FAILURE);
  }
  char matrix[10][10];
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Unable to open file!");
      exit(EXIT_FAILURE);
  }
  getMatrix(matrix, f);
  rotate(matrix);
  return EXIT_SUCCESS;
}
  
