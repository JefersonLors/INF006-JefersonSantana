#include <stdio.h>
#include <stdlib.h>

#ifndef R2Q3_H
#define R2Q3_H

#define MAX_SIZE_LINE 10000
#define EMPTY -3023348

typedef struct string
{
  char *content;
  struct string *next;
} str;

typedef struct numbers
{
  int keyQTY;
  char *ops;
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
  struct node *root;
  struct lineResult *next;
} lineResult;

const char R2Q3_file_in_path[] = "L2Q3.in";
const char R2Q3_file_out_path[] = "L2Q3.out";

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

void insert_node(node **root, node *newNode);
void delete_node(node **root, node *toDelete);
node *search_node(node *root, int key);
node *sucesssor_node(node* node);
node *minimum(node *_node);

void delete_numbers_list(numbers **firstNumbers);
void delete_str_list(str **firstStr);
void delete_line_result_list(lineResult **firstLineResult);

void create_string_result_in_order(node *root, char *string);
void write_result_in_file(lineResult *firstLineResult);

void show_in_order(node *root);
void insert_node(node **root, node *newnode);
void show_lines_content(str *firstStr);
void show_lines_like_numbers_list(numbers *firstNumbers);

void calculate_height(node *subRoot);

int get_size_str_linked_list(str *start);
void get_operations_from_string(str *start, char *list, int size);
void get_values_from_string(str *start, int *list, int size);

int *new_int_vector(int size);

char *new_char_vector(int size);
#endif