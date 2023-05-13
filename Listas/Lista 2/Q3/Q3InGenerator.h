#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef Q3InGenerator_h
#define Q3InGenerator_h

#define INT_LIST_MAX_SIZE 10
#define FLOAT_LIST_MAX_SIZE 10
#define MAX_INT 50
#define MAX_QTY_LINE 60000

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

void L1Q3_in_generator();
listBase *create_number_base_list();

number *create_number();
int get_random_qty(int max);
int generate_random_int();
void generate_random_float_list(int baseInterger, int sizeList, float **emptyList);

bool write_in_file(listBase *firstBase);
void delete_line_list(listBase **firstBase);
void show_all_content( listBase *firstBase );
#endif