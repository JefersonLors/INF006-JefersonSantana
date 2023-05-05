#include <stdlib.h>
#include <stdio.h>

#ifndef R1Q1_h
#define R1Q1_h

#define MAX_SIZE_LINE 255
#define KEY_WORD "start"
#define END_VECTOR -100000

typedef struct string
{
  char *line;
  struct string *next;
} str;

typedef struct naturals
{
  int *values;
  int length;
  int sum;
  struct naturals *next;
} nat;

typedef struct naturalBase
{
  struct naturals *content;
  struct naturalBase *next;
} natBase;

typedef struct stringBase
{
  struct string *content;
  struct stringBase *next;
} strBase;

const char R1Q1_file_in_path[] = "L1Q1.in";
const char R1Q1_file_out_path[] = "L1Q1.out";

str *get_lines_from_file();
str *break_lines_in_str_list(str *line);
strBase *create_str_matrix(str *firstLine);
natBase *create_nat_matrix(strBase *firstStrBase);
nat *create_nat_list(str *stringList);

void insertion_sort_for_line(natBase *begining);
void insertio_sort_for_vector(int *vector);
int create_nat_int_list(char *stringVector, int **intVector);
int calculate_list_sum(int *natList);
void *free_str_memory_allocated(str **first);
void show_lines_as_strings(str *first);
bool isEmpty(char *string);

#endif