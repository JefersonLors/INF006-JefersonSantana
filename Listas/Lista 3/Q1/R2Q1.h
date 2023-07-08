#include <stdio.h>
#include <stdlib.h>

#ifndef R2Q1_H
#define R2Q1_H

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
  int height;
  struct node *p;
  struct node *left;
  struct node *right;
} node;

typedef struct lineResult
{
  int hQty;
  int *heights;
  int max;
  int maxH;
  int maxPred;
  struct lineResult *next;
} lineResult;

const char R2Q1_file_in_path[] = "L2Q1.in";
const char R2Q1_file_out_path[] = "L2Q1.out";

str *get_lines_from_file();
str *new_str();
str *break_line_in_str_list(char *line);

numbers *new_numbers();
numbers *create_numbers_list(str *firstStr);

node *create_tree(numbers *values, int *heights);
node *create_node(int value);
node *maximum(node *root);
node *predecessor(node *root);

lineResult *create_line_result_list(numbers *values);
lineResult *create_line_result();
lineResult *new_line_result();

void write_result_in_file(lineResult *firstLineResult);

void delete_line_result_list(lineResult **firstlineResult);
void delete_str_list(str **firstStr);
void delete_numbers_list(numbers **firstNumber);

int calculate_height(node *subRoot);

int insert_node(node **root, node *newnode);
void show_in_order(node *root);

void show_lines_content(str *firstStr);
void show_lines_like_numbers_list(numbers *firstNumbers);

int get_size_str_linked_list(str *start);
int *new_int_vector(int size);

char *new_char_vector(int size);
#endif