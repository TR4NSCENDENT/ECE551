#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char * suffix = ".counts";
  int len1 = strlen(inputName);
  int len2 = strlen(suffix); //allow change of suffix
  char * ans = malloc((len1 + len2) * sizeof(*ans) + 1);
  strcpy(ans, inputName);
  strcat(ans, suffix);
  return ans;
}
