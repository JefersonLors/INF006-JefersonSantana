#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Q3InGenerator_h
#define Q3InGenerator_h

#define _MAX_SIZE_LINE 1000
#define MAX_QTY_NUMBERS 100
#define MAX_QTY_LINE 60000
#define MIN_QTY_LINE 10000
#define ADD "add"
#define REMOVE "remove"

typedef struct _string{
  char *line;
  struct _string *next;
}_str;

extern const char *R2Q3_file_in; 

void L2Q3_in_generator();
_str *create_line_list();
char *add_or_remov_select();
char *generate_string_interger_list();
bool toNegative();
bool write_in_file(_str *start);
void delete_line_list(_str **start);

#endif