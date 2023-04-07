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

//ESTRUTURA QUE CONTÉM UMA LISTA DE PONTOS,
//A SOMA DA DISTÂNCIA ENTRE ELES E AINDA,
//A DISTÂNCIA ENTRE O PRIMEIRO E O ÚLTIMO PONTO 
struct Base{
    float distance;
    float shortCut;
    struct List *list;
    struct Base *next;
};

//ESTRUTURA QUE CONTÉM AS COORDENADAS EM FLOAT DE UM PONTO
struct List{
    float *coordinates;
    float distanceFromOrigin;
    struct List *next;
};

//ESTRUTURA QUE CONTÉM AS COORDENADAS EM STRING DE PONTO;
struct String_List{
    char *string;
    struct String_List *next;
};

//APP
int main(){
    BASE *points = get_lists_from_file_and_returns_float_dynamic_matriz( fileInPath );
    BASE *actList = points;

    while( actList != NULL ){
        actList->distance = calculate_distance_between_points(actList->list);
        actList->shortCut = calculate_shortCut(actList->list);
        calculate_distance_from_origin(actList->list);
        sort_point_list(actList->list);
        write_list_on_out_file( fileOutPath, actList->list, actList->distance, actList->shortCut );
        actList = actList->next;
    }

    /*DESCOMENTE PARA DEGUBAR*/

    // BASE *actBase = points;
   
    // while( actBase != NULL ){
    //     LIST *actList = actBase->list;

    //     printf("Points: " );
    //     while( actList != NULL ){
    //         printf("(%.2f, %.2f)\t", actList->coordinates[0], actList->coordinates[1]);

    //         actList = actList->next;
    //     }
    //     printf("\ndistance: %.2f\n", actBase->distance);
    //     printf("shortCut: %.2f\n", actBase->shortCut);
    //     putchar('\n');

    //     actBase = actBase->next;
    // }
    return EXIT_SUCCESS;
}

//CARREGA PRA MEMÓRIA TODOS OS PONTOS DE CADA LINHA
BASE *get_lists_from_file_and_returns_float_dynamic_matriz (const char *filesName){
    FILE *fileInPtr = fopen( filesName,"r");
    BASE *headBase = NULL;
    BASE *actBase = NULL;
    BASE *newBase = NULL;

    LIST *list = NULL;

    char line[MAX_SIZE_LINE];

    if( !fileInPtr ){
        return headBase;

    }else{
        while( fgets(line, MAX_SIZE_LINE, fileInPtr) != NULL ){
            line[strlen(line)] = '\0';
            list = get_line_and_returns_float_dynamic_list(line);
            
            if( headBase == NULL ){
                newBase = malloc(sizeof(BASE));
                newBase->list = list;
                newBase->next = NULL;
                headBase = newBase;
            } else{
                actBase = headBase;

                while( actBase->next != NULL ){
                    actBase = actBase->next;
                }

                newBase = malloc(sizeof(BASE));
                newBase->list = list;
                newBase->next = NULL;
                actBase->next = newBase;
            }
        } 
    }
    
    /*DESCOMENTE PARA DEBUGAR*/

    // actBase = headBase;

    // while( actBase != NULL ){
    //     LIST *actList = actBase->list;

    //     printf("Points: " );
    //     while( actList != NULL ){
    //         printf("(%.1f, %.1f)\t", actList->coordinates[0], actList->coordinates[1]);
    //         actList = actList->next;
    //     }
    //     putchar('\n');

    //     actBase = actBase->next;
    // }
    fclose(fileInPtr);
    return headBase;
}

//CRIA UMA LISTA DE FLOATS COM AS COORDENADAS DA LINHA
LIST *get_line_and_returns_float_dynamic_list( char*line ){
    STR_LIST *stringPointsList = get_string_line_and_returns_dynamic_string_list(line);

    LIST *headPoint = NULL;
    LIST *newPoint = NULL;
    LIST *actPoint = NULL;

    if( stringPointsList != NULL ){
        newPoint = malloc(sizeof(LIST));
        newPoint->coordinates = get_string_and_returns_float_array(stringPointsList->string);
        newPoint->next = NULL;
        headPoint = newPoint;

        stringPointsList = stringPointsList->next;
        
        while( stringPointsList != NULL ){
            actPoint = headPoint;

            while( actPoint->next != NULL ){
                 actPoint = actPoint->next;
            }

            newPoint = malloc(sizeof(LIST));
            newPoint->coordinates = get_string_and_returns_float_array(stringPointsList->string);
            newPoint->next = NULL;
            actPoint->next = newPoint;
            stringPointsList = stringPointsList->next;
        }

    } else{
        return NULL;
    }
    /*DESCOMENTE PARA DEBUGAR*/

    // actPoint = headPoint;   

    // printf("points: ");
    // while(actPoint != NULL ){
    //     printf("(%.1f, %.1f)\t", actPoint->coordinates[0], actPoint->coordinates[1] );
    //     actPoint = actPoint->next;  
    // }
    // putchar('\n');
    return headPoint;
}

//CRIA UMA LISTA DE PONTOS AINDA EM STRINGS
STR_LIST *get_string_line_and_returns_dynamic_string_list( char*line ){
    char *slice = NULL;
    char *sliceBackUp = NULL;

    float *points;

    STR_LIST *actPoint = NULL;
    STR_LIST *newPoint = NULL; 
    STR_LIST *headPoint = NULL;

    //QUEBRA O PRIMEIRO ELEMENTO "Points"
    slice = strtok( line, " " );

    //SOBRESCREVE "Points" COM AS COORDENADAS DO PRIMEIRO PONTO
    slice = strtok( NULL, " " );

    //CRIA LISTA COM OS PONTOS AINDA COMO STRING
    if( slice != NULL ){
        newPoint = malloc(sizeof(STR_LIST));
        newPoint->string = slice;
        newPoint->next = NULL;
        headPoint = newPoint;

        slice = strtok( NULL, " " );

        while(slice != NULL ){
            actPoint = headPoint;

            while(actPoint->next != NULL){
                actPoint = actPoint->next;
            }

            newPoint = malloc(sizeof(STR_LIST));
            newPoint->string = slice;
            newPoint->next = NULL;
            actPoint->next = newPoint;
            slice = strtok( NULL, " " );
        }
    }else {
        return NULL;
    }

    /*DESCOMENTE PARA DEBUGAR*/
    // actPoint = headPoint;   

    // printf("points: ");
    // while(actPoint != NULL ){
    //     printf("%s\t", actPoint->string );
    //     actPoint = actPoint->next;  
    // }
    // puts("fim");
    // putchar('\n');

    return headPoint;
}

//TRANSFORMA A STRING QUE REPRESENTA UM PONTO NUM VETOR DE FLOAT CONTENDO SUAS COORDENADAS
float *get_string_and_returns_float_array( char *numericString ){
    char delimiterLeft = '(';
    char delimiterRight = ')';
    char delimiterCenter = ',';
    char *slice = numericString;
    char *sliceBackUp = NULL;
    char *garbage = NULL;

    /*DESCOMENTE PARA DEBUGAR*/
    // printf("numericString: %s\n", numericString);
    // getchar();

    float *coordenates = malloc(sizeof(float)*TAM_COORD);

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

//CALCULA A SOMA DA DISTÂNCIA ENTRE OS PONTOS DE UMA LISTA
float calculate_distance_between_points( LIST *list ){
    LIST *pointA = list;
    LIST *pointB = NULL;
    float distance = 0;

    while( pointA->next != NULL ){
        pointB = pointA->next;
        distance += calculate_distance_between_two_points( pointA->coordinates[0], pointA->coordinates[1], pointB->coordinates[0], pointB->coordinates[1] );
        pointA = pointA->next;
    }
    return distance;
}

//CALCULA A DISTÂNCIA ENTRE DOIS PONTOS QUAISQUER
float calculate_distance_between_two_points( float Xa, float Ya, float Xb, float Yb ){
    float distance = sqrt( pow((Xb - Xa), 2) + pow((Yb - Ya), 2) );
    return distance;
}

//CALCULAR A DISTÂNCIA ENTRE O PRIMEIRO E O ÚLTIMO PONTO DE UMA LISTA
float calculate_shortCut( LIST *list){
    LIST *point = list;
    float *firstPoint = point->coordinates;
    float *lastPoint = NULL;

    while (point->next != NULL)
    {
        point = point->next;
    }
    lastPoint = point->coordinates;

    return calculate_distance_between_two_points(firstPoint[0], firstPoint[1], lastPoint[0], lastPoint[1]);
}

//CALCULA A DISTÂNCIA ENTRE OS PONTOS DE UMA LISTA E A ORIGEM
void calculate_distance_from_origin( LIST *list ){
    LIST *point = list;

    while( point != NULL ){
        point->distanceFromOrigin = calculate_distance_between_point_and_origin( point->coordinates[0], point->coordinates[1] );
        point = point->next;
    }
}

//CALCULA A DISTÂNCIA ENTRE UM PONTO E A ORIGEM
float calculate_distance_between_point_and_origin( float x, float y ){
    return calculate_distance_between_two_points(.0, .0, x, y );
}

//ORDENA CRESCENTEMENTE OS PONTOS DE UMA LISTA
void sort_point_list( LIST *list ){
    LIST *actPoint = list;
    LIST *tempPoint = NULL;

    float *coordenatesbackUp = NULL;
    float distanceFromOrignBackUp = 0;

    while( actPoint != NULL ){
        tempPoint = actPoint;

        while( tempPoint->next != NULL ){
            if( tempPoint->distanceFromOrigin > tempPoint->next->distanceFromOrigin ){
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

//ESCREVE LISTAS ORDENADAS EM ARQUIVO
void write_list_on_out_file( const char*filesName, LIST *list, float distance, float shortCut ){
    FILE *fileOutPtr = fopen(filesName, "a+");
    
    LIST *actPoint = list;

    fprintf(fileOutPtr, "points " );
    while( actPoint != NULL ){
        fprintf(fileOutPtr, "(%.2f, %.2f) ", actPoint->coordinates[0], actPoint->coordinates[1] );
        actPoint = actPoint->next;
    }
    fprintf(fileOutPtr, "distance %.2f shortcut %.2f\n", distance, shortCut );
    fclose(fileOutPtr);
}