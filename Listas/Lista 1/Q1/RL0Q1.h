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

///MACROS
#define MAX_SIZE_LINE 255
#define MAX_ELEMENT_SIZE 10
#define TAM_COORD 2

///PATHS
const char *fileInPath = "L0Q1.in";
const char *fileOutPath = "L0Q1.out";

///TIPOS
typedef struct Node NODE;
typedef struct Point POINT;
typedef struct String STR;

/// FUNÇÕES DE CRIAÇÃO DE ESTRUTURAS DE DADOS
NODE *get_lists_from_file_and_returns_float_dynamic_matriz( const char*fileInPath );
POINT *get_line_and_returns_float_dynamic_list( char*line );
STR *get_string_line_and_returns_dynamic_string_list( char*line );

///FUNÇÕES DE CONVERSÃO
float *get_string_and_returns_float_array( char* );

///FUNÇÕES DE ARITMÉTICA SOBRE PONTOS
float calculate_distance_between_points( POINT *);
float calculate_distance_between_two_points( float Xa, float Ya, float Xb, float Yb );
void calculate_distance_from_origin( POINT* );
float calculate_distance_between_point_and_origin( float X, float Y );
float calculate_shortCut( POINT * );

///FUNÇÕES DE ORDENAÇÃO DE PONTOS
void sort_point_list(POINT*);

///FUNÇÕES DE ESCRITA EM ARQUIVO
void write_list_on_out_file( const char*filesName, POINT *list, float distance, float shortCut );

///FUNÇÕES DE DEPURAÇÃO NO TERMINAL
void show_base_list_content( NODE *base );
void show_list_content( POINT *list );
void show_str_list_content( STR_LIST *strList );

#endif