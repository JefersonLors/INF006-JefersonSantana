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
  _str *firstLine = create_name_list_to_in();

  if (!write_in_file(firstLine))
  {
    printf("\nops!generate issues in L1Q2.in!\n");
  }
  else
  {
    delete_line_list(&firstLine);
  }
}
_str *create_name_list_to_in()
{
  _str *first = NULL;
  _str *curr = NULL;
  _str *new = NULL;
  _str *last = NULL;

  int sizeLine = MIN_QTY_LINE + rand() % MAX_QTY_LINE;
  printf("%d - %d -> %d\n", MIN_QTY_LINE, MAX_QTY_LINE, sizeLine);
  int i = 0;
  int quantyName = 0;

  if (sizeLine > 0)
  {
    quantyName = 1 + rand() % MAX_QTY_NAME;
    new = malloc(sizeof(_str));
    new->line = create_line(quantyName);
    new->next = NULL;
    first = new;
    last = new;

    i++;
    while (i < sizeLine )
    {
      quantyName = 1 + rand() % MAX_QTY_NAME;
      new = malloc(sizeof(_str));
      new->line = create_line(quantyName);
      new->next = NULL;

      curr = last;
      curr->next = new;
      last = new;

      i++;
    }
  }
  return first;
}
bool write_in_file(_str *firstLine)
{
  FILE *fileResultPtr = fopen(R1Q2_file_in, "w");

  _str *curr = firstLine;
  int i = 1;
  if (fileResultPtr)
  {
    while (curr)
    {
      fprintf(fileResultPtr, "%s", curr->line);
      fprintf(fileResultPtr, "%c", '\n');
      curr = curr->next;
    }
    fclose(fileResultPtr);
    return true;
  }
  return false;
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
  line[strlen(line)] = '\0';

  return line;
}
void delete_line_list(_str **firstLine)
{
  _str *curr = *firstLine;
  _str *prev = NULL;

  while(curr ){
    prev = curr;
    curr = curr->next;
    free(curr);
    curr = NULL;
  }
  *firstLine = NULL;
}