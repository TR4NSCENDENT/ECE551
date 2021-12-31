#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"


//any functions you want your main to use

//error handling function
void giveErr(const char * err_msg, const char * line);

//similar to strsep, but this function returns NULL and keeps
//str the same when c is not found in str
char * my_strsep(char ** str, const char c);

//similar to strdup, but will return NULL if str is NULL
char * my_strdup(const char * str);

//a helper function of the extractor that parse the str into n
//pieces, based on delimiter c
char ** extractor_helper(char * const str, const char c, const int n);

//extract the name of blank and its left and right part from 
//the given line, and store them in a new allocated memory
char ** extractor(const char * const line, const char c, const int n);

//put the parts (left part, the chosen word, and right part)
//together in a new allocated memory
char * constructor(char ** parts, const char * word);

//check if a category name is a valid integer using strtol
int isValidInt(char * category);

//select the recent used word based on the index given,
//i.e. 1 is the most recent one
const char * chooseProvious(int index, category_t * usedWord);

//remove a word of a specific category form the category array by first
//freeing its space, and then allocated an empty space for it.
void rmWord(const char * new_word, char * category, catarray_t * cats);

//ensure that we have avaliable words, otherwise will be an infinite loop
void checkAvailability(char * category, catarray_t * cats);

//generall function that manage how to choose a suitable word in different steps
const char * chooseBetterWord(char * category, catarray_t * cats, category_t * usedWord);

//add an used word to the usedWord list
void addUsedWord(const char * newWord, category_t * usedWord);

//recursive function that replace all blanks in one line with the
//corresponding words. It will free the memory that we will never
//use again. If there is no blanks in the given line then it does nothing. 
char * replace(char * str, catarray_t * cats, category_t * usedWord, int signal);

//run replace() on all the lines we read
void replaceAll(category_t * lines, catarray_t * cats, category_t * usedWord, int signal);

//read all lines from the file f, and organize them as a char **
char ** readAll_helper(FILE * f, size_t * count_p);

//error handling for open and close the given file use category
//type to store lines we read
void readAll(const char * filename, category_t * cat);

//simple function that removes the '\n' at the end
void rmNewline(char * line);

//one helper function for writeOne that parses the line
char ** writeOne_getParts(char * line);

//another helper function for writeOne that add a word
//to its corresponding category
void writeOne_addWord(category_t * p, char * word);

//the last helper function that is responsible for adding
//a new chategory when there's no existing one to use
void writeOne_addCat(catarray_t * cats, char ** parts);

//general function that write one line of category:word into the
//well organized catarray_t stracture
void writeOne(catarray_t * cats, char * line);

//loop over writeOne on all the lines we read from the file
void writeAll(catarray_t * cats, category_t * lines);

//print out a cat to stdout, used for step1, 3 and 4
void printCat(category_t * cat);

//print out a cats to stdout, used for step2
void printCats(catarray_t * cats);

//frees all the allocated space in a char **
void freeParts(char ** parts, const int n);

//free all the allocated memory for a category_t
void freeCat(category_t * cat, int freeItself);

//free all the allocated memory for a catarray_t
void freeCats(catarray_t * cats);

#endif
