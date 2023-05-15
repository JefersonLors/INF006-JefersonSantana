#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q3_h
#define R1Q3_h

#define MAX_SIZE_LINE 1000
#define KEY_WORD1 "LE"
#define KEY_WORD2 "LI"

typedef struct values
{
  float *content;
  struct values *next;
} values;

typedef struct key
{
  int content;
  values *list;
  struct key *prev;
  struct key *next;
} key;

typedef struct numbers
{
  int keyQTY;
  int *keys;
  int valuesQTY;
  float *values;
  struct numbers *next;
} numbers;

typedef struct string
{
  char *content;
  struct string *next;
} str;

typedef struct strValues
{
  char *intStrList;
  char *floatStrList;
  struct strValues *next;
} strV;

const char R1Q3_file_in_path[] = "L1Q3.in";
const char R1Q3_file_out_path[] = "L1Q3.out";

str *get_lines_from_file();
str *break_line_in_str_list(char *line);
strV *create_strV_list(str *firstLine);
strV *break_in_two_lists(str *line);
numbers *create_numbers_list(strV *firstsStrValues);

void remove_alphabetic_non_numeric_characters_from_string(char *string);
void delete_str_list(str **firstStr);
void delete_numbers_list(numbers **firstNumbers);
void delete_strV_list(strV **firstStrV);
int get_size_str_linked_list(str *start);
#endif