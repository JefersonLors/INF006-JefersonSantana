#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Q2InGenerator_h
#define Q2InGenerator_h

#define NAME_LIST_SIZE 52
#define _MAX_SIZE_LINE 800
#define MAX_QTY_NAME 10
#define MAX_QTY_LINE 9000
#define MIN_QTY_LINE 6000

typedef struct _string
{
  char *line;
  struct _string *next;
} _str;

extern const char *R1Q2_file_in;
extern const char *names[NAME_LIST_SIZE];

_str *create_name_list_to_in();

void L1Q2_in_generator();
char *create_line(int qty);
bool write_in_file(_str *firstLine);
void delete_line_list(_str **firstLine);
int get_random_int( int min, int max );

#endif