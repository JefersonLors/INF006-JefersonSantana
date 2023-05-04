#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q1_h
#define R1Q1_h

#define MAX_SIZE_LINE 255

typedef struct string{
  char *line;
  struct string *next;
}str;

typedef struct naturals{
  int *values;
  int sum;
  struct naturals *next; 
}nat;

typedef struct base{
  struct naturals *list;
  struct base *next;
}base;

const char R1Q1_file_in_path[] = "L1Q1.in"; 
const char R1Q1_file_out_path[] = "L1Q1.out"; 

str *get_lines_from_file();


#endif