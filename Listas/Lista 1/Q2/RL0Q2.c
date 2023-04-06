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

int main( ){
  NODE *first = get_items_from_file_and_returns_item_dynamic_typed_matrix(fileInPath);

  puts("FIM");
  return EXIT_SUCCESS;
}

NODE *get_items_from_file_and_returns_item_dynamic_typed_matrix( const char *fileName ){
  NODE *firstNode = NULL; 
  NODE *newNode = NULL; 
  NODE *actNode = NULL; 
  NODE *lastNode = NULL;

  ITEM *newListItem = create_dynamic_string_items_matrix(fileName);
  ITEM *actListItem = newListItem;
  
  if( newListItem == NULL ){
    return firstNode;
  }else{
    newNode = malloc(sizeof(NODE));
    puts("aqui");
    newNode = type_items(newListItem->list);
    puts("aqui");
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

  return firstNode;
}
STR *get_line_and_return_dynamic_items_list(char *line){
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

    while( word != NULL ){
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
  // actString = firstString;

  // printf("Lista de Strings: ");
  // while( actString != NULL ){
  //   printf("%s\t", actString->value );
  //   actString = actString->next;
  // }
  // putchar('\n');

  return firstString;
}
ITEM *create_dynamic_string_items_matrix(const char *fileName ){
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

    if( line != NULL ){
      newItem = malloc(sizeof(ITEM));
      newItem->list = get_line_and_return_dynamic_items_list(line);
      newItem->next = NULL;
      firstItem = newItem;
      lastItem = newItem;
      
      while( fgets(line, MAX_SIZE_LINE, fileInPtr) != NULL ){
        line[strlen(line)-1] = '\0';
        newItem = malloc(sizeof(ITEM));
        newItem->list = get_line_and_return_dynamic_items_list(line);
        newItem->next = NULL;
        actItem = lastItem;
        actItem->next = newItem;
        lastItem = newItem; 
      }
    }
  }

  /*DESCOMENTE PARA DEBUGAR*/
  // actItem = firstItem;

  // while( actItem != NULL ){
  //   STR *actString = actItem->list;

  //   printf("\nList: ");
  //   while(actString != NULL ){
  //     printf("%s\t", actString->value);
  //     actString = actString->next;
  //   }
  //   putchar('\n');
  //   actItem = actItem->next;
  // }
  return firstItem;
}
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
        newString->value = to_string(actItem->value);
        newString->next = NULL;

        if( firstString == NULL ){
          firstString = newString;
          lastString = newString;
        }else{
          actString = lastString;
          actString->next = newString;
          lastString = newString;
        }
        continue;
      }
      if( is_interger(actItem->value) ){
        newInterger = malloc(sizeof(INT));
        newInterger->value = to_interger(actItem->value);
        newInterger = NULL;

        if( firstInterger == NULL ){
          firstInterger = newInterger;
          lastInterger = newInterger;
        }else{
          actInterger = lastInterger;
          actInterger->next = newInterger;
          lastInterger = newInterger;
        }
        continue;
      }
      if( is_floating(actItem->value)){
        newFloating = malloc(sizeof(FLOAT));
        newFloating = to_floating(actItem->value);
        newFloating = NULL;

        if( firstFloating == NULL ){
          firstFloating = newFloating;
          lastFloating = newFloating;
        }else{
          actFloating = lastFloating;
          actFloating->next = newFloating;
          lastFloating = newFloating;
        }
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
POINT *to_point( char *string ){
  POINT *node = malloc(sizeof(POINT));
  node->value = extract_point_from_string(string);
  node->distanceFromOrigin = calculate_distance_from_origin(node->value[0], node->value[1]);
  node->next = NULL;
  return node;
}
INT *to_interger( char *string ){
  INT *node = malloc(sizeof(INT));
  node->value = atoi(string);
  node->next = NULL;
  return node;
}
FLOAT *to_floating( char *string ){
  FLOAT *node = malloc(sizeof(FLOAT));
  node->value = atof(string);
  node->next = NULL;
  return node;
}
STR *to_string( char *string ){
  STR *node = malloc(sizeof(STR));
  node->value = string;
  node->next = NULL;
  return node;
}
float *extract_point_from_string( char *numericString ){
    char delimiterLeft = '(';
    char delimiterRight = ')';
    char delimiterCenter = ',';
    char *slice = numericString;
    char *sliceBackUp = NULL;
    char *garbage = NULL;

    /*DESCOMENTE PARA DEBUGAR*/
    // printf("numericString: %s\n", numericString);
    // getchar();

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
float calculate_distance_from_origin( float X, float Y ){
    float distance = sqrt( pow((X - 0), 2) + pow((Y - 0), 2) );
    return distance;
}