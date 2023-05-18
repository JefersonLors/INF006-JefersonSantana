#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Q3InGenerator.h"
#include "R1Q3.h"

int main()
{
  // L1Q3_in_generator();
  str *firstStr = get_lines_from_file();
  strV *firstStrV = create_strV_list(firstStr);
  numbers *firstsNumbers = create_numbers_list(firstStrV);

  delete_str_list(&firstStr);
  delete_strV_list(&firstStrV);
  delete_numbers_list(&firstsNumbers);
  printf("teste");
  // int l = 0;
  // while (firstsNumbers)
  // {
  //   int i = 0;

  //   printf("line[%d] -> keys: ", l);
  //   while (i < firstsNumbers->keyQTY)
  //   {
  //     printf("%d\t", firstsNumbers->keys[i]);
  //     i++;
  //   }
  //   i = 0;

  //   printf("values: ");
  //   while (i < firstsNumbers->valuesQTY)
  //   {
  //     printf("%.2f\t", firstsNumbers->values[i]);
  //     i++;
  //   }
  //   printf("\n\n");
  //   l++;
  //   firstsNumbers = firstsNumbers->next;
  // }

  puts("end run!");
  return EXIT_SUCCESS;
}
str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R1Q3_file_in_path, "r");

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
      newStr = (str *)malloc(sizeof(str));
      newStr->content = (char *)malloc(sizeof(char) * MAX_SIZE_LINE);
      strcpy(newStr->content, line);
      newStr->next = NULL;

      firstStr = newStr;
      lastStr = newStr;

      while (fgets(line, MAX_SIZE_LINE, fileInPtr))
      {
        line[strlen(line) - 1] = '\0';
        newStr = (str *)malloc(sizeof(str));
        newStr->content = (char *)malloc(sizeof(char) * MAX_SIZE_LINE);
        strcpy(newStr->content, line);
        newStr->next = NULL;

        currStr = lastStr;
        currStr->next = newStr;
        lastStr = newStr;
      }
    }
  }
  return firstStr;
}
str *break_line_in_str_list(char *line)
{
  str *firstS = NULL;
  str *currS = NULL;
  str *newS = NULL;
  str *lastS = NULL;

  char *middleWhere = NULL;

  middleWhere = strtok(line, " ");
  int sizeStr = strlen(middleWhere);

  if (sizeStr)
  {
    newS = (str *)malloc(sizeof(str));
    newS->content = (char *)malloc(sizeof(char) * sizeStr);
    newS->next = NULL;
    strcpy(newS->content, "");
    strcpy(newS->content, middleWhere);
    firstS = newS;
    lastS = newS;
  }

  middleWhere = strtok(NULL, " ");
  while (middleWhere)
  {
    sizeStr = strlen(middleWhere);
    if (sizeStr)
    {
      newS = (str *)malloc(sizeof(str));
      newS->content = (char *)malloc(sizeof(char) * sizeStr);
      newS->next = NULL;
      strcpy(newS->content, "");
      strcpy(newS->content, middleWhere);
      currS = lastS;
      currS->next = newS;
      lastS = newS;
    }
    middleWhere = strtok(NULL, " ");
  }
  return firstS;
}
strV *create_strV_list(str *firstLine)
{
  strV *first = NULL;
  strV *curr = NULL;
  strV *new = NULL;
  strV *last = NULL;

  if (firstLine)
  {
    str *currLine = firstLine;

    new = break_in_two_lists(currLine);
    first = new;
    last = new;

    currLine = currLine->next;

    while (currLine)
    {
      new = break_in_two_lists(currLine);
      curr = last;
      curr->next = new;
      last = new;
      currLine = currLine->next;
    }
  }

  return first;
}
strV *break_in_two_lists(str *line)
{
  strV *new = (strV *)malloc(sizeof(strV));

  new->intStrList = (char *)malloc(sizeof(char) * 100);
  new->floatStrList = (char *)malloc(sizeof(char) * 1000);
  new->next = NULL;

  strcpy(new->intStrList, strtok(line->content, KEY_WORD2));
  strcpy(new->floatStrList, strtok(NULL, KEY_WORD2));

  remove_alphabetic_non_numeric_characters_from_string(new->intStrList);
  remove_alphabetic_non_numeric_characters_from_string(new->floatStrList);

  return new;
}
numbers *create_numbers_list(strV *firstsStrValues)
{
  strV *currStrV = firstsStrValues;

  numbers *firstN = NULL;
  numbers *currN = NULL;
  numbers *newN = NULL;
  numbers *lastN = NULL;

  str *firstStrKey = break_line_in_str_list(currStrV->intStrList);
  str *firstStrFloat = break_line_in_str_list(currStrV->floatStrList);

  str *currStrKey = firstStrKey;
  str *currStrFloat = firstStrFloat;

  newN = (numbers *)malloc(sizeof(numbers));
  newN->keyQTY = get_size_str_linked_list(currStrKey);
  newN->keys = (int *)malloc(sizeof(int) * newN->keyQTY);

  int i = 0;

  while (i < newN->keyQTY && currStrKey)
  {
    newN->keys[i] = atoi(currStrKey->content);
    i++;
    currStrKey = currStrKey->next;
  }

  newN->valuesQTY = get_size_str_linked_list(currStrFloat);
  newN->values = (float *)malloc(sizeof(float) * newN->valuesQTY);

  i = 0;

  while (i < newN->valuesQTY && currStrFloat)
  {
    newN->values[i] = atof(currStrFloat->content);
    i++;
    currStrFloat = currStrFloat->next;
  }
  delete_str_list(&firstStrKey);
  delete_str_list(&firstStrFloat);

  firstN = newN;
  lastN = newN;

  currStrV = currStrV->next;

  while (currStrV)
  {
    firstStrKey = break_line_in_str_list(currStrV->intStrList);
    firstStrFloat = break_line_in_str_list(currStrV->floatStrList);

    str *currStrKey = firstStrKey;
    str *currStrFloat = firstStrFloat;

    newN = (numbers *)malloc(sizeof(numbers));
    newN->keyQTY = get_size_str_linked_list(currStrKey);
    newN->keys = (int *)malloc(sizeof(int) * newN->keyQTY);

    int i = 0;

    while (i < newN->keyQTY && currStrKey)
    {
      newN->keys[i] = atoi(currStrKey->content);
      i++;
      currStrKey = currStrKey->next;
    }

    newN->valuesQTY = get_size_str_linked_list(currStrFloat);
    newN->values = (float *)malloc(sizeof(float) * newN->valuesQTY);

    i = 0;

    while (i < newN->valuesQTY && currStrFloat)
    {
      newN->values[i] = atof(currStrFloat->content);
      i++;
      currStrFloat = currStrFloat->next;
    }
    delete_str_list(&firstStrKey);
    delete_str_list(&firstStrFloat);

    currN = lastN;
    currN->next = newN;
    lastN = newN;

    currStrV = currStrV->next;
  }
  return firstN;
}
void delete_str_list(str **firstStr)
{
  str *curr = *firstStr;
  str *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstStr = NULL;
}
void delete_strV_list(strV **firstStrV)
{
  strV *curr = *firstStrV;
  strV *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstStrV = NULL;
}
void delete_numbers_list( numbers **firstNumbers )
{
  numbers *curr = *firstNumbers;
  numbers *prev = NULL;

  while( curr ){
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstNumbers = NULL;
} 
void remove_alphabetic_non_numeric_characters_from_string(char *string)
{
  int i = 0;
  while (string[i] != '\0')
  {
    if (string[i] != '.' && (string[i] < 48 || string[i] > 57))
    {
      string[i] = ' ';
    }
    i++;
  }
}
int get_size_str_linked_list(str *start)
{
  str *curr = start;
  int i = 0;
  while (curr)
  {
    i++;
    curr = curr->next;
  }
  return i;
}