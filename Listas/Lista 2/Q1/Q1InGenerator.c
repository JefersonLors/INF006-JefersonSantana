#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Q1InGenerator.h"

const char *R1Q1_file_in = "L1Q1.in";

void L1Q1_in_generator()
{
  srand(time(NULL));
  _str *start = create_line_list();

  if (!write_in_file(start))
  {
    printf("\nops!generate issues in L1Q1.in!\n");
  }
  else
  {
    delete_line_list(&start);
  }
}
void delete_line_list(_str **start)
{
  _str *act = *start;
  _str *prev = NULL;

  while(act ){
    prev = act;
    act = act->next;
    free(act);
    act = NULL;
  }
  start = NULL;
}
bool write_in_file(_str *start)
{
  FILE *fileResultPtr = fopen(R1Q1_file_in, "w");

  _str *act = start;

  if (fileResultPtr)
  {
    while (act)
    {
      fprintf(fileResultPtr, "%s", act->line);
      act = act->next;
    }
    fclose(fileResultPtr);
    return true;
  }
  return false;
}
_str *create_line_list()
{
  _str *first = NULL;
  _str *act = NULL;
  _str *new = NULL;
  _str *last = NULL;

  int quantyLine = MIN_QTY_LINE + rand() % MAX_QTY_LINE;
  int quantyList = 0;

  if (quantyLine > 0)
  {
    quantyList = 0 + rand() % MAX_QTY_LIST;
    new = malloc(sizeof(_str));
    new->line = create_line(quantyList);
    new->next = NULL;
    first = new;
    last = new;

    quantyLine--;
    while (quantyLine > 0)
    {
      quantyList = 0 + rand() % MAX_QTY_LIST;
      new = malloc(sizeof(_str));
      new->line = create_line(quantyList);
      new->next = NULL;

      act = last;
      act->next = new;
      last = new;

      quantyLine--;
    }
  }
  return first;
}
char *create_line(int qty)
{
  char *line = malloc(sizeof(char) * _MAX_SIZE_LINE);
  int q = 0;
  strcpy(line, "");
  while (q < qty)
  {
    strcat(line, generate_naturals_number_list());
    q++;
  }
  if (qty)
  {
    strcat(line, "\n");
  }
  return line;
}
char *generate_naturals_number_list()
{
  int number = 0;
  char sNumber[5];
  char *line = malloc(sizeof(char) * 50);
  int quanty = 0 + rand() % 7;

  strcpy(line, "start ");
  while (quanty > 0)
  {
    number = rand() % 100;
    sprintf(sNumber, "%d ", number);
    strcat(line, sNumber);
    quanty--;
  }

  return line;
}
