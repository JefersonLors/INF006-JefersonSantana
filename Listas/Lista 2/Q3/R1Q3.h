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

const char R1Q3_file_in_path[] = "L1Q3.in";
const char R1Q3_file_out_path[] = "L1Q3.out";

str *get_lines_from_file();
str *break_lines_in_str_list(str *line);

#endif