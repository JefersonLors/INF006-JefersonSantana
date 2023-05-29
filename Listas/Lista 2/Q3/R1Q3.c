#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "R1Q3.h"

int main()
{
  str *firstStr = NULL;
  strV *firstStrV = NULL;
  numbers *firstsNumbers = NULL;
  packBase *firstPackBase = NULL;
  packBase *currPackBase = NULL;

  firstStr = get_lines_from_file();
  firstStrV = create_strV_list(firstStr);

  delete_str_list(&firstStr);

  firstsNumbers = create_numbers_list(firstStrV);

  delete_strV_list(&firstStrV);

  firstPackBase = create_packBase_list(firstsNumbers);

  delete_numbers_list(&firstsNumbers);

  currPackBase = firstPackBase;

  while (currPackBase)
  {
    sort_pack_list(currPackBase->packs);
    pack *currPack = currPackBase->packs;

    while (currPack)
    {
      sort_value_list(currPack->floats, currPack->valuesQTY);
      currPack = currPack->next;
    }
    currPackBase = currPackBase->next;
  }
  write_result_in_file(firstPackBase);
  // show_packaBase_content(firstPackBase);

  currPackBase = firstPackBase;

  while (currPackBase)
  {
    delete_pack_list(&currPackBase->packs);
    currPackBase = currPackBase->next;
  }

  delete_packBase_list(&firstPackBase);

  puts("END RUN!");
  return EXIT_SUCCESS;
}
packBase *create_packBase_list(numbers *firstNumbers)
{
  numbers *currNumbers = firstNumbers;

  packBase *first = NULL;
  packBase *curr = NULL;
  packBase *new = NULL;
  packBase *last = NULL;

  if (currNumbers)
  {
    new = new_packBase();
    new->packs = create_number_pack(currNumbers);
    new->next = NULL;

    first = new;
    last = new;

    currNumbers = currNumbers->next;
    while (currNumbers)
    {
      new = new_packBase();
      new->packs = create_number_pack(currNumbers);
      new->next = NULL;

      curr = last;
      curr->next = new;
      last = new;

      currNumbers = currNumbers->next;
    }
  }
  return first;
}
pack *create_number_pack(numbers *firstsNumbers)
{
  numbers *currNumbers = firstsNumbers;

  pack *first = NULL;
  pack *curr = NULL;
  pack *new = NULL;
  pack *last = NULL;

  if (currNumbers)
  {
    int i = 0;
    new = new_pack();
    new->key = currNumbers->keys[i];
    new->floats = get_values(new->key, currNumbers->values, currNumbers->valuesQTY, &new->valuesQTY);
    new->next = NULL;
    new->prev = NULL;

    first = new;
    last = new;

    i++;
    while (i < currNumbers->keyQTY)
    {
      new = new_pack();
      new->key = currNumbers->keys[i];
      new->floats = get_values(new->key, currNumbers->values, currNumbers->valuesQTY, &new->valuesQTY);
      new->next = NULL;
      new->prev = NULL;

      curr = last;
      curr->next = new;
      new->prev = curr;
      last = new;

      i++;
    }
  }
  return first;
}
value *get_values(int key, float *values, int valuesQTY, int *sizeList)
{
  value *first = NULL;
  value *curr = NULL;
  value *new = NULL;
  value *last = NULL;
  int _sizeList = 0;

  if (valuesQTY > 0)
  {
    int i = 0;
    new = new_value();
    new->next = NULL;

    while (i < valuesQTY)
    {
      if (values[i] >= key && values[i] < key + 1)
      {
        new->content = values[i];
        _sizeList++;
        break;
      }
      i++;
    }
    first = new;
    last = new;
    last->next = first;

    i++;
    while (i < valuesQTY)
    {
      if (values[i] >= key && values[i] < key + 1)
      {
        new = new_value();
        new->content = values[i];
        new->next = NULL;
        _sizeList++;

        curr = last;
        curr->next = new;
        last = new;
        last->next = first;
      }
      i++;
    }
  }
  *sizeList = _sizeList;
  return first;
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
      newStr = new_str();
      newStr->content = new_char_vector(MAX_SIZE_LINE);
      strcpy(newStr->content, line);
      newStr->next = NULL;

      firstStr = newStr;
      lastStr = newStr;

      while (fgets(line, MAX_SIZE_LINE, fileInPtr))
      {
        line[strlen(line) - 1] = '\0';
        newStr = new_str();
        newStr->content = new_char_vector(MAX_SIZE_LINE);
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
    newS = new_str();
    newS->content = new_char_vector(sizeStr);
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
      newS = new_str();
      newS->content = new_char_vector(sizeStr);
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

  new->intStrList = new_char_vector(100);
  new->floatStrList = new_char_vector(1000);
  new->next = NULL;

  strcpy(new->intStrList, strtok(line->content, KEY_WORD2));
  strcpy(new->floatStrList, strtok(NULL, KEY_WORD2));

  remove_non_numeric_characters_from_string(new->intStrList);
  remove_non_numeric_characters_from_string(new->floatStrList);

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

  newN = new_numbers();
  newN->keyQTY = get_size_str_linked_list(currStrKey);
  newN->keys = new_int_vector(newN->keyQTY);
  newN->next = NULL;
  int i = 0;

  while (i < newN->keyQTY && currStrKey)
  {
    newN->keys[i] = atoi(currStrKey->content);
    i++;
    currStrKey = currStrKey->next;
  }

  newN->valuesQTY = get_size_str_linked_list(currStrFloat);
  newN->values = new_float_vector(newN->valuesQTY);

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

    newN = new_numbers();
    newN->keyQTY = get_size_str_linked_list(currStrKey);
    newN->keys = new_int_vector(newN->keyQTY);
    newN->next = NULL;

    int i = 0;

    while (i < newN->keyQTY && currStrKey)
    {
      newN->keys[i] = atoi(currStrKey->content);
      i++;
      currStrKey = currStrKey->next;
    }

    newN->valuesQTY = get_size_str_linked_list(currStrFloat);
    newN->values = new_float_vector(newN->valuesQTY);

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
void delete_numbers_list(numbers **firstNumbers)
{
  numbers *curr = *firstNumbers;
  numbers *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstNumbers = NULL;
}
void delete_pack_list(pack **firstPack)
{
  pack *curr = *firstPack;
  pack *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstPack = NULL;
}
void delete_packBase_list(packBase **firstPackBase)
{
  packBase *curr = *firstPackBase;
  packBase *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(prev);
    prev = NULL;
  }
  *firstPackBase = NULL;
}
void remove_non_numeric_characters_from_string(char *string)
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
void show_packaBase_content(packBase *firstPack)
{
  packBase *curr = firstPack;
  int l = 1;

  while (curr)
  {
    printf("linha[%d] -> ", l);
    pack *currT = curr->packs;
    printf("[");
    while (currT)
    {
      int j = 0;
      printf("%d(", currT->key);

      value *floats = currT->floats;
      while (j < currT->valuesQTY)
      {
        printf("%.2f", floats->content);
        if (j + 1 < currT->valuesQTY)
        {
          printf("->");
        }
        floats = floats->next;
        j++;
      }
      printf(")");
      if (currT->next)
      {
        printf("->");
      }

      currT = currT->next;
    }
    printf("]\n");
    l++;
    curr = curr->next;
  }
}
void sort_value_list(value *firstValue, int sizeList)
{
  if (firstValue)
  {
    value *currValue = firstValue;
    int i = 0;

    while (i < sizeList)
    {
      value *nextValue = currValue->next;

      int j = 1;
      while (j < sizeList)
      {
        if (currValue->content < nextValue->content)
        {
          float saveValue = nextValue->content;
          nextValue->content = currValue->content;
          currValue->content = saveValue;
        }
        j++;
        nextValue = nextValue->next;
      }
      i++;
      currValue = currValue->next;
    }
  }
}
void sort_pack_list(pack *firstPack)
{
  if (firstPack)
  {
    pack *currPack = firstPack->next;

    while (currPack)
    {
      pack *prevPack = currPack->prev;
      pack *nextPack = NULL;

      value *saveCurrValues = currPack->floats;
      int saveCurrValuesQTY = currPack->valuesQTY;
      int saveCurrKey = currPack->key;

      while (prevPack && (prevPack->key > saveCurrKey))
      {
        nextPack = prevPack->next;

        nextPack->key = prevPack->key;
        nextPack->floats = prevPack->floats;
        nextPack->valuesQTY = prevPack->valuesQTY;

        prevPack = prevPack->prev;
      }
      if (prevPack)
      {
        prevPack->next->floats = saveCurrValues;
        prevPack->next->valuesQTY = saveCurrValuesQTY;
        prevPack->next->key = saveCurrKey;
      }
      else
      {
        nextPack->prev->floats = saveCurrValues;
        nextPack->prev->valuesQTY = saveCurrValuesQTY;
        nextPack->prev->key = saveCurrKey;
      }
      currPack = currPack->next;
    }
  }
}
void write_result_in_file(packBase *firstPackBase)
{
  FILE *fileOutPtr = fopen(R1Q3_file_out_path, "w");

  if (fileOutPtr)
  {
    packBase *currPackBase = firstPackBase;

    while (currPackBase)
    {
      fprintf(fileOutPtr, "[");

      pack *currPack = currPackBase->packs;

      while (currPack)
      {
        fprintf(fileOutPtr, "%d(", currPack->key);
        int i = 0;
        value *currValue = currPack->floats;
        while (i < currPack->valuesQTY)
        {
          fprintf(fileOutPtr, "%.2f", currValue->content);
          if (i + 1 != currPack->valuesQTY)
          {
            fprintf(fileOutPtr, "->");
          }
          currValue = currValue->next;
          i++;
        }
        fprintf(fileOutPtr, ")");
        if (currPack->next)
        {
          fprintf(fileOutPtr, "->");
        }
        currPack = currPack->next;
      }

      fprintf(fileOutPtr, "]\n");
      currPackBase = currPackBase->next;
    }
    fclose(fileOutPtr);
  }
  else
  {
    printf("ops! file creation issues :[\n");
  }
}
str *new_str()
{
  return (str *)malloc(sizeof(str));
}
packBase *new_packBase()
{
  return (packBase *)malloc(sizeof(packBase));
}
pack *new_pack()
{
  return (pack *)malloc(sizeof(pack));
}
value *new_value()
{
  return (value *)malloc(sizeof(value));
}
char *new_char_vector(int size)
{
  if (size < 1)
  {
    return NULL;
  }
  return (char *)malloc(sizeof(char) * size);
}
int *new_int_vector(int size)
{
  if (size < 1)
  {
    return NULL;
  }

  return (int *)malloc(sizeof(int) * size);
}
float *new_float_vector(int size)
{
  if (size < 1)
  {
    return NULL;
  }

  return (float *)malloc(sizeof(float) * size);
}
numbers *new_numbers()
{
  return (numbers *)malloc(sizeof(numbers));
}