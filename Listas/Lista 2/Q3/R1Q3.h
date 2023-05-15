#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q3_h
#define R1Q3_h

#define MAX_SIZE_LINE 1000
#define KEY_WORD1 "LE"
#define KEY_WORD2 "LI"

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
void remove_alfabetic_non_numeric_characters_from_string( char *string );
strV *create_strV_list(str *firstLine);
strV *break_in_two_lists(str *line);


#endif