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
  strBase *firstStrBase = create_str_stack_matrix(firstLine);
  logBase *logLines = create_log_line_matrix(firstStrBase);

  free_str_memory_allocated(&firstLine);

  while (firstStrBase)
  {
    free_str_memory_allocated(&firstStrBase->content);
    firstStrBase = firstStrBase->next;
  }
  write_result_in_file(logLines);
  free_logLine_memory_allocated(&logLines);
  puts("end run!");
  return EXIT_SUCCESS;
}
logBase *create_log_line_matrix(strBase *nameList)
{
  strBase *currNameList = nameList;

  logBase *firstLogLine = NULL;
  logBase *currLogLine = NULL;
  logBase *newLogLine = NULL;
  logBase *lastLogLine = NULL;

  if (currNameList)
  {
    newLogLine = (logBase *)malloc(sizeof(logBase));
    newLogLine->content = create_log_line(currNameList->content);
    newLogLine->next = NULL;

    firstLogLine = newLogLine;
    lastLogLine = newLogLine;

    currNameList = currNameList->next;

    while (currNameList)
    {
      newLogLine = (logBase *)malloc(sizeof(logBase));
      newLogLine->content = create_log_line(currNameList->content);
      newLogLine->next = NULL;
      currLogLine = lastLogLine;
      currLogLine->next = newLogLine;
      lastLogLine = newLogLine;
      currNameList = currNameList->next;
    }
  }
  return firstLogLine;
}
strBase *create_str_stack_matrix(str *firstLine)
{
  str *firstStrList = firstLine;

  strBase *firstStrBase = NULL;
  strBase *currStrBase = NULL;
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

      currStrBase = lastStrBase;
      currStrBase->next = newStrBase;
      lastStrBase = newStrBase;

      firstStrList = firstStrList->next;
    }
  }
  return firstStrBase;
}
str *break_lines_in_str_list(str *line)
{
  str *firstName = NULL;
  str *currName = NULL;
  str *lastName = NULL;
  str *newName = NULL;

  char *strList;

  strList = strtok(line->content, KEY_WORD);

  if (strList)
  {
    if (!isEmpty(strList))
    {
      newName = (str *)malloc(sizeof(str));
      newName->content = (char *)malloc(sizeof(char) * strlen(strList));
      strcpy(newName->content, strList);
      newName->next = NULL;
      newName->prev = NULL;

      firstName = newName;
      lastName = newName;
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
        newName = (str *)malloc(sizeof(str));
        newName->content = (char *)malloc(sizeof(char) * strlen(strList));
        strcpy(newName->content, strList);
        newName->next = NULL;
        newName->prev = NULL;

        firstName = newName;
        lastName = newName;
      }
    }
    if (firstName)
    {
      strList = strtok(NULL, KEY_WORD);

      while (strList != NULL)
      {
        if (!isEmpty(strList))
        {
          newName = (str *)malloc(sizeof(str));
          newName->content = (char *)malloc(sizeof(char) * strlen(strList));

          strcpy(newName->content, strList);

          newName->next = NULL;
          newName->prev = NULL;

          currName = lastName;
          currName->next = newName;
          newName->prev = currName;
          lastName = newName;
        }
        strList = strtok(NULL, KEY_WORD);
      }
    }
  }
  firstName->prev = NULL;
  lastName->next = NULL;
  return firstName;
}
str *get_lines_from_file()
{
  FILE *fileInPtr = fopen(R1Q2_file_in_path, "r");

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
char *create_log_line(str *nameList)
{
  str *currItem = nameList;
  char *newLogLine = NULL;

  if (currItem)
  {
    newLogLine = (char *)malloc(sizeof(char) * MAX_SIZE_LINE);
    strcpy(newLogLine, "");

    sprintf(newLogLine, "push-%s ", currItem->content);
    if (currItem->next)
    {
      currItem = currItem->next;
      do
      {
        stack_name_insert_sorted(currItem, newLogLine);
        currItem = currItem->next;
      } while (currItem);
    }
  }
  return newLogLine;
}
void stack_name_insert_sorted(str *currItem, char *log)
{
  if (currItem)
  {
    str *next = currItem;
    str *prev = currItem->prev;
    int popI = 0;

    if (prev)
    {
      int sizeCurrItemContent = strlen(currItem->content);
      char *currItemContent = (char *)malloc(sizeof(char) * 20);

      strcpy(currItemContent, currItem->content);

      if (strcmp(prev->content, currItemContent) > 0)
      {
        while (prev && strcmp(prev->content, currItemContent) > 0)
        {
          next = prev->next;

          int newSize = strlen(prev->content);
          int oldSize = strlen(next->content);

          if (oldSize < newSize)
          {
            next->content = NULL;
            next->content = (char *)malloc(sizeof(char) * newSize);
            strcpy(next->content, "");
          }
          strcpy(next->content, prev->content);

          next = prev;
          popI++;
          prev = prev->prev;
        }
        if (prev)
        {
          int newSize = strlen(currItemContent);
          int oldSize = strlen(prev->next->content);

          if (oldSize < newSize)
          {
            prev->next->content = NULL;
            prev->next->content = (char *)malloc(sizeof(char) * newSize);
            strcpy(prev->next->content, "");
          }
          strcpy(prev->next->content, currItemContent);
        }
        else
        {
          int newSize = strlen(currItemContent);
          int oldSize = strlen(next->content);

          if (oldSize < newSize)
          {
            next->content = NULL;
            next->content = (char *)malloc(sizeof(char) * newSize);
            strcpy(next->content, "");
          }
          strcpy(next->content, currItemContent);
        }
        char *popS = (char *)malloc(sizeof(char) * 10);
        strcpy(popS, "");
        sprintf(popS, "%d", popI);

        strcat(log, popS);
        strcat(log, "x-pop ");
        free(popS);

        str *push = (prev ? prev->next : next);
        int i = popI;
        while (i >= 0)
        {
          strcat(log, "push-");
          strcat(log, push->content);
          if (push->next)
          {
            strcat(log, " ");
          }
          push = push->next;
          i--;
        }
      }
      else
      {
        strcat(log, "push-");
        strcat(log, next->content);
        if (next->next)
        {
          strcat(log, " ");
        }
      }
      free(currItemContent);
    }
  }
}
void write_result_in_file(logBase *firstLog)
{
  logBase *currLog = firstLog;
  FILE *fileOutPtr = fopen(R1Q2_file_out_path, "w");

  if (fileOutPtr)
  {
    while (currLog)
    {
      fprintf(fileOutPtr, "%s\n", currLog->content);
      currLog = currLog->next;
    }
    fclose(fileOutPtr);
  }
  else
  {
    puts("ops! file issues!:(");
  }
}
void free_str_memory_allocated(str **firstStr)
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
void free_logLine_memory_allocated(logBase **firstLog)
{
  logBase *currLog = *firstLog;
  logBase *prev = NULL;

  while (currLog)
  {
    prev = currLog;
    currLog = currLog->next;
    free(prev);
    prev = NULL;
  }
  *firstLog = NULL;
}