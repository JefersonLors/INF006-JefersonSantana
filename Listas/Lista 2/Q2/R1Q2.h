#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q2_h
#define R1Q2_h

#define MAX_SIZE_LINE 255
#define KEY_WORD " "

enum operation
{
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

typedef struct nameBase
{
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

const char R1Q2_file_in_path[] = "L1Q2.in";
const char R1Q2_file_out_path[] = "L1Q2.out";

str *get_lines_from_file();
str *break_lines_in_str_list(str *line);
strBase *create_str_matrix(str *firstLine);
nameBase *create_name_matrix(strBase *firstStrBase);
name *create_name_list(str *firstStr);
name *create_name( char *stringName);

bool isEmpty(char *string);
void free_str_memory_allocated(str **first);
void show_all_name_list( nameBase *firstNameBase);

#endif