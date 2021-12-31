#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  c -> counts = NULL;
  c -> size = 0;
  c -> unknown_count = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //if unknown case
  if (name == NULL) {
    c->unknown_count++;
    return;
  }
  //try to find name from existing counts
  int res;
  one_count_t * p;
  for (int i = 0; i < c->size; i++) {
    p = c->counts[i];
    res = strcmp(p->str, name);
    if (res == 0) {
      p->n++;
      return;
    }
  }
  //if no existing count
  c->counts = realloc(c->counts, (c->size + 1) * sizeof(*c->counts));
  c->counts[c->size] = malloc(sizeof(*c->counts[0]));
  c->counts[c->size]->str = strdup(name);
  c->counts[c->size]->n = 1;
  c->size++;
}
void printCounts(counts_t * c, FILE * outFile) {
  one_count_t * p;
  for (int i = 0; i < c->size; i++) {
    p = c->counts[i];
    fprintf(outFile, "%s: %d\n", p->str, p->n);
  }
  if (c->unknown_count != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknown_count);
  }
}

void freeCounts(counts_t * c) {
  one_count_t * p;
  for (int i = 0; i < c->size; i++) {
    p = c->counts[i];
    free(p->str);
    free(p);
  }
  free(c->counts);
  free(c);
}
