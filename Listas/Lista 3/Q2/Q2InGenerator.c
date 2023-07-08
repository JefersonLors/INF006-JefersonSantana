#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Q2InGenerator.h"

const char *R2Q2_file_in = "L2Q2.in";

void L2Q2_in_generator()
{
  srand(time(NULL));
  _str *start = create_line_list();

  if (!write_in_file(start))
  {
    printf("\nops!generate issues in L2Q1.in!\n");
  }
  else
  {
    delete_line_list(&start);
  }
}
void delete_line_list(_str **start)
{
  _str *curr = *start;
  _str *prev = NULL;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
    free(curr);
    curr = NULL;
  }
  start = NULL;
}
bool write_in_file(_str *start)
{
  FILE *fileResultPtr = fopen(R2Q2_file_in, "w");

  _str *curr = start;

  if (fileResultPtr)
  {
    while (curr)
    {
      fprintf(fileResultPtr, "%s", curr->line);
      curr = curr->next;
    }
    fclose(fileResultPtr);
    return true;
  }
  return false;
}
_str *create_line_list()
{
  _str *first = NULL;
  _str *curr = NULL;
  _str *new = NULL;
  _str *last = NULL;

  int quantyLine = MIN_QTY_LINE + rand() % MAX_QTY_LINE;

  if (quantyLine > 0)
  {
    new = (_str *)malloc(sizeof(_str));
    new->line = generate_string_interger_list();
    new->next = NULL;
    first = new;
    last = new;

    quantyLine--;
    while (quantyLine > 0)
    {
      new = (_str *)malloc(sizeof(_str));
      new->line = generate_string_interger_list();
      new->next = NULL;

      curr = last;
      curr->next = new;
      last = new;

      quantyLine--;
    }
  }
  return first;
}

char *generate_string_interger_list()
{
  int number = 0;
  char sNumber[10];
  char *line = malloc(sizeof(char) * _MAX_SIZE_LINE);
  int quanty = 1 + rand() % MAX_QTY_NUMBERS;

  strcpy(line, "");

  while (quanty > 0)
  {
    number = 0 + rand() % 100;
    number *= (toNegative() ? -1 : 1);
    sprintf(sNumber, "%d ", number);
    strcat(line, sNumber);
    quanty--;
  }
  line[strlen(line) - 1] = '\n';

  return line;
}
bool toNegative()
{
  int toNegative = 0 + rand() % 10;
  return (toNegative > 8 ? true : false);
}