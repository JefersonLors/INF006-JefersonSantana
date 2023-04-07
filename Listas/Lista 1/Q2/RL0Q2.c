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
#include <ctype.h>
#include "RL0Q2.h"

///ESTRUTURAS DE DADOS 
struct String{
  char *value;
  struct String *next;
};

struct Point{
  float *value;
  float distanceFromOrigin;
  struct Point *next;
};

struct Interger{
  int value;
  struct Interger *next;
};

struct Floating{
  float value;
  struct Floating *next; 
};

struct Node{
  struct String *string;
  struct Interger *interger;
  struct Floating *floating;
  struct Point *point;
  struct Node *next;
};

struct Item{
  struct String *list;
  struct Item *next;
};

///APP
int main( ){
  NODE *firstNode = get_items_from_file_and_returns_dynamic_typed_item_matrix(fileInPath);
  NODE *actNode = firstNode;

  while( actNode ){
    sort_node(actNode);
    write_node_on_file(actNode);
    actNode = actNode->next;
  }
  /*DESCOMENTE PARA DEBUGAR*/
  // show_node_list_content(firstNode);
  return EXIT_SUCCESS;
}
///RECUPERA OS ITENS DO ARQUIVO E OS COLOCA NUMA MATRIZ DINÂMICA, AGRUPADOS PODE TIPO
NODE *get_items_from_file_and_returns_dynamic_typed_item_matrix( const char *fileName ){
  NODE *firstNode = NULL; 
  NODE *newNode = NULL; 
  NODE *actNode = NULL; 
  NODE *lastNode = NULL;

  ITEM *newListItem = create_dynamic_item_matrix(fileName);
  ITEM *actListItem = newListItem;
  
  if( newListItem == NULL ){
    return firstNode;
  }else{
    newNode = malloc(sizeof(NODE));
    newNode = type_items(newListItem->list);
    newNode->next = NULL;

    if( newNode == NULL ){
        return firstNode;
    }
    firstNode = newNode;
    lastNode = newNode;
    actListItem = actListItem->next; 

    while( actListItem != NULL ){
      newNode = malloc(sizeof(NODE));
      newNode = type_items(actListItem->list);
      newNode->next = NULL;
      actNode = lastNode;
      actNode->next = newNode;
      lastNode = newNode;
  
      actListItem = actListItem->next; 
    }
  }
  /*DESCOMENTE PARA DEBUGAR*/
  // show_node_list_content( firstNode );
  return firstNode;
}
///QUEBRA OS ITENS DE UMA LINHA EM STRINGS PARA UMA LISTA ENCADEADA
STR *break_line_in_dynamic_str_list(char *line){
  STR *firstString = NULL;
  STR *lastString = NULL;
  STR *actString = NULL;
  STR *newString = NULL;

  char *word = NULL;
  char *delimiter = " ";
  char *newWord = malloc(sizeof(char)*20);

  word = strtok(line, delimiter);
  strcpy(newWord, word);

  if( !word ){
    return firstString;
  }else{
    newString = malloc(sizeof(STR));
    newString->value = newWord;
    newString->next = NULL;
    firstString = newString;
    lastString = newString;
    
    word = strtok(NULL, delimiter);

    while( word ){
      newWord = NULL;
      newWord = malloc(sizeof(char)*20);
      strcpy(newWord, word);

      newString = malloc(sizeof(STR));
      newString->value = newWord;
      newString->next = NULL;
      actString = lastString;
      actString->next = newString;
      lastString = newString;

      word = strtok( NULL, delimiter );
    }
  }
  /*DESCOMENTE PARA DEBUGAR*/
  // show_str_list_content(firstString);
  return firstString;
}
///CRIA RECUPERA ITENS DE UMA MESMA LINHA NUM ARQUIVO AINDA COMO STRINGS
ITEM *create_dynamic_item_matrix(const char *fileName ){
  FILE *fileInPtr = fopen(fileName, "r");
  ITEM *firstItem = NULL;
  ITEM *lastItem = NULL;
  ITEM *newItem = NULL;
  ITEM *actItem = NULL;
    
  char line[MAX_SIZE_LINE];

  if( !fileInPath ){
    return firstItem;

  } else {
    fgets(line, MAX_SIZE_LINE, fileInPtr);
    line[strlen(line)-1] = '\0';

    if( line ){
      newItem = malloc(sizeof(ITEM));
      newItem->list = break_line_in_dynamic_str_list(line);
      newItem->next = NULL;
      firstItem = newItem;
      lastItem = newItem;
      
      while( fgets(line, MAX_SIZE_LINE, fileInPtr) != NULL ){
        line[strlen(line)-1] = '\0';
        newItem = malloc(sizeof(ITEM));
        newItem->list = break_line_in_dynamic_str_list(line);
        newItem->next = NULL;
        actItem = lastItem;
        actItem->next = newItem;
        lastItem = newItem; 
      }
    }
  }
  /*DESCOMENTE PARA DEBUGAR*/
  // show_item_list_content(firstItem);
  return firstItem;
}
///TIPA OS ITENS DA LISTA 
NODE *type_items( STR *itemList ){
  NODE *node = NULL;
  STR *actItem = NULL;

  STR *firstString = NULL;
  STR *lastString = NULL;
  STR *actString = NULL;
  STR *newString = NULL;

  POINT *firstPoint = NULL;
  POINT *lastPoint = NULL;
  POINT *actPoint = NULL;
  POINT *newPoint = NULL;

  INT *firstInterger = NULL;
  INT *lastInterger = NULL;
  INT *actInterger = NULL;
  INT *newInterger = NULL;

  FLOAT *firstFloating = NULL;
  FLOAT *lastFloating = NULL;
  FLOAT *actFloating = NULL;
  FLOAT *newFloating = NULL; 

  if( !itemList ){
    return node;
  }else{
    node = malloc(sizeof(NODE));
    actItem = itemList;
    while( actItem != NULL ){
      if( is_string(actItem->value)){
        newString =  malloc(sizeof(STR));
        newString = to_string(actItem->value);
        newString->next = NULL;

        if( firstString == NULL ){
          firstString = newString;
          lastString = newString;
        }else{
          actString = lastString;
          actString->next = newString;
          lastString = newString;
        }
        actItem = actItem->next;
        continue;
      }
      if( is_interger(actItem->value) ){
        newInterger = malloc(sizeof(INT));
        newInterger = to_interger(actItem->value);
        newInterger->next = NULL;

        if( firstInterger == NULL ){
          firstInterger = newInterger;
          lastInterger = newInterger;
        }else{
          actInterger = lastInterger;
          actInterger->next = newInterger;
          lastInterger = newInterger;
        }
        actItem = actItem->next;
        continue;
      }
      if( is_floating(actItem->value)){
        newFloating = malloc(sizeof(FLOAT));
        newFloating = to_floating(actItem->value);
        newFloating->next = NULL;
  	    
        if( firstFloating == NULL ){
          firstFloating = newFloating;
          lastFloating = newFloating;
        }else{
          actFloating = lastFloating;
          actFloating->next = newFloating;
          lastFloating = newFloating;
        }
        actItem = actItem->next;
        continue;
      }
      if( is_point(actItem->value) ){
        newPoint = malloc(sizeof(POINT));
        newPoint = to_point(actItem->value);
        newPoint->next = NULL;

        if( firstPoint == NULL ){
          firstPoint = newPoint;
          lastPoint = newPoint;
        }else{
          actPoint = lastPoint;
          actPoint->next = newPoint;
          lastPoint = newPoint;
        }
        actItem = actItem->next;
        continue;
      }
      actItem = actItem->next;
    }
  }
  node->floating = firstFloating;
  node->interger = firstInterger;
  node->point = firstPoint;
  node->string = firstString;
  node->next = NULL;

  /*DESCOMENTE PARA DEBUGAR*/
  // show_node_list_content( node );
  return node;
}
//VERIFICA SE O ITEM(STRING DA LISTA) É UMA STRING
bool is_string( char *string ){
  for( int i = 0; string[i] != '\0'; i++ ){
    if( !isalpha(string[i]) ){
      return false;
    }
  }
  return true;
}
//VERIFICA SE O ITEM(STRING DA LISTA) É UM PONTO
bool is_point( char *string ){
  if( is_string(string) ){
      return false;
  }
  
  int i = 0;
  if( string[i] != '(' ){
    return false;
  }
  i++;
  while( string[i + 1] != '\0' ){
    if( !isdigit(string[i]) && 
    (string[i] != ',' && 
    string[i] != '.' && 
    string[i] != '-') ){
      return false;
    }
    i++;
  }
  if( string[i] != ')' ){
    return false;
  }
  return true;
}
//VERIFICA SE O ITEM(STRING DA LISTA) É UM INTEIRO
bool is_interger( char *string ){
  if( is_string(string) || is_point(string) || !is_number(string) ){
      return false;
  }

  float numberFloat = atof(string);
  int numberInt = numberFloat;

  if( numberFloat != numberInt ){
    return false;
  }

  return true;
}
//VERIFICA SE O ITEM(STRING DA LISTA) É UM FLOAT
bool is_floating( char *string ){
  if(  is_interger(string) || 
  is_string(string) || 
  is_point(string) || 
  !is_number(string) ){
      return false;
  }
  return true;
}
//VERIFICA SE ITEM(STRING DA LISTA) É UM NÚMERO
bool is_number(char *string ){
  int i = 0;
  while(string[i] != '\0'){
    if( !isdigit(string[i]) && string[i] != '.' && string[i] != '-' ){
      return false;
    }
    i++;
  }
  return true;
}
///CONVERTE UM ITEM NUM ELEMENTO POINT DA LISTA ENCADEADA PRINCIPAL
POINT *to_point( char *string ){
  POINT *node = malloc(sizeof(POINT));
  node->value = extract_point_from_string(string);
  node->distanceFromOrigin = calculate_distance_from_origin(node->value[0], node->value[1]);
  node->next = NULL;
  return node;
}
///CONVERTE UM ITEM NUM ELEMENTO INT DA LISTA ENCADEADA PRINCIPAL
INT *to_interger( char *string ){
  INT *node = malloc(sizeof(INT));
  node->value = atoi(string);
  node->next = NULL;
  return node;
}
///CONVERTE UM ITEM NUM ELEMENTO FLOAT DA LISTA ENCADEADA PRINCIPAL
FLOAT *to_floating( char *string ){
  FLOAT *node = malloc(sizeof(FLOAT));
  node->value = atof(string);
  node->next = NULL;
  return node;
}
///CONVERTE STRING NUM ELEMENTO STR DA LISTA ENCADEADA PRINCIPAL
STR *to_string( char *string ){
  STR *node = malloc(sizeof(STR));
  node->value = string;
  node->next = NULL;
  return node;
}
///EXTRAI A COORDENADAS DE UMA STRING DE PONTO
float *extract_point_from_string( char *stringPoint ){
    char delimiterLeft = '(';
    char delimiterRight = ')';
    char delimiterCenter = ',';

    char *slice = stringPoint;
    char *sliceBackUp = NULL;
    char *garbage = NULL;

    float *coordenates = malloc(sizeof(float)*COORD_SIZE);

    /// RETIRA CARACTERES ALFABETICOS DO ELEMENTO
    garbage = strchr(slice, delimiterLeft);
    garbage[0] = ' ';
 
    garbage = strchr(slice, delimiterRight);
    garbage[0] = ' ';
 
    garbage = strchr(slice, delimiterCenter);
    garbage[0] = ' ';
 
    //PEGA O PRIMEIRO PONTO E CONVERTE PRA FLOAT
    slice = strtok(slice, " ");
    coordenates[0] = atof(slice);

    //PEGA O SEGUNDO PONTO E CONVERTE PRA FLOAT
    slice = strtok(NULL, " ");
    coordenates[1] = atof(slice);

    return coordenates;
}
///CALCULA A DISTÂNCIA ENTRA UM PONTO E A ORIGEM
float calculate_distance_from_origin( float X, float Y ){
    float distance = sqrt( pow((X - 0), 2) + pow((Y - 0), 2) );
    return distance;
}
///ORDENA OS ITENS CONTIDOS NO NODE
void sort_node( NODE *node ){
  point_selection_sort(node->point);
  string_selection_sort(node->string);
  interger_selection_sort(node->interger);
  floating_selection_sort(node->floating);
}
///ORDENA LISTA DE PONTOS
void point_selection_sort( POINT *initList ){
  POINT *actPoint = initList;
  POINT *nextPoint = NULL; 

  float *coordenatesTemp = NULL;
  float distFromOriginTemp = .0;

  while( actPoint->next ){
    nextPoint = actPoint->next;

    while( nextPoint ){
      if( actPoint->distanceFromOrigin > nextPoint->distanceFromOrigin ){
        coordenatesTemp = nextPoint->value;
        distFromOriginTemp = nextPoint->distanceFromOrigin;

        nextPoint->value = actPoint->value;
        nextPoint->distanceFromOrigin = actPoint->distanceFromOrigin;

        actPoint->value = coordenatesTemp;
        actPoint->distanceFromOrigin = distFromOriginTemp;
      }
      nextPoint = nextPoint->next;
    }
    actPoint = actPoint->next;
  }
}
///ORDENA LISTA DE STRINGS
void string_selection_sort( STR *initList ){
  STR *actStr = initList;
  STR *nextStr = NULL;

  char *strTemp = NULL;

  while( actStr->next ){
    nextStr = actStr->next;

    while( nextStr ){
      if( strcmp( actStr->value, nextStr->value ) > 0 ){
        strTemp = nextStr->value;
        nextStr->value = actStr->value;
        actStr->value = strTemp;
      }
      nextStr = nextStr->next;
    }
    actStr = actStr->next;
  }
}
///ORDENA LISTA DE INTEIROS
void interger_selection_sort( INT *initList ){
  INT *actInt = initList;
  INT *nextInt = NULL;

  int intTemp = 0;

  while( actInt->next ){
    nextInt = actInt->next;

    while( nextInt ){
      if( actInt->value > nextInt->value ){
        intTemp = nextInt->value;
        nextInt->value = actInt->value;
        actInt->value = intTemp;
      }
      nextInt = nextInt->next;
    }
    actInt = actInt->next;
  }
}
///ORDENA LISTA DE FLOATS
void floating_selection_sort( FLOAT *initList ){
  FLOAT *actFloat = initList;
  FLOAT *nextFloat = NULL;

  int floatTemp = 0;

  while( actFloat->next ){
    nextFloat = actFloat->next;

    while( nextFloat ){
      if( actFloat->value > nextFloat->value ){
        floatTemp = nextFloat->value;
        nextFloat->value = actFloat->value;
        actFloat->value = floatTemp;
      }
      nextFloat = nextFloat->next;
    }
    actFloat = actFloat->next;
  }
}
///ESCREVE A LISTA DE ELEMENTOS SEPARADAS POR TIPO 
///E ORDENADAS CRESCENTEMENTE NO ARQUIVO DE SAÍDA
void write_node_on_file( NODE *node ){
  FILE *fileOutPtr = fopen( fileOutPath, "a+");

  INT *nodeInts = node->interger; 
  INT *actInt = nodeInts;

  FLOAT *nodeFloats = node->floating;
  FLOAT *actFloat = nodeFloats;

  STR *nodeStrs = node->string;
  STR *actStr = nodeStrs;

  POINT *nodePoints = node->point;
  POINT *actPoint = nodePoints;

  fprintf(fileOutPtr, "str: ");
  while( actStr ){
    fprintf(fileOutPtr, "%s ", actStr->value );
    actStr = actStr->next;
  }
  fprintf(fileOutPtr, "int: ");
  while( actInt ){
    fprintf(fileOutPtr,"%d ", actInt->value);
    actInt = actInt->next;
  }
  fprintf(fileOutPtr, "float: ");
  while( actFloat ){
    fprintf(fileOutPtr, "%.2f ", actFloat->value);
    actFloat = actFloat->next;
  }
  fprintf(fileOutPtr, "point: ");
  while( actPoint )
  {
    fprintf(fileOutPtr, "(%.2f, %.2f) ", actPoint->value[0], actPoint->value[1] );
    actPoint = actPoint->next;
  }
  fprintf(fileOutPtr, "\n");
  fclose(fileOutPtr);
}
///MOSTRA O CONTEÚDO DE UMA LISTA DE NODE
void show_node_list_content( NODE *initNode ){
  NODE *actNode = initNode;

  while( actNode ){
    INT *nodeInts = actNode->interger; 
    INT *actInt = nodeInts;

    FLOAT *nodeFloats = actNode->floating;
    FLOAT *actFloat = nodeFloats;

    STR *nodeStrs = actNode->string;
    STR *actStr = nodeStrs;

    POINT *nodePoints = actNode->point;
    POINT *actPoint = nodePoints;

    printf("\nSTART BLOCK");
    printf("\n\tIntergers: ");
    while( actInt ){
      printf("%d\t", actInt->value);
      actInt = actInt->next;
    }
    printf("\n\tFloatings: ");
    while( actFloat ){
      printf("%.2f\t", actFloat->value);
      actFloat = actFloat->next;
    }
    printf("\n\tStrings: ");
    while( actStr ){
      printf( "%s\t", actStr->value );
      actStr = actStr->next;
    }
    printf("\n\tPoints: ");
    while( actPoint )
    {
      printf("[(%.2f, %.2f) d = %.2f]\t", actPoint->value[0], actPoint->value[1], actPoint->distanceFromOrigin );
      actPoint = actPoint->next;
    }
    printf("\nEND BLOCK\n");
  
    actNode = actNode->next;
  }
}
///MOSTRA CONTEÚDO DE UMA LISTA DE STRs
void show_str_list_content( STR *initStr ){
  STR *actString = initStr;

  printf("Lista de Strings: ");
  while( actString != NULL ){
    printf("%s\t", actString->value );
    actString = actString->next;
  }
}
///MOSTRA O CONTEÚDO DE UMA LISTA DE ITEMs
void show_item_list_content( ITEM *initItem ){
  ITEM *actItem = initItem;

  while( actItem != NULL ){
    STR *actString = actItem->list;

    printf("\nList: ");
    while(actString != NULL ){
      printf("%s\t", actString->value);
      actString = actString->next;
    }
    putchar('\n');
    actItem = actItem->next;
  }
}
//FUNÇÃO TESTE PARA AS VERIFICADORAS DE TIPO
void test_data_type_funtions(void){
  char string[] = "string,";
  printf("\n[%s] is_string: %s\n", string, (is_string(string) ? "true" : "false" ));
  printf("[%s] is_interger: %s\n", string, (is_interger(string) ? "true" : "false" ));
  printf("[%s] is_floating: %s\n", string, (is_floating(string) ? "true" : "false" ));
  printf("[%s] is_point: %s\n", string, (is_point(string) ? "true" : "false" ));

  char point[] = "(2.1,-1)";
  printf("\n[%s] is_string: %s\n", point, (is_string(point) ? "true" : "false" ));
  printf("[%s] is_interger: %s\n", point, (is_interger(point) ? "true" : "false" ));
  printf("[%s] is_floating: %s\n", point, (is_floating(point) ? "true" : "false" ));
  printf("[%s] is_point: %s\n", point, (is_point(point) ? "true" : "false" ));
  
  char interger[] = "-1";
  printf("\n[%s] is_string: %s\n", interger, (is_string(interger) ? "true" : "false" ));
  printf("[%s] is_interger: %s\n", interger, (is_interger(interger) ? "true" : "false" ));
  printf("[%s] is_floating: %s\n", interger, (is_floating(interger) ? "true" : "false" ));
  printf("[%s] is_point: %s\n", interger, (is_point(interger) ? "true" : "false" ));

  char floating[] = "-1.3";
  printf("\n[%s] is_string: %s\n", floating, (is_string(floating) ? "true" : "false" ));
  printf("[%s] is_interger: %s\n", floating, (is_interger(floating) ? "true" : "false" ));
  printf("[%s] is_floating: %s\n", floating, (is_floating(floating) ? "true" : "false" ));
  printf("[%s] is_point: %s\n", floating, (is_point(floating) ? "true" : "false" ));

  char almostPoint[] ="(2.1,-1";
  printf("\n[%s] is_string: %s\n", almostPoint, (is_string(almostPoint) ? "true" : "false" ));
  printf("[%s] is_interger: %s\n", almostPoint, (is_interger(almostPoint) ? "true" : "false" ));
  printf("[%s] is_floating: %s\n", almostPoint, (is_floating(almostPoint) ? "true" : "false" ));
  printf("[%s] is_point: %s\n", almostPoint, (is_point(almostPoint) ? "true" : "false" ));
}