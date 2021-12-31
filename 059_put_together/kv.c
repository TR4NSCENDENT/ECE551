#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

//This function handles erro for realloc in readKVs
void err_handling(kvarray_t * array) {
  perror("realloc in readKVs");
  fprintf(stderr, "Failed to create more space\n");
  if (array->kvpairs != NULL) {
    free(array->kvpairs);
  }
  free(array);
  exit(EXIT_FAILURE);
}

//This function divide the line to key and value and write
//them into the last block of the kvpair array
void write_kvpair(kvarray_t * array, char * input) {
  kvpair_t * pair_p = malloc(sizeof(kvpair_t));
  array->kvpairs[array->num_kvpairs] = pair_p;
  array->num_kvpairs++;
  char * temp_str = strdup(input); //a copy of input
  char * p = strchr(temp_str, '=');
  *p = '\0'; //break the input to two strings
  pair_p->key = strdup(temp_str);
  pair_p->value = strdup(p + 1);
  free(temp_str);
}

//This function change the first '\n' in str to '\0'
void rm_newline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

//This function write an array of kvpairs
void write_kvarray(kvarray_t * ans, FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  kvpair_t ** test_p = NULL;
  while ((getline(&line, &sz, f)) >= 0) {
    test_p = realloc(ans->kvpairs,
		     (ans->num_kvpairs + 1) * sizeof(*ans->kvpairs));
    if (test_p == NULL) {
      err_handling(ans);
    }
    ans->kvpairs = test_p;
    rm_newline(line);
    write_kvpair(ans, line);
    free(line);
    line = NULL;
  }
  free(line);
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->kvpairs = NULL; //initialize the ans
  ans->num_kvpairs = 0; //with base case
  write_kvarray(ans, f);
  if (fclose(f) != 0) {
    fprintf(stderr, "unable to close %s\n", fname);
    exit(EXIT_FAILURE);
  }
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  kvpair_t * p = NULL;
  for (int i = 0; i < pairs->num_kvpairs; i++) {
    p = pairs->kvpairs[i];
    free(p->key);
    free(p->value);
    free(p);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  kvpair_t * p;
  for (int i = 0; i < pairs->num_kvpairs; i++) {
    p = pairs->kvpairs[i];
    fprintf(stdout, "key = '%s' value = '%s'\n", p->key, p->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  kvpair_t * p;
  int res;
  for (int i = 0; i < pairs->num_kvpairs; i++) {
    p = pairs->kvpairs[i];
    res = strcmp(p->key, key);
    if (res == 0) {
      return p->value;
    }
  }
  return NULL;
}
