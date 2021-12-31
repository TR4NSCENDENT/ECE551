#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  size_t s = 0;
  ssize_t len = 0;
  if (argc == 1) {
    char ** lines = NULL;
    char * curr = NULL;
    int k = 0;
    while ((len = getline(&curr, &s, stdin)) >= 0) {
      lines = realloc(lines, (k+1)*sizeof(*lines));
      lines[k] = curr;
      curr = NULL;
      k++;
    }
    free(curr);
    sortData(lines, k);
    for (int j = 0; j < k; j++) {
      fprintf(stdout, "%s", lines[j]);
      free(lines[j]);
    }
    free(lines);
    /*
    char * line[1];
    line[0] = NULL;
    len = getline(&line[0], &s, stdin);
    if (len == -1) {
      fprintf(stderr, "Unable to read the line!\n");
      return EXIT_FAILURE;
    }
    sortData(line, 1);
    fprintf(stdout, "%s", line[0]);
    free(line[0]);
    */
    return EXIT_SUCCESS;
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
	fprintf(stderr, "Unable to open the file!\n");
	return EXIT_FAILURE;
      }
      char ** lines = NULL;
      char * curr = NULL;
      int k = 0;
      while ((len = getline(&curr, &s, f)) >= 0) {
	lines = realloc(lines, (k+1)*sizeof(*lines));
	lines[k] = curr;
	curr = NULL;
	k++;
      }
      free(curr);
      sortData(lines, k);
      for (int j = 0; j < k; j++) {
	fprintf(stdout, "%s", lines[j]);
	free(lines[j]);
      }
      free(lines);
      if (fclose(f) != 0) {
	fprintf(stderr, "Unable to close the file!\n");
	return EXIT_FAILURE;
      }
    }
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
