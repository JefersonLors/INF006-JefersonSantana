#include <stdio.h>
#include <stdlib.h>

#ifndef R2Q2_H
#define R2Q2_H

#define MAX_SIZE_LINE 5000

typedef struct string
{
  char *content;
  struct string *next;
} str;

typedef struct numbers
{
  int keyQTY;
  int *keys;
  struct numbers *next;
} numbers;

const char R2Q2_file_in_path[] = "L2Q2.in";
const char R2Q2_file_out_path[] = "L2Q2.out";

str *get_lines_from_file();
str *new_str();
str *break_line_in_str_list(char *line);
numbers *new_numbers();
numbers *create_numbers_list(str *firstStr);

void delete_str_list(str **firstStr);
void show_lines_content(str *firstStr);
void show_lines_like_numbers_list(numbers *firstNumbers);

int get_size_str_linked_list(str *start);
int *new_int_vector(int size);

char *new_char_vector(int size);
#endif