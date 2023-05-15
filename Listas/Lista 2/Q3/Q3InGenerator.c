#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Q3InGenerator.h"

const char *R1Q3_file_in = "L1Q3.in";

void L1Q3_in_generator()
{
  srand(time(NULL));
  listBase *firstBase = create_number_base_list();
  values *firstValues = make_list_of_values( firstBase );

  delete_list_Base(&firstBase);
  write_in_file(firstValues);
  delete_list_value(&firstValues);
  // show_values_content( firstValues );
  // show_list_base_content(firstBase);
}
void write_in_file(values *firstValue)
{
  FILE *fileOutPtr = fopen(R1Q3_file_in, "w");

  if (fileOutPtr)
  {
    values *currValue = firstValue;
    while( currValue ){
      fprintf(fileOutPtr, "%s", "LE");
      int i = 0;

      while( i < currValue->intQTY ){
        fprintf(fileOutPtr, " %d", currValue->intList[i]);
        i++;
      }

      i = 0;
      fprintf(fileOutPtr, " %s", "LI");
      while( i < currValue->floatQTY ){
        fprintf(fileOutPtr, " %.2f", currValue->floatList[i]);
        i++;
      }
      fprintf(fileOutPtr, "\n");

      currValue = currValue->next;
    }
    fclose(fileOutPtr);
  }
  else
  {
    puts("ops! file issues :[");
  }
}
values *make_list_of_values( listBase *firstBase )
{
  listBase *curr = firstBase;

  values *firstValues = NULL;
  values *currValues = NULL;
  values *newValues = NULL;
  values *lastValues = NULL;

  int i = 0;
  int sizeFloatList = 0;

  int *intList = (int*)malloc(sizeof(int)*curr->numQTY);

  while (i < curr->numQTY)
  {
    number *numberList = curr->numbersVector[i];
    intList[i] = numberList->baseInt;
    sizeFloatList += numberList->floatQTY;
    i++;
  }

  float *floatList = (float *)malloc(sizeof(float) * sizeFloatList);
  merge_floats(floatList, sizeFloatList, curr);
  random_float_vector( floatList, sizeFloatList );

  newValues = (values*)malloc(sizeof(values));
  newValues->floatQTY = sizeFloatList;
  newValues->floatList = floatList;
  newValues->intQTY = curr->numQTY;
  newValues->intList = intList;
  newValues->next = NULL;

  firstValues = newValues;
  lastValues = newValues;

  while (curr)
  {
    int i = 0;
    int sizeFloatList = 0;

    int *intList = (int*)malloc(sizeof(int)*curr->numQTY);

    while (i < curr->numQTY)
    {
      number *numberList = curr->numbersVector[i];
      intList[i] = numberList->baseInt;
      sizeFloatList += numberList->floatQTY;
      i++;
    }

    float *floatList = (float *)malloc(sizeof(float) * sizeFloatList);
    merge_floats(floatList, sizeFloatList, curr);
    random_float_vector( floatList, sizeFloatList );
    newValues = (values*)malloc(sizeof(values));
    newValues->floatQTY = sizeFloatList;
    newValues->floatList = floatList;
    newValues->intQTY = curr->numQTY;
    newValues->intList = intList;
    newValues->next = NULL;

    currValues = lastValues;
    currValues->next = newValues;
    lastValues = newValues;

    curr = curr->next;
  }
  return firstValues;
}
void merge_floats(float *floatRandomList, int size, listBase *listBase)
{
  int k = 0;
  int i = 0;
 
  while (i < listBase->numQTY)
  {
    int j = 0;
    number *list = listBase->numbersVector[i];

    while (j < list->floatQTY)
    {
      floatRandomList[k] = list->floatings[j];
      k++;
      j++;
    }
    i++;
  }

}
void random_float_vector( float *vector, int vectorSize)
{
  int i = 0;
  while (i < vectorSize)
  {
    int r = rand() % vectorSize;
    float temp = vector[i];
    vector[i] = vector[r];
    vector[r] = temp;
    i++;
  }
}
listBase *create_number_base_list()
{
  listBase *first = NULL;
  listBase *curr = NULL;
  listBase *new = NULL;
  listBase *last = NULL;

  int qtyLine = get_random_qty(MIN_QTY_LINE, MAX_QTY_LINE);

  new = (listBase *)malloc(sizeof(listBase));
  new->numQTY = get_random_qty(1, INT_LIST_MAX_SIZE);
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
    new->numQTY = get_random_qty(1, INT_LIST_MAX_SIZE);
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
  new->floatQTY = get_random_qty(1, FLOAT_LIST_MAX_SIZE);
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
int get_random_qty(int min, int max )
{
  return min + rand() % (max + 1);
}
void show_list_base_content(listBase *first)
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
void delete_list_Base(listBase **firstBase)
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
void delete_list_value(values **firstValues)
{
  values *curr = *firstValues;
  values *prev = NULL;

  int i = 0;
  int k = 0;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstValues = NULL;
}
void show_values_content( values *firstValues )
{
  values *firstLine = firstValues;

  int l = 0;
  while( firstLine ){
    printf("line[%d] -> ", l);
    int i = 0;

    printf("ints: ");
    while( i < firstLine->intQTY )
    {
      printf("%d\t", firstLine->intList[i]);
      i++;
    }
    i = 0;
    printf("floats: ");
    while( i < firstLine->floatQTY )
    {
      printf("%.2f\t", firstLine->floatList[i]);
      i++;
    }
    puts("\n");
    l++;
    firstLine = firstLine->next;
  }
}