#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Q2InGenerator_h
#define Q2InGenerator_h

#define _MAX_SIZE_LINE 800
#define MAX_QTY_NUMBERS 100
#define MAX_QTY_LINE 60000
#define MIN_QTY_LINE 10000

typedef struct _string{
  char *line;
  struct _string *next;
}_str;

extern const char *R2Q2_file_in; 

void L2Q2_in_generator();
_str *create_line_list();
char *generate_string_interger_list();
bool toNegative();
bool write_in_file(_str *start);
void delete_line_list(_str **start);

#endif