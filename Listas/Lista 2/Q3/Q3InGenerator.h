#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Q3InGenerator_h
#define Q3InGenerator_h

#define INT_LIST_MAX_SIZE 10
#define FLOAT_LIST_MAX_SIZE 10
#define MAX_INT 50
#define MAX_QTY_LINE 60000
#define MIN_QTY_LINE 20000

typedef struct values
{
  int intQTY;
  int *intList;
  int floatQTY;
  float *floatList;
  struct values *next;
} values;

typedef struct number
{
  int baseInt;
  int floatQTY;
  float *floatings;
} number;

typedef struct listBase
{
  int numQTY;
  number **numbersVector;
  struct listBase *next;
} listBase;

extern const char *R1Q3_file_in;

listBase *create_number_base_list();
number *create_number();
values *make_list_of_values(listBase *firstBase);

int get_random_qty(int min, int max);
int generate_random_int();

void L1Q3_in_generator();
void generate_random_float_list(int baseInterger, int sizeList, float **emptyList);
void random_float_vector(float *vector, int vectorSize);
void merge_floats(float *floatRandomList, int size, listBase *listBase);
void show_list_base_content(listBase *firstBase);
void show_values_content(values *firstValues);
void delete_list_Base(listBase **firstBase);
void delete_list_value(values **firstValues);
void write_in_file(values *firstStringList);

#endif