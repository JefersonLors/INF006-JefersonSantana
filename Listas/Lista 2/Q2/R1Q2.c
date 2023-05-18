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

  puts("END RUN!");

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
    newLogLine = new_logBase();
    newLogLine->content = create_log_line(currNameList->content);
    newLogLine->next = NULL;

    firstLogLine = newLogLine;
    lastLogLine = newLogLine;

    currNameList = currNameList->next;

    while (currNameList)
    {
      newLogLine = new_logBase();
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
      newName = new_str();
      newName->content = new_char_vector(strlen(strList));
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
        newName = new_str();
        newName->content = new_char_vector(strlen(strList));
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
          newName = new_str();
          newName->content = new_char_vector(strlen(strList));

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
      newStr = new_str();
      newStr->content = new_char_vector( MAX_SIZE_LINE);
      strcpy(newStr->content, line);
      newStr->next = NULL;
      newStr->prev = NULL;

      firstStr = newStr;
      lastStr = newStr;

      while (fgets(line, MAX_SIZE_LINE, fileInPtr))
      {
        line[strlen(line) - 1] = '\0';
        newStr = new_str();
        newStr->content = new_char_vector(MAX_SIZE_LINE);
        strcpy(newStr->content, line);
        newStr->next = NULL;
        newStr->prev = NULL;
        
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
    newLogLine = new_char_vector( MAX_SIZE_LINE);
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
      char *currItemContent = new_char_vector(MIN_NAME_SIZE);

      strcpy(currItemContent, currItem->content);

      if (strcmp(prev->content, currItemContent) > 0)
      {
        while (prev && strcmp(prev->content, currItemContent) > 0)
        {
          shift_list_content(prev, next);

          next = prev;
          popI++;
          prev = prev->prev;
        }
        if (prev)
        {
          prev->next->content = currItemContent;
        }
        else
        {
          next->content = currItemContent;
        }
        char *popS = new_char_vector(STRING_NUMBER_SIZE);
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
void shift_list_content(str *prev, str *next)
{
  next->content = prev->content;
}
void write_result_in_file(logBase *firstLog)
{
  if (!firstLog)
  {
    printf("empty content! :[\n");
    return;
  }

  logBase *currLog = firstLog;
  FILE *fileOutPtr = fopen(R1Q2_file_out_path, "w");

  if (!fileOutPtr)
  {
    puts("ops! file issues!:(");
    return;
  }

  while (currLog)
  {
    fprintf(fileOutPtr, "%s\n", currLog->content);
    currLog = currLog->next;
  }
  fclose(fileOutPtr);
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
logBase *new_logBase()
{
  return (logBase *)malloc(sizeof(logBase));
}
strBase *new_strBase()
{
  return (strBase *)malloc(sizeof(strBase));
}
str *new_str()
{
  return (str *)malloc(sizeof(str));
}
char *new_char_vector(int size)
{
  return (char *)malloc(sizeof(char) * size);
}