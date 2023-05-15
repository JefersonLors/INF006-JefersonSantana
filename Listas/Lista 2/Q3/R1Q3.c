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
  strV *fistStrV = create_strV_list(firstStr);
  // int i = 1;
  // while( firstStr ){
  //   printf("line[%d] -> %s\n", i, firstStr->content);
  //   i++;
  //   firstStr = firstStr->next;
  // }

  puts("end run!");
  return EXIT_SUCCESS;
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

  remove_alfabetic_non_numeric_characters_from_string(new->intStrList);
  remove_alfabetic_non_numeric_characters_from_string(new->floatStrList);

  return new;
}
void remove_alfabetic_non_numeric_characters_from_string(char *string)
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
