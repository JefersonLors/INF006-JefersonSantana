#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Q3InGenerator.h"

const char *R1Q3_file_in = "L1Q3.in";

int main()
{
  srand(time(NULL));
  L1Q3_in_generator();

  puts("end run");
  return EXIT_SUCCESS;
}
bool write_in_file(listBase *firstBase)
{
  FILE *fileOutPtr = fopen(R1Q3_file_in, "w");

  if( fileOutPtr ){
    listBase *curr = firstBase;
    // int i = 0;
    // int k = 0;
    
    // while (curr)
    // {
    //   k = 0;
    //   printf("line[%d]\n", i);
    //   number **vector = curr->numbersVector;

    //   while (k < curr->numQTY)
    //   {
    //     number *subVector = curr->numbersVector[k];
    //     int j = 0;
    //     printf("\tnumber[%d] -> ", subVector->baseInt);
    //     while (j < subVector->floatQTY)
    //     {
    //       printf("%.2f, ", subVector->floatings[j]);
    //       j++;
    //     }
    //     k++;
    //     printf("\n");
    //   }
    //   printf("\n");
    //   i++;
    //   curr = curr->next;
    // }
  }else{
    puts("ops! file issues :[");
  }
}
void L1Q3_in_generator()
{
  listBase *first = create_number_base_list();
  write_in_file(first);
  delete_line_list(&first);
  // show_all_content(first);
}
listBase *create_number_base_list()
{
  listBase *first = NULL;
  listBase *curr = NULL;
  listBase *new = NULL;
  listBase *last = NULL;

  int qtyLine = get_random_qty(MAX_QTY_LINE);

  new = (listBase *)malloc(sizeof(listBase));
  new->numQTY = get_random_qty(INT_LIST_MAX_SIZE);
  new->numbersVector = (number **)malloc(sizeof(number *) * new->numQTY);
  new->next = NULL;

  int i = 0;
  while (i < new->numQTY)
  {
    new->numbersVector[i] = create_number();
    i++;
  }

  first = new;
  last = new;

  int j = 1;

  while (j <= qtyLine)
  {
    new = (listBase *)malloc(sizeof(listBase));
    new->numQTY = get_random_qty(INT_LIST_MAX_SIZE);
    new->numbersVector = (number **)malloc(sizeof(number *) * new->numQTY);
    new->next = NULL;

    int i = 0;
    while (i < new->numQTY)
    {
      new->numbersVector[i] = create_number();
      i++;
    }

    curr = last;
    curr->next = new;
    last = new;
    j++;
  }
  return first;
}
number *create_number()
{
  number *new = (number *)malloc(sizeof(number));
  new->baseInt = generate_random_int();
  new->floatQTY = get_random_qty(FLOAT_LIST_MAX_SIZE);
  new->floatings = (float *)malloc(sizeof(float) * new->floatQTY);
  generate_random_float_list(new->baseInt, new->floatQTY, &new->floatings);

  return new;
}
void generate_random_float_list(int baseInterger, int sizeList, float **list)
{
  int i = 0;
  float num = 0;
  float prev = 0;
  while (i < sizeList)
  {
    do
    {
      num = (float)rand() / (float)RAND_MAX;
      num *= baseInterger + 1 - baseInterger;
      num += baseInterger;
    } while (num == prev);

    (*list)[i] = num;
    prev = num;
    i++;
  }
}
int generate_random_int()
{
  return 1 + rand() % (MAX_INT + 1);
}
int get_random_qty(int max)
{
  return 1 + rand() % (max + 1);
}
void show_all_content(listBase *first)
{
  int i = 0;
  int k = 0;

  while (first)
  {
    k = 0;
    printf("line[%d]\n", i);
    number **vector = first->numbersVector;

    while (k < first->numQTY)
    {
      number *subVector = first->numbersVector[k];
      int j = 0;
      printf("\tnumber[%d] -> ", subVector->baseInt);
      while (j < subVector->floatQTY)
      {
        printf("%.2f, ", subVector->floatings[j]);
        j++;
      }
      k++;
      printf("\n");
    }
    printf("\n");
    i++;
    first = first->next;
  }
}
void delete_line_list(listBase **firstBase)
{
  listBase *curr = *firstBase;
  listBase *prev = NULL;

  int i = 0;
  int k = 0;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(*prev->numbersVector);
    free(prev);
    prev = NULL;
  }
  *firstBase = NULL;
}