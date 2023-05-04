#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Q1InGenerator_h
#define Q1InGenerator_h

#define _MAX_SIZE_LINE 255
#define MAX_QTY_LIST 10
#define MAX_QTY_LINE 1000
#define MIN_QTY_LINE 100

typedef struct _string{
  char *line;
  struct _string *next;
}_str;

extern const char *R1Q1_file_in; 

void L1Q1_in_generator();
_str *create_line_list();
char *create_line(int qty);
char *generate_naturals_number_list();
bool write_in_file(_str *start);
void delete_line_list(_str **start);

#endif