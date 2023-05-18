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

  natBase *currNatBase = firstNatBase;

  while (currNatBase)
  {
    sort_vector(currNatBase);
    sort_line(currNatBase);
    currNatBase = currNatBase->next;
  }
  write_result_in_file(firstNatBase);

  while (firstNatBase)
  {
    free_nat_memory_allocated(&firstNatBase->content);
    firstNatBase = firstNatBase->next;
  }

  show_natBase_list_content(firstNatBase);

  puts("END RUN!");

  return EXIT_SUCCESS;
}

str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R1Q1_file_in_path, "r");

  str *firstStr = NULL;
  str *lastStr = NULL;
  str *currStr = NULL;
  str *newStr = NULL;

  char line[MAX_SIZE_LINE];

  if (fileInPtr)
  {
    if (fgets(line, MAX_SIZE_LINE, fileInPtr))
    {
      line[strlen(line) - 1] = '\0';
      newStr = new_str();
      newStr->line = new_char_vector(MAX_SIZE_LINE);
      strcpy(newStr->line, line);
      newStr->next = NULL;

      firstStr = newStr;
      lastStr = newStr;

      while (fgets(line, MAX_SIZE_LINE, fileInPtr))
      {
        line[strlen(line) - 1] = '\0';
        newStr = new_str();
        newStr->line = new_char_vector(MAX_SIZE_LINE);
        strcpy(newStr->line, line);
        newStr->next = NULL;

        currStr = lastStr;
        currStr->next = newStr;
        lastStr = newStr;
      }
    }
  }
  return firstStr;
}

str *break_lines_in_str_list(str *line)
{
  str *firstStrList = NULL;
  str *currStrList = NULL;
  str *lastStrList = NULL;
  str *newStrList = NULL;

  char *strList;

  strList = strtok(line->line, KEY_WORD);

  if (strList)
  {
    if (!isEmpty(strList))
    {
      newStrList = new_str();
      newStrList->line = new_char_vector(strlen(strList));
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
        newStrList = new_str();
        newStrList->line = new_char_vector(strlen(strList));
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
          newStrList = new_str();
          newStrList->line = new_char_vector(strlen(strList));

          strcpy(newStrList->line, strList);

          newStrList->next = NULL;
          currStrList = lastStrList;
          currStrList->next = newStrList;
          lastStrList = newStrList;
        }
        strList = strtok(NULL, KEY_WORD);
      }
    }
  }
  return firstStrList;
}

natBase *create_nat_matrix(strBase *firstStrBase)
{
  strBase *currStrBase = firstStrBase;

  natBase *firstNatBase = NULL;
  natBase *currNatBase = NULL;
  natBase *newNatBase = NULL;
  natBase *lastNatBase = NULL;

  if (currStrBase)
  {
    newNatBase = new_natBase();
    newNatBase->content = create_nat_list(currStrBase->content);
    newNatBase->next = NULL;

    firstNatBase = newNatBase;
    lastNatBase = newNatBase;

    currStrBase = currStrBase->next;

    while (currStrBase)
    {
      newNatBase = new_natBase();
      newNatBase->content = create_nat_list(currStrBase->content);
      newNatBase->next = NULL;

      currNatBase = lastNatBase;
      currNatBase->next = newNatBase;
      lastNatBase = newNatBase;

      currStrBase = currStrBase->next;
    }
  }
  return firstNatBase;
}
strBase *create_str_matrix(str *firstLine)
{
  str *firstStrList = firstLine;

  strBase *firstStrBase = NULL;
  strBase *currStrBase = NULL;
  strBase *newStrBase = NULL;
  strBase *lastStrBase = NULL;

  if (firstStrList)
  {
    newStrBase = new_strBase();
    newStrBase->content = break_lines_in_str_list(firstStrList);
    newStrBase->next = NULL;

    firstStrBase = newStrBase;
    lastStrBase = newStrBase;

    firstStrList = firstStrList->next;
    while (firstStrList)
    {
      newStrBase = new_strBase();
      newStrBase->content = break_lines_in_str_list(firstStrList);
      newStrBase->next = NULL;

      currStrBase = lastStrBase;
      currStrBase->next = newStrBase;
      lastStrBase = newStrBase;

      firstStrList = firstStrList->next;
    }
  }
  return firstStrBase;
}

nat *create_nat_list(str *stringList)
{
  str *currStringList = stringList;

  nat *firstNat = NULL;
  nat *currNat = NULL;
  nat *newNat = NULL;
  nat *lastNat = NULL;

  if (currStringList)
  {
    newNat = new_nat();
    newNat->length = create_nat_int_list(currStringList->line, &newNat->values);
    newNat->sum = calculate_list_sum(newNat->values, newNat->length);
    newNat->next = NULL;

    firstNat = newNat;
    lastNat = newNat;

    currStringList = currStringList->next;

    while (currStringList)
    {
      newNat = new_nat();
      newNat->length = create_nat_int_list(currStringList->line, &newNat->values);
      newNat->sum = calculate_list_sum(newNat->values, newNat->length);
      newNat->next = NULL;
      currNat = lastNat;
      currNat->next = newNat;
      lastNat = newNat;

      currStringList = currStringList->next;
    }
  }
  return firstNat;
}

int create_nat_int_list(char *stringList, int **vectorInt)
{
  str *firstInt = NULL;
  str *currInt = NULL;
  str *newInt = NULL;
  str *lastInt = NULL;

  int vectorSize = 0;

  char *number = strtok(stringList, " ");

  if (number)
  {
    newInt = new_str();
    newInt->line = new_char_vector(strlen(number));
    strcpy(newInt->line, number);
    newInt->next = NULL;
    vectorSize++;
    firstInt = newInt;
    lastInt = newInt;

    number = strtok(NULL, " ");
    while (number)
    {
      newInt = new_str();
      newInt->line = new_char_vector(strlen(number));
      strcpy(newInt->line, number);
      newInt->next = NULL;

      currInt = lastInt;
      currInt->next = newInt;
      lastInt = newInt;

      vectorSize++;
      number = strtok(NULL, " ");
    }
  }

  *vectorInt = (int *)malloc(sizeof(int) * vectorSize);

  currInt = firstInt;

  int i = 0;

  while (currInt && i < vectorSize)
  {
    (*vectorInt)[i] = atoi(currInt->line);
    i++;
    currInt = currInt->next;
  }
  free_str_memory_allocated(&firstInt);
  return vectorSize;
}

void free_str_memory_allocated(str **first)
{
  str *curr = *first;
  str *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }

  *first = NULL;
}
void free_nat_memory_allocated(nat **first)
{
  nat *curr = *first;
  nat *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *first = NULL;
}

bool isEmpty(char *string)
{
  int i = 0;

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

void sort_line(natBase *start)
{
  if (!start->content)
    return;

  nat *firstList = start->content;

  while (firstList)
  {

    nat *currList = firstList->next;

    while (currList)
    {
      if (firstList->sum > currList->sum)
      {
        swap_list_content(firstList, currList);
      }
      currList = currList->next;
    }
    firstList = firstList->next;
  }
}
void sort_vector(natBase *start)
{
  nat *currNatList = start->content;

  while (currNatList)
  {
    insertio_sort(currNatList->values, currNatList->length);
    currNatList = currNatList->next;
  }
}
void swap_list_content(nat *listA, nat *listB)
{
  int auxSum = listB->sum;
  int auxLength = listB->length;
  int *auxValues = listB->values;

  listB->sum = listA->sum;
  listB->length = listA->length;
  listB->values = listA->values;

  listA->sum = auxSum;
  listA->length = auxLength;
  listA->values = auxValues;
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

void show_natBase_list_content(natBase *start)
{
  natBase *currNatBase = start;
  int i = 0;

  while (currNatBase)
  {
    nat *currNatList = currNatBase->content;

    printf("linha[%d]: ", i);
    while (currNatList)
    {
      printf("{%d} ", currNatList->length);
      int j = 0;
      printf("[ ");
      while (j < currNatList->length)
      {
        printf("%d ", currNatList->values[j]);
        j++;
      }
      printf("]\t");
      currNatList = currNatList->next;
    }
    putchar('\n');
    i++;
    currNatBase = currNatBase->next;
  }
}
void show_str_list(str *first)
{
  str *curr = first;
  int i = 1;

  while (curr)
  {
    printf("line[%d]: %s\n", i, curr->line);
    i++;
    curr = curr->next;
  }
}

void write_result_in_file(natBase *firstLine)
{
  if (!firstLine)
  {
    printf("empty content! :[\n");
    return;
  }

  natBase *currLine = firstLine;
  FILE *fileOutPtr = fopen(R1Q1_file_out_path, "w");

  if (!fileOutPtr)
  {
    printf("create file issues! :[\n");
    return;
  }

  while (currLine)
  {
    nat *line = currLine->content;

    while (line)
    {
      int i = 0;
      fprintf(fileOutPtr, "%s", "start");
      while (i < line->length)
      {
        fprintf(fileOutPtr, " %d", line->values[i]);
        i++;
      }
      fprintf(fileOutPtr, "%c", (line->next ? ' ' : '\n'));
      line = line->next;
    }

    currLine = currLine->next;
  }
}

str *new_str()
{
  return (str *)malloc(sizeof(str));
}
nat *new_nat()
{
  return (nat *)malloc(sizeof(nat));
}

strBase *new_strBase()
{
  return (strBase *)malloc(sizeof(strBase));
}
natBase *new_natBase()
{
  return (natBase *)malloc(sizeof(natBase));
}

char *new_char_vector(int size)
{
  return (char *)malloc(sizeof(char) * size);
}