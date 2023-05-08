#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "R1Q2.h"
#include "Q2InGenerator.h"

int main()
{
  // L1Q2_in_generator();
  str *firstLine = get_lines_from_file();
  strBase *firstStrBase = create_str_matrix(firstLine);
  nameBase *firstNameBase = create_name_matrix(firstStrBase);

  free_str_memory_allocated(&firstLine);

  while (firstStrBase)
  {
    free_str_memory_allocated(&firstStrBase->content);
    firstStrBase = firstStrBase->next;
  }
  show_all_name_list(firstNameBase);

  puts("fim");
  return EXIT_SUCCESS;
}
nameBase *create_name_matrix(strBase *firstStrBase)
{
  strBase *actStrBase = firstStrBase;

  nameBase *firstNameBase = NULL;
  nameBase *actNameBase = NULL;
  nameBase *newNameBase = NULL;
  nameBase *lastNameBase = NULL;

  if (actStrBase)
  {
    newNameBase = (nameBase *)malloc(sizeof(nameBase));
    newNameBase->list = create_name_list(actStrBase->content);
    newNameBase->next = NULL;
    firstNameBase = newNameBase;
    lastNameBase = newNameBase;

    actStrBase = actStrBase->next;

    while (actStrBase)
    {
      newNameBase = (nameBase *)malloc(sizeof(nameBase));
      newNameBase->list = create_name_list(actStrBase->content);
      newNameBase->next = NULL;

      actNameBase = lastNameBase;
      actNameBase->next = newNameBase;
      lastNameBase = newNameBase;

      actStrBase = actStrBase->next;
    }
  }
  return firstNameBase;
}
name *create_name_list(str *firstStr)
{
  str *actStr = firstStr;

  name *firstName = NULL;
  name *actName = NULL;
  name *newName = NULL;
  name *lastName = NULL;

  if (actStr)
  {
    newName = create_name(actStr->line);

    firstName = newName;
    lastName = newName;

    actStr = actStr->next;

    while (actStr)
    {
      newName = create_name(actStr->line);

      actName = lastName;
      actName->next = newName;
      lastName = newName;

      actStr = actStr->next;
    }
  }

  return firstName;
}
name *create_name(char *stringName)
{
  name *new = (name *)malloc(sizeof(name));
  new->operation = NONE;
  new->content = (char *)malloc(sizeof(char) * strlen(stringName));
  strcpy(new->content, stringName);
  new->next = NULL;

  return new;
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
    newStrBase = (strBase *)malloc(sizeof(strBase));
    newStrBase->content = break_lines_in_str_list(firstStrList);
    newStrBase->next = NULL;

    firstStrBase = newStrBase;
    lastStrBase = newStrBase;

    firstStrList = firstStrList->next;
    while (firstStrList)
    {
      newStrBase = (strBase *)malloc(sizeof(strBase));
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
      newStrList = (str *)malloc(sizeof(str));
      newStrList->line = (char *)malloc(sizeof(char) * strlen(strList));
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
        newStrList = (str *)malloc(sizeof(str));
        newStrList->line = (char *)malloc(sizeof(char) * strlen(strList));
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
          newStrList = (str *)malloc(sizeof(str));
          newStrList->line = (char *)malloc(sizeof(char) * strlen(strList));

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
  return firstStrList;
}
str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R1Q2_file_in_path, "r");

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
void free_str_memory_allocated(str **first)
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
void show_all_name_list(nameBase *firstNameBase)
{
  nameBase *act = firstNameBase;

  int i = 1;

  while (act)
  {
    printf("linha[%d]", i);
    name *actName = act->list;

    while (actName)
    {
      printf(" %s {%d}", actName->content, actName->operation);
      actName = actName->next;
    }
    printf("\n");

    i++;
    act = act->next;
  }
}