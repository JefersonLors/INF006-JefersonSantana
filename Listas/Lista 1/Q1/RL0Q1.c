/*
Instituto Federal da Bahia
Salvador - BA
Curso de Análise e Desenvolvimento de Sistemas
Disciplina: INF006 - Estrutura de Dados e Algoritmos
Professor: José Dihego

----- Dados do Aluno -----
Nome: Jeferson Leandro de Oliveira dos Reis Santana
email: 20212160060@ifba.edu.br
Matrícula: 20212160060
Semestre: 2023.1
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "RL0Q1.h"

// ESTRUTURA DE DADOS
struct Node
{
  float distance;
  float shortCut;
  struct Point *list;
  struct Node *next;
};

struct Point
{
  float *coordinates;
  float distanceFromOrigin;
  struct Point *next;
};

struct String
{
  char *string;
  struct String *next;
};

// APP
int main()
{
  NODE *points = get_lists_from_file_and_returns_float_dynamic_matriz(fileInPath);
  NODE *actList = points;

  while (actList != NULL)
  {
    actList->distance = calculate_distance_between_points(actList->list);
    actList->shortCut = calculate_shortCut(actList->list);
    calculate_distance_from_origin(actList->list);
    sort_point_list(actList->list);
    write_list_on_out_file(fileOutPath, actList->list, actList->distance, actList->shortCut);
    actList = actList->next;
  }

  /*DESCOMENTE PARA DEGUBAR*/
  // show_base_list_content(points);
  return EXIT_SUCCESS;
}
// CARREGA PRA MEMÓRIA TODOS OS PONTOS DE CADA LINHA
NODE *get_lists_from_file_and_returns_float_dynamic_matriz(const char *filesName)
{
  FILE *fileInPtr = fopen(filesName, "r");

  NODE *headBase = NULL;
  NODE *actBase = NULL;
  NODE *newBase = NULL;

  POINT *list = NULL;

  char line[MAX_SIZE_LINE];

  if (!fileInPtr)
  {
    return headBase;
  }
  else
  {
    while (fgets(line, MAX_SIZE_LINE, fileInPtr) != NULL)
    {
      line[strlen(line)] = '\0';
      list = get_line_and_returns_float_dynamic_list(line);

      if (headBase == NULL)
      {
        newBase = malloc(sizeof(NODE));
        newBase->list = list;
        newBase->next = NULL;
        headBase = newBase;
      }
      else
      {
        actBase = headBase;

        while (actBase->next != NULL)
        {
          actBase = actBase->next;
        }
        newBase = malloc(sizeof(NODE));
        newBase->list = list;
        newBase->next = NULL;
        actBase->next = newBase;
      }
    }
  }
  fclose(fileInPtr);

  /*DESCOMENTE PARA DEBUGAR*/
  // show_base_list_content(headBase);
  return headBase;
}
// CRIA UMA LISTA DE FLOATS COM AS COORDENADAS DA LINHA
POINT *get_line_and_returns_float_dynamic_list(char *line)
{
  STR *stringPointsList = get_string_line_and_returns_dynamic_string_list(line);

  POINT *headPoint = NULL;
  POINT *newPoint = NULL;
  POINT *actPoint = NULL;

  if (stringPointsList != NULL)
  {
    newPoint = malloc(sizeof(POINT));
    newPoint->coordinates = get_string_and_returns_float_array(stringPointsList->string);
    newPoint->next = NULL;
    headPoint = newPoint;

    stringPointsList = stringPointsList->next;

    while (stringPointsList != NULL)
    {
      actPoint = headPoint;

      while (actPoint->next != NULL)
      {
        actPoint = actPoint->next;
      }

      newPoint = malloc(sizeof(POINT));
      newPoint->coordinates = get_string_and_returns_float_array(stringPointsList->string);
      newPoint->next = NULL;
      actPoint->next = newPoint;
      stringPointsList = stringPointsList->next;
    }
  }
  else
  {
    return NULL;
  }
  /*DESCOMENTE PARA DEBUGAR*/
  // show_list_content(headPoint);

  return headPoint;
}
// CRIA UMA LISTA DE PONTOS AINDA EM STRINGS
STR *get_string_line_and_returns_dynamic_string_list(char *line)
{
  char *slice = NULL;
  char *sliceBackUp = NULL;

  float *points;

  STR *actPoint = NULL;
  STR *newPoint = NULL;
  STR *headPoint = NULL;

  // QUEBRA O PRIMEIRO ELEMENTO "Points"
  slice = strtok(line, " ");

  // SOBRESCREVE "Points" COM AS COORDENADAS DO PRIMEIRO PONTO
  slice = strtok(NULL, " ");

  // CRIA LISTA COM OS PONTOS AINDA COMO STRING
  if (slice != NULL)
  {
    newPoint = malloc(sizeof(STR));
    newPoint->string = slice;
    newPoint->next = NULL;
    headPoint = newPoint;

    slice = strtok(NULL, " ");

    while (slice != NULL)
    {
      actPoint = headPoint;

      while (actPoint->next != NULL)
      {
        actPoint = actPoint->next;
      }

      newPoint = malloc(sizeof(STR));
      newPoint->string = slice;
      newPoint->next = NULL;
      actPoint->next = newPoint;
      slice = strtok(NULL, " ");
    }
  }
  else
  {
    return NULL;
  }

  /*DESCOMENTE PARA DEBUGAR*/
  // show_str_list_content(headPoint);
  return headPoint;
}
// TRANSFORMA A STRING QUE REPRESENTA UM PONTO NUM VETOR DE FLOAT CONTENDO SUAS COORDENADAS
float *get_string_and_returns_float_array(char *numericString)
{
  char delimiterLeft = '(';
  char delimiterRight = ')';
  char delimiterCenter = ',';

  char *slice = numericString;
  char *sliceBackUp = NULL;
  char *garbage = NULL;

  float *coordenates = malloc(sizeof(float) * TAM_COORD);

  /// RETIRA CARACTERES ALFABETICOS DO ELEMENTO
  garbage = strchr(slice, delimiterLeft);
  garbage[0] = ' ';

  garbage = strchr(slice, delimiterRight);
  garbage[0] = ' ';

  garbage = strchr(slice, delimiterCenter);
  garbage[0] = ' ';

  // PEGA O PRIMEIRO PONTO E CONVERTE PRA FLOAT
  slice = strtok(slice, " ");
  coordenates[0] = atof(slice);

  // PEGA O SEGUNDO PONTO E CONVERTE PRA FLOAT
  slice = strtok(NULL, " ");
  coordenates[1] = atof(slice);

  return coordenates;
}
// CALCULA A SOMA DA DISTÂNCIA ENTRE OS PONTOS DE UMA LISTA
float calculate_distance_between_points(POINT *list)
{
  POINT *pointA = list;
  POINT *pointB = NULL;
  float distance = 0;

  while (pointA->next != NULL)
  {
    pointB = pointA->next;
    distance += calculate_distance_between_two_points(
        pointA->coordinates[0],
        pointA->coordinates[1],
        pointB->coordinates[0],
        pointB->coordinates[1]);
    pointA = pointA->next;
  }
  return distance;
}
// CALCULA A DISTÂNCIA ENTRE DOIS PONTOS QUAISQUER
float calculate_distance_between_two_points(float Xa, float Ya, float Xb, float Yb)
{
  float distance = sqrt(pow((Xb - Xa), 2) + pow((Yb - Ya), 2));
  return distance;
}
// CALCULAR A DISTÂNCIA ENTRE O PRIMEIRO E O ÚLTIMO PONTO DE UMA LISTA
float calculate_shortCut(POINT *list)
{
  POINT *point = list;
  float *firstPoint = point->coordinates;
  float *lastPoint = NULL;

  while (point->next != NULL)
  {
    point = point->next;
  }
  lastPoint = point->coordinates;

  return calculate_distance_between_two_points(
      firstPoint[0],
      firstPoint[1],
      lastPoint[0],
      lastPoint[1]);
}
// CALCULA A DISTÂNCIA ENTRE OS PONTOS DE UMA LISTA E A ORIGEM
void calculate_distance_from_origin(POINT *list)
{
  POINT *point = list;

  while (point != NULL)
  {
    point->distanceFromOrigin = calculate_distance_between_point_and_origin(
        point->coordinates[0],
        point->coordinates[1]);
    point = point->next;
  }
}
// CALCULA A DISTÂNCIA ENTRE UM PONTO E A ORIGEM
float calculate_distance_between_point_and_origin(float x, float y)
{
  return calculate_distance_between_two_points(.0, .0, x, y);
}
// ORDENA CRESCENTEMENTE OS PONTOS DE UMA LISTA
void sort_point_list(POINT *list)
{
  POINT *actPoint = list;
  POINT *tempPoint = NULL;

  float *coordenatesbackUp = NULL;
  float distanceFromOrignBackUp = 0;

  while (actPoint != NULL)
  {
    tempPoint = actPoint;

    while (tempPoint->next != NULL)
    {
      if (tempPoint->distanceFromOrigin > tempPoint->next->distanceFromOrigin)
      {
        coordenatesbackUp = tempPoint->next->coordinates;
        distanceFromOrignBackUp = tempPoint->next->distanceFromOrigin;

        tempPoint->next->coordinates = tempPoint->coordinates;
        tempPoint->next->distanceFromOrigin = tempPoint->distanceFromOrigin;

        tempPoint->coordinates = coordenatesbackUp;
        tempPoint->distanceFromOrigin = distanceFromOrignBackUp;
      }
      tempPoint = tempPoint->next;
    }
    actPoint = actPoint->next;
  }
}
// ESCREVE LISTAS ORDENADAS EM ARQUIVO
void write_list_on_out_file(const char *filesName, POINT *list, float distance, float shortCut)
{
  FILE *fileOutPtr = fopen(filesName, "a+");

  POINT *actPoint = list;

  fprintf(fileOutPtr, "points ");
  while (actPoint != NULL)
  {
    fprintf(fileOutPtr, "(%.2f, %.2f) ", actPoint->coordinates[0], actPoint->coordinates[1]);
    actPoint = actPoint->next;
  }
  fprintf(fileOutPtr, "distance %.2f shortcut %.2f\n", distance, shortCut);
  fclose(fileOutPtr);
}
// MOSTRA CONTEÚDO DE LISTA DE NODE NO TERMINAL
void show_base_list_content(NODE *base)
{
  NODE *actBase = base;

  while (actBase != NULL)
  {
    POINT *actList = actBase->list;

    show_list_content(actList);
    printf("\ndistance: %.2f\n", actBase->distance);
    printf("shortCut: %.2f\n", actBase->shortCut);
    putchar('\n');

    actBase = actBase->next;
  }
}
// MOSTRA CONTEÚDO DE LISTA DE POINT NO TERMINAL
void show_list_content(POINT *list)
{
  POINT *actPoint = list;

  printf("points: ");
  while (actPoint != NULL)
  {
    printf("(%.1f, %.1f)\t", actPoint->coordinates[0], actPoint->coordinates[1]);
    actPoint = actPoint->next;
  }
  putchar('\n');
}
// MOSTRA CONTEÚDO DE LISTA DE STR NO TERMINAL 
void show_str_list_content(STR *strList)
{
  STR *actPoint = strList;

  printf("points: ");
  while (actPoint != NULL)
  {
    printf("%s\t", actPoint->string);
    actPoint = actPoint->next;
  }
  putchar('\n');
}