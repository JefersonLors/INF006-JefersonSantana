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

void ordernate_vector(natBase *start);
void ordenate_line(natBase *start);
void insertio_sort(int *vector, int size);
void swap_list_content(nat *listA, nat *listB);

void free_str_memory_allocated(str **first);
void free_nat_memory_allocated(nat **first);
void show_lines_as_strings(str *first);
void show_all_content(natBase *start);

int create_nat_int_list(char *stringVector, int **intVector);
int calculate_list_sum(int *natList, int size);

bool isEmpty(char *string);

void write_result_in_file( natBase *firstLine );
#endif