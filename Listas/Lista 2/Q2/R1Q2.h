#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q2_h
#define R1Q2_h

#define MAX_SIZE_LINE 255
#define KEY_WORD " "

enum operation{
  NONE = 0,
  PUSH,
  POP,
};

typedef struct name
{
  char *content;
  unsigned short operation;
  struct name *next;
} name;

typedef struct nameBase{
  struct name *list;
  struct nameBase *next; 
} nameBase;

typedef struct string
{
  char *line;
  struct string *next;
} str;

typedef struct stringBase
{
  struct string *content;
  struct stringBase *next;
} strBase;

str *get_lines_from_file();
str *break_lines_in_str_list(str *line);
strBase *create_str_matrix(str *firstLine);
bool isEmpty(char *string);

const char R1Q2_file_in_path[] = "L1Q2.in";
const char R1Q2_file_out_path[] = "L1Q2.out";

#endif