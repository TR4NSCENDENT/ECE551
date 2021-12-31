#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

//This function change the first '\n' in str to '\0'
void rm_newline(char * str);

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
  }
  counts_t * ans = createCounts();
  char * name = NULL;
  size_t sz = 0;
  while (getline(&name, &sz, f) >= 0) {
    rm_newline(name);
    addCount(ans, lookupValue(kvPairs, name));
  }
  free(name);
  fclose(f);
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "Usage: main kvFile listFile listFile2");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    fprintf(stderr, "Unable to open %s\n", argv[1]);
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      fprintf(stderr, "Unable to open %s\n", argv[i]);
      return EXIT_FAILURE;
    }
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Unable to close the file %s\n", outName);
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
