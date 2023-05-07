#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Q2InGenerator.h"

const char *R1Q2_file_in = "L1Q2.in";

const char *names[NAME_LIST_SIZE] = {
    "Maria", "João", "Pedro", "Ana", "Bruno", "Catarina", "Eduardo", "Fernanda", "Gustavo", "Isabel",
    "Joaquim", "Larissa", "Miguel", "Natália", "Otávio", "Patrícia", "Rafael", "Sara", "Thiago", "Vanessa",
    "Xavier", "Yasmin", "Zara", "Felipe", "Lucas", "Camila", "Daniel", "Gabriel", "Ricardo", "Natalia",
    "Vitor", "Eva", "Isadora", "Fábio", "Tatiana", "Diego", "Paula", "Marcelo", "Carolina", "Leandro",
    "Luana", "Roberto", "Lorena", "Luciana", "Mariana", "Anderson", "Aline", "Rita", "Marina", "Luiz", "Renata", "Simone" };

void L1Q2_in_generator()
{
  srand(time(NULL));
  _str *start = create_name_list();

  if (!write_in_file(start))
  {
    printf("\nops!generate issues in L1Q2.in!\n");
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
  FILE *fileResultPtr = fopen(R1Q2_file_in, "w");

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
_str *create_name_list()
{
  _str *first = NULL;
  _str *act = NULL;
  _str *new = NULL;
  _str *last = NULL;

  int sizeLine = MIN_QTY_LINE + rand() % MAX_QTY_LINE;
  int quantyName = 0;

  if (sizeLine > 0)
  {
    quantyName = 1 + rand() % MAX_QTY_NAME;
    new = malloc(sizeof(_str));
    new->line = create_line(quantyName);
    new->next = NULL;
    first = new;
    last = new;

    sizeLine--;
    while (sizeLine > 0)
    {
      quantyName = 1 + rand() % MAX_QTY_NAME;
      new = malloc(sizeof(_str));
      new->line = create_line(quantyName);
      new->next = NULL;

      act = last;
      act->next = new;
      last = new;

      sizeLine--;
    }
  }
  return first;
}
char *create_line(int qty)
{
  char *line = malloc(sizeof(char) * _MAX_SIZE_LINE);
  int q = 0;
  int pos = 0;

  strcpy(line, "");
  
  while (q < qty)
  {
    pos = 0 + rand() % NAME_LIST_SIZE;
    strcat(line, names[pos]);
    if( q + 1 < qty){
      strcat(line, " ");
    }
    q++;
  }
  line[strlen(line)] = '\n';

  return line;
}
