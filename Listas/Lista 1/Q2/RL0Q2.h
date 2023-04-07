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
#ifndef RL0Q2_H_INCLUDED
#define RL0Q2_H_INCLUDED

/// MACROS
#define MAX_SIZE_LINE 255
#define MAX_ELEMENT_SIZE 10
#define COORD_SIZE 2

/// PATHS
const char *fileInPath = "L0Q2.in";
const char *fileOutPath = "L0Q2.out";

/// TIPOS
typedef struct String STR;
typedef struct Floating FLOAT;
typedef struct Interger INT;
typedef struct Point POINT;
typedef struct Node NODE;
typedef struct Item ITEM;

/// FUNÇÕES DE CRIAÇÃO DE ESTRUTURAS DE DADOS
NODE *get_items_from_file_and_returns_dynamic_typed_item_matrix(const char *fileName);
STR *break_line_in_dynamic_str_list(char *line);
ITEM *create_dynamic_item_matrix(const char *fileName);

/// FUNÇÕES DE TIPAGEM
NODE *type_items(STR *list);

/// FUNÇÕES DE OPERAÇÕES SOBRE PONTOS
float *extract_point_from_string(char *stringPoint);
float calculate_distance_from_origin(float X, float Y);

/// FUNÇÕES QUE FAZEM VERIFICAÇÃO DE TIPO
bool is_string(char *string);
bool is_point(char *string);
bool is_interger(char *string);
bool is_floating(char *string);
bool is_number(char *string);

/// FUNÇÕES QUE TESTAM AS FUNÇÕES DE TIPAGEM
void test_data_type_funtions(void);

/// FUNÇÕES DE CONVERSÃO
POINT *to_point(char *string);
INT *to_interger(char *string);
FLOAT *to_floating(char *string);
STR *to_string(char *string);

/// FUNÇÕES DE ORDENAÇÃO
void sort_node(NODE *node);
void point_selection_sort(POINT *initList);
void string_selection_sort(STR *initList);
void interger_selection_sort(INT *initList);
void floating_selection_sort(FLOAT *initList);

/// FUNÇÕES DE ESCRITA EM ARQUIVO
void write_node_on_file(NODE *node);

/// FUNÇÕES DE DEPURAÇÃO DE EM TERMINAL
void show_node_list_content(NODE *initNode);
void show_str_list_content(STR *initStr);
void show_item_list_content(ITEM *initItem);

#endif