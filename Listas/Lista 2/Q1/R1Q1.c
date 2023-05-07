#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "R1Q1.h"
#include "Q1InGenerator.h"

int main()
{
  // L1Q1_in_generator();
  str *firstLine = get_lines_from_file();
  strBase *firstStrBase = create_str_matrix(firstLine);
  natBase *firstNatBase = create_nat_matrix(firstStrBase);

  free_str_memory_allocated(&firstLine);

  while (firstStrBase)
  {
    free_str_memory_allocated(&firstStrBase->content);
    firstStrBase = firstStrBase->next;
  }

  natBase *actNatBase = firstNatBase;
  int i = 1;
  while (actNatBase)
  {
    ordernate_vector(actNatBase);
    printf("linha[%d]\n", i);
    ordenate_line(actNatBase);
    actNatBase = actNatBase->next;
    i++;
  }

  // actNatBase = firstNatBase;

  // int i = 0;
  // actNatBase = firstNatBase;

  // while( actNatBase ){
  //   nat *actNatList = actNatBase->content;

  //   printf("linha[%d]: ", i);
  //   while( actNatList ){
  //     printf("{%d} ", actNatList->length);
  //     int j = 0;
  //     printf("[ " );
  //     while( j < actNatList->length  ){
  //       printf("%d ", actNatList->values[j]);
  //       j++;
  //     }
  //     printf("]\t" );
  //     actNatList = actNatList->next;
  //   }
  //   putchar('\n');
  //   i++;
  //   actNatBase = actNatBase->next;
  // }

  // strBase *actStrBase = firstStrBase;
  // int i = 0;
  // while( actStrBase ){
  //   str *content = actStrBase->content;
  //   printf("lista[%d]: ", i);
  //   while( content ){
  //     printf("%s\t", content->line );
  //     content = content->next;
  //   }
  //   putchar('\n');
  //   i++;
  //   actStrBase = actStrBase->next;
  // }

  puts("fim");
  return EXIT_SUCCESS;
}
void ordenate_line(natBase *start)
{
  if( !start->content )
    return;
    
  nat *firstList = start->content;

  while (firstList->next)
  {
    // nat *actList = firstList;
    
    // while (actList->next)
    // {
    //   if (actList->sum > actList->next->sum)
    //   {
    //     // puts("\t=> antes swap");
    //     // swap_list_content(actList, actList->next);
    //     // puts("\t<= depois swap");
    //   }
    //   actList = actList->next;
    // }
    firstList = firstList->next;
  }
}
void ordernate_vector(natBase *start)
{
  nat *actNatList = start->content;

  while (actNatList)
  {
    insertio_sort(actNatList->values, actNatList->length);
    actNatList = actNatList->next;
  }
}
natBase *create_nat_matrix(strBase *firstStrBase)
{
  strBase *actStrBase = firstStrBase;

  natBase *firstNatBase = NULL;
  natBase *actNatBase = NULL;
  natBase *newNatBase = NULL;
  natBase *lastNatBase = NULL;

  if (actStrBase)
  {
    newNatBase = malloc(sizeof(natBase));
    newNatBase->content = create_nat_list(actStrBase->content);
    newNatBase->next = NULL;

    firstNatBase = newNatBase;
    lastNatBase = newNatBase;

    actStrBase = actStrBase->next;

    while (actStrBase)
    {
      newNatBase = malloc(sizeof(natBase));
      newNatBase->content = create_nat_list(actStrBase->content);
      newNatBase->next = NULL;

      actNatBase = lastNatBase;
      actNatBase->next = newNatBase;
      lastNatBase = newNatBase;

      actStrBase = actStrBase->next;
      ;
    }
  }
  // int i = 0;
  // actNatBase = firstNatBase;

  // while( actNatBase ){
  //   nat *actNatList = actNatBase->content;

  //   printf("linha[%d]:", i);
  //   while( actNatList ){
  //     int j = 0;
  //     printf("[ " );
  //     while( j < actNatList->length ){
  //       printf("%d ", actNatList->values[j]);
  //       j++;
  //     }
  //     printf("]\t" );
  //     actNatList = actNatList->next;
  //   }
  //   putchar('\n');
  //   i++;
  //   actNatBase = actNatBase->next;
  // }

  return firstNatBase;
}
strBase *create_str_matrix(str *firstLine)
{
  str *firstStrList = firstLine;

  strBase *firstStrBase = NULL;
  strBase *actStrBase = NULL;
  strBase *newStrBase = NULL;
  strBase *lastStrBase = NULL;

  if (firstStrList)
  {
    newStrBase = malloc(sizeof(strBase));
    newStrBase->content = break_lines_in_str_list(firstStrList);
    newStrBase->next = NULL;

    firstStrBase = newStrBase;
    lastStrBase = newStrBase;

    firstStrList = firstStrList->next;
    while (firstStrList)
    {
      newStrBase = malloc(sizeof(strBase));
      newStrBase->content = break_lines_in_str_list(firstStrList);
      newStrBase->next = NULL;

      actStrBase = lastStrBase;
      actStrBase->next = newStrBase;
      lastStrBase = newStrBase;

      firstStrList = firstStrList->next;
    }
  }
  return firstStrBase;
}
str *break_lines_in_str_list(str *line)
{
  str *firstStrList = NULL;
  str *actStrList = NULL;
  str *lastStrList = NULL;
  str *newStrList = NULL;

  char *strList;

  strList = strtok(line->line, KEY_WORD);

  if (strList)
  {
    if (!isEmpty(strList))
    {
      newStrList = malloc(sizeof(str));
      newStrList->line = malloc(sizeof(char) * strlen(strList));
      strcpy(newStrList->line, strList);
      newStrList->next = NULL;

      firstStrList = newStrList;
      lastStrList = newStrList;
    }
    else
    {
      strList = strtok(NULL, KEY_WORD);
      while (isEmpty(strList) && strList)
      {
        strList = strtok(NULL, KEY_WORD);
      }
      if (strList)
      {
        newStrList = malloc(sizeof(str));
        newStrList->line = malloc(sizeof(char) * strlen(strList));
        strcpy(newStrList->line, strList);
        newStrList->next = NULL;

        firstStrList = newStrList;
        lastStrList = newStrList;
      }
    }
    if (firstStrList)
    {
      strList = strtok(NULL, KEY_WORD);

      while (strList != NULL)
      {
        if (!isEmpty(strList))
        {
          newStrList = malloc(sizeof(str));
          newStrList->line = malloc(sizeof(char) * strlen(strList));

          strcpy(newStrList->line, strList);

          newStrList->next = NULL;
          actStrList = lastStrList;
          actStrList->next = newStrList;
          lastStrList = newStrList;
        }
        strList = strtok(NULL, KEY_WORD);
      }
    }
  }

  // actStrList = firstStrList;
  // while (actStrList)
  // {
  //   puts(actStrList->line);
  //   actStrList = actStrList->next;
  // }
  return firstStrList;
}
str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R1Q1_file_in_path, "r");

  str *firstStr = NULL;
  str *lastStr = NULL;
  str *actStr = NULL;
  str *newStr = NULL;

  char line[MAX_SIZE_LINE];

  if (fileInPtr)
  {
    if (fgets(line, MAX_SIZE_LINE, fileInPtr))
    {
      line[strlen(line) - 1] = '\0';
      newStr = (str *)malloc(sizeof(str));
      newStr->line = (char *)malloc(sizeof(char) * MAX_SIZE_LINE);
      strcpy(newStr->line, line);
      newStr->next = NULL;

      firstStr = newStr;
      lastStr = newStr;

      while (fgets(line, MAX_SIZE_LINE, fileInPtr))
      {
        line[strlen(line) - 1] = '\0';
        newStr = (str *)malloc(sizeof(str));
        newStr->line = (char *)malloc(sizeof(char) * MAX_SIZE_LINE);
        strcpy(newStr->line, line);
        newStr->next = NULL;

        actStr = lastStr;
        actStr->next = newStr;
        lastStr = newStr;
      }
    }
  }
  return firstStr;
}
nat *create_nat_list(str *stringList)
{
  str *actStringList = stringList;

  nat *firstNat = NULL;
  nat *actNat = NULL;
  nat *newNat = NULL;
  nat *lastNat = NULL;

  if (actStringList)
  {
    newNat = malloc(sizeof(nat));
    newNat->length = create_nat_int_list(actStringList->line, &newNat->values);
    newNat->sum = calculate_list_sum(newNat->values, newNat->length);
    newNat->next = NULL;

    firstNat = newNat;
    lastNat = newNat;

    actStringList = actStringList->next;

    while (actStringList)
    {
      newNat = malloc(sizeof(nat));
      newNat->length = create_nat_int_list(actStringList->line, &newNat->values);
      newNat->sum = calculate_list_sum(newNat->values, newNat->length);
      newNat->next = NULL;
      actNat = lastNat;
      actNat->next = newNat;
      lastNat = newNat;

      actStringList = actStringList->next;
    }
  }
  // actNat = firstNat;

  // while( actNat ){
  //   printf("[ " );
  //   int i = 0;

  //   while( actNat->values[i] != END_VECTOR){
  //     printf("%d ", actNat->values[i]);
  //     i++;
  //   }

  //   printf("]\t" );
  //   actNat = actNat->next;
  // }
  // putchar('\n');
  return firstNat;
}
int create_nat_int_list(char *stringList, int **vectorInt)
{
  str *firstInt = NULL;
  str *actInt = NULL;
  str *newInt = NULL;
  str *lastInt = NULL;

  int vectorSize = 0;

  char *number = strtok(stringList, " ");

  if (number)
  {
    newInt = malloc(sizeof(str));
    newInt->line = malloc(sizeof(char) * strlen(number));
    strcpy(newInt->line, number);
    newInt->next = NULL;
    vectorSize++;
    firstInt = newInt;
    lastInt = newInt;

    number = strtok(NULL, " ");
    while (number)
    {
      newInt = malloc(sizeof(str));
      newInt->line = malloc(sizeof(char) * strlen(number));
      strcpy(newInt->line, number);
      newInt->next = NULL;

      actInt = lastInt;
      actInt->next = newInt;
      lastInt = newInt;

      vectorSize++;
      number = strtok(NULL, " ");
    }
  }

  *vectorInt = malloc(sizeof(int) * vectorSize);

  actInt = firstInt;

  int i = 0;

  while (actInt && i < vectorSize)
  {
    (*vectorInt)[i] = atoi(actInt->line);
    i++;
    actInt = actInt->next;
  }
  free_str_memory_allocated(&firstInt);
  return vectorSize;
}
void *free_str_memory_allocated(str **first)
{
  str *act = *first;
  str *prev = NULL;

  while (act)
  {
    prev = act;
    act = act->next;
    free(prev);
    prev = NULL;
  }

  *first = NULL;
}
void show_lines_as_strings(str *first)
{
  str *act = first;
  int i = 1;

  while (act)
  {
    printf("line[%d]: %s\n", i, act->line);
    i++;
    act = act->next;
  }
}
bool isEmpty(char *string)
{
  int i = 0;
  // printf("string : %s\n", string);
  if (string)
  {
    while (string[i] != '\0')
    {
      if (string[i] != ' ')
      {
        return false;
      }
      i++;
    }
  }
  return true;
}
void insertio_sort(int *vector, int size)
{
  int key;

  for (int i = 1; i < size; i++)
  {
    key = vector[i];
    int j = i - 1;
    while (j >= 0 && vector[j] > key)
    {
      vector[j + 1] = vector[j];
      j--;
    }
    vector[j + 1] = key;
  }
}
int calculate_list_sum(int *natList, int size)
{
  int i = 0;
  int sum = 0;
  while (i < size)
  {
    sum += natList[i];
    i++;
  }
  return sum;
}
void swap_list_content(nat *listA, nat *listB)
{
  int auxSum = listB->sum;
  int auxLength = listB->length;
  int *auxValues = malloc(sizeof(int) * auxLength);

  int i = 0;

  while (i < auxLength)
  {
    auxValues[i] = listB->values[i];
    i++;
  }

  listB->length = listA->length;
  listB->sum = listA->sum;
  free(listB->values);
  listB->values = NULL;

  i = 0;

  listB->values = malloc(sizeof(int) * listA->length);

  while (i < listA->length)
  {
    listB->values[i] = listA->values[i];
    i++;
  }

  listA->length = auxLength;
  listA->sum = auxSum;

  i = 0;

  free(listA->values);
  listA->values = NULL;

  listA->values = malloc(sizeof(int) * auxLength);

  while (i < auxLength)
  {
    listA->values[i] = auxValues[i];
    i++;
  }
}