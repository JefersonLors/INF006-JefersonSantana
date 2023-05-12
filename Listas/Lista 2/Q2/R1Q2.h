#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q2_h
#define R1Q2_h

#define MAX_SIZE_LINE 1000
#define KEY_WORD " "

enum operation
{
  NONE = 0,
  PUSH,
  POP,
};

typedef struct string
{
  char *content;
  struct string *next;
  struct string *prev;
} str;

typedef struct stringBase
{
  struct string *content;
  struct stringBase *next;
} strBase;

typedef struct logBase
{
  char *content;
  struct logBase *next;
} logBase;

const char R1Q2_file_in_path[] = "L1Q2.in";
const char R1Q2_file_out_path[] = "L1Q2.out";

str *get_lines_from_file();
str *break_lines_in_str_list(str *line);
strBase *create_str_stack_matrix(str *firstLine);
logBase *create_log_line_matrix(strBase *nameList);

bool isEmpty(char *string);
char *create_log_line(str *nameList);

void write_result_in_file(logBase *firstLog);
void stack_name_insert_sorted(str *currItem, char *log);
void free_str_memory_allocated(str **firstStr);
void free_logLine_memory_allocated(logBase **firstLog);

#endif