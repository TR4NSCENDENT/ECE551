#include "pandemic.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//This function handles the operations when detecting error cases
void err_msg(char * message, char * location);


/* ------------------ Step 1 ------------------ */


//This helper function extracts the country's name and its population
//from the given line, and returns a country_t.
country_t parseHelper(char * line);


country_t parseLine(char * line) {
  //error handling for NULL input or empty line_c
  if (line == NULL || line[0] == '\n') {
    err_msg("Null/empty input detected!", line);
  }
  country_t country = parseHelper(line);
  //make negative or zero population invalid
  if (country.population <= 0) {
    err_msg("Positive population required!", line);
  }
  return country;
}


/* ------------------ Step 2 ------------------ */


//This function calculate the sum of first N terms of data
unsigned getNsum(unsigned * data, size_t N);


void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //error handling for case data less than 7
  if (n_days < 7) {
    err_msg("Case data is not enough (less than 7)!", "calcRunningAvg");
  }
  unsigned sum = getNsum(data, 6); //setup the base case (with first 6 days)
  for (size_t i = 0; i < n_days - 6; i++) {
    sum += data[i + 6]; //make it 7 days by adding the 7th day
    avg[i] = sum / 7.; 
    sum -= data[i]; //remove current day before move to next day
  }
}


/* ------------------ Step 3 ------------------ */


void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //error handling for empty data set
  if (data == NULL) {
    err_msg("Empty data detected!", "calcCumulative\n");
  }
  uint64_t case_cum = 0;
  double per_hdth_people = 100000. / pop; //set up the multiplication factor first
  for (size_t i = 0; i < n_days; i++) {
    case_cum += data[i];
    cum[i] = case_cum * per_hdth_people; //this way can maximize the precision
  }
}


/* ------------------ Step 4 ------------------ */


void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days)
{
  //error handling for empty input
  if (countries == NULL || data == NULL) {
    err_msg("Empty country/data input!", "printCountryWithMax\n");
  }
  country_t * country_ptr = countries;
  unsigned * case_ptr = data[0];
  //loop over the 2D array to find the maximum
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > *case_ptr) {
	case_ptr = data[i] + j;
	country_ptr = countries + i;
      }
    }
  }
  //print the required information
  printf("%s has the most daily cases with %d\n",
	 country_ptr -> name,
	 *case_ptr);
}



/* ------------- Helper Functions ------------- */


void err_msg(char * message, char * location) {
  if (location != NULL) {
    //print cooresponding location if applicable
    fprintf(stderr, "Error in: %s", location);
  }
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}


country_t parseHelper(char * line) {
  
  //make a copy of the original string
  char line_c[strlen(line)+1];
  strcpy(line_c, line);
  char * p = strchr(line_c, ','); //point to the first comma
  char * p2 = strrchr(line_c, ',');

  //error handling for missing country name or wrong number of comma
  if (p == line_c || p == NULL || p != p2) {
    err_msg("Wrong input format detected!", line);  
  }

  *p = '\0'; //break the line_c into two string literals
  p++; //move p to the decimal part
  country_t ans;
  char ** endp = &p;
  strcpy(ans.name, line_c);
  ans.population = strtol(p, endp, 10); //0 if population is missing

  //error handling for invalid population format
  if (**endp != '\n' && **endp != '\0') {
    //here we allow the line to end without '\n'
    err_msg("Invalid population format", line);
  }

  return ans;
}


unsigned getNsum(unsigned * data, size_t N) {
  if (N == 0) return 0; //base case
  return data[0] + getNsum(data + 1, N - 1);
} 
