#include <stdio.h>
#include <stdlib.h>

#ifndef R2Q2_H
#define R2Q2_H

#define MAX_SIZE_LINE 5000
#define EMPTY -3023348

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

typedef struct node
{
  int key;
  int subTRLessSubTL;
  struct node *p;
  struct node *left;
  struct node *right;
} node;

typedef struct lineResult
{
  struct node *root;
  struct lineResult *next;
} lineResult;

const char R2Q2_file_in_path[] = "L2Q2.in";
const char R2Q2_file_out_path[] = "L2Q2.out";

str *get_lines_from_file();
str *new_str();
str *break_line_in_str_list(char *line);
numbers *new_numbers();
numbers *create_numbers_list(str *firstStr);

node *create_tree(numbers *values);
node *new_node(int value);

lineResult *create_line_result_list(numbers *values);
lineResult *create_line_result();
lineResult *new_line_result();

void delete_numbers_list(numbers **firstNumbers);
void delete_str_list(str **firstStr);
void delete_line_result_list(lineResult **firstLineResult);

void create_string_result_in_order(node *root, char *string);
void write_result_in_file(lineResult *firstLineResult);

void show_in_order(node *root);
void insert_node(node **root, node *newnode);
void show_lines_content(str *firstStr);
void show_lines_like_numbers_list(numbers *firstNumbers);
void calculate_subTR_less_subTL(node *root);

int calculate_tree_keys_sum(node *root);
int get_size_str_linked_list(str *start);
int *new_int_vector(int size);

char *new_char_vector(int size);
#endif