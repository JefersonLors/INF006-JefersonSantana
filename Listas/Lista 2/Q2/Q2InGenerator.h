#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Q2InGenerator_h
#define Q2InGenerator_h

#define NAME_LIST_SIZE 52
#define _MAX_SIZE_LINE 255
#define MAX_QTY_NAME 30
#define MAX_QTY_LINE 60000
#define MIN_QTY_LINE 10000

typedef struct _string
{
  char *line;
  struct _string *next;
} _str;

extern const char *R1Q2_file_in;
extern const char *names[NAME_LIST_SIZE];

void L1Q2_in_generator();
_str *create_name_list();
char *create_line(int qty);
bool write_in_file(_str *start);
void delete_line_list(_str **start);

#endif