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

#include <stdio.h>

#ifndef RL0Q1_H_INCLUDED
#define RL0Q1_H_INCLUDED

#define MAX_SIZE_LINE 255
#define MAX_ELEMENT_SIZE 10
#define TAM_COORD 2

const char *fileInPath = "L0Q1.in";
const char *fileOutPath = "L0Q1.out";

typedef struct Base BASE;
typedef struct List LIST;
typedef struct String_List STR_LIST;

BASE *get_lists_from_file_and_returns_float_dynamic_matriz( const char*fileInPath );
LIST *get_line_and_returns_float_dynamic_list( char*line );
STR_LIST *get_string_line_and_returns_dynamic_string_list( char*line );
float *get_string_and_returns_float_array( char* );
float calculate_distance_between_points( LIST *);
float calculate_distance_between_two_points( float Xa, float Ya, float Xb, float Yb );
void calculate_distance_from_origin( LIST* );
float calculate_distance_between_point_and_origin( float X, float Y );
float calculate_shortCut( LIST * );
void sort_point_list(LIST*);
void write_list_on_out_file( const char*filesName, LIST *list, float distance, float shortCut );

#endif