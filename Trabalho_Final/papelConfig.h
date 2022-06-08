#ifndef papelConfig_h
#define papelConfig_h
#include "gerais.h"
#include "dadosConfig.h"
#include <string.h>

#define TAM_NOME_PREGAO 15   
#define TAM_CODIGO 9

typedef struct papel{
    char nomeDePregao[TAM_NOME_PREGAO],
         codigo[TAM_CODIGO];
    struct papel *next; 
}papel;

bool adiciona_papel( );
bool salvaPapeis( papel* );
bool recuperaPapeis( papel** );
bool listar_papeis( papel** );
bool retira_papel( papel** );

bool adiciona_papel( ){
    printf( "=========================================\n" 
            "\t\t\t ADICIONANDO PAPEIS\n\n" 
            "DIGITE [0 PARA SAIR]:\n\n");
    
    papel *primeiro = NULL,
          *atual = NULL,
          *novo = NULL;
    
    FILE *quantidadePapel = fopen( dadosConfig, "r" );
    
    fscanf( quantidadePapel, "%d", &dados.quantidade_de_papel );
    fclose( quantidadePapel );
    
    do{ if( primeiro == NULL ){
            primeiro = (papel*)malloc( sizeof(papel) );
            printf( "NOME: " );
            fgets( primeiro->nomeDePregao, TAM_NOME_PREGAO, stdin );///validar
            limpaTexto( primeiro->nomeDePregao );
        
            if( primeiro->nomeDePregao[0] == '0' ){ 
                free(primeiro);
                primeiro = NULL;
                break;
            }else{
                printf( "CÓDIGO: " );
                fgets( primeiro->codigo, TAM_CODIGO, stdin );///validar
                limpaTexto( primeiro->codigo );
                primeiro->next = NULL;
                dados.quantidade_de_papel++;
                putchar('\n');}
        }else{
            atual = primeiro;
            while( atual->next != NULL ){
                atual = atual->next;}
            
            novo = (papel*)malloc( sizeof(papel) );
            printf( "NOME: " );
            fgets( novo->nomeDePregao, TAM_NOME_PREGAO, stdin );///validar
            limpaTexto( novo->nomeDePregao );
        
            if( novo->nomeDePregao[0] == '0'){ 
                free(novo);
                novo = NULL;
                break;
            }else{          
                printf( "CÓDIGO: " );
                fgets( novo->codigo, TAM_CODIGO, stdin );///validar
                limpaTexto( novo->codigo );
                atual->next = novo;
                novo->next = NULL;
                dados.quantidade_de_papel++;
                putchar('\n');}}
    }while( true );
    putchar('\n');
    
    int quantidadeBackup = dados.quantidade_de_papel;
    
    if( salvaPapeis( primeiro ) ){
        quantidadePapel = fopen( dadosConfig, "w" );
        fprintf( quantidadePapel, "%d", quantidadeBackup ); 
        fclose( quantidadePapel );
        return true;
    }else { return false; }
}
bool salvaPapeis( papel *head ){
    papel *atual = head,
          *inicioBackup = NULL,
          *backup = NULL,
          *inicio = NULL;

    recuperaPapeis( &inicio );
    inicioBackup = inicio;

    while( inicioBackup->next != NULL ){
        inicioBackup = inicioBackup->next;}
    
    FILE *arquivoPapeis = fopen( papeis, "w" ),
         *arquivoConfig = fopen( dadosConfig, "w" );

    if( !arquivoPapeis ){
        return false;
    }else{
        inicioBackup->next = head;
        while( inicio != NULL ){
            backup = inicio->next; 
            fprintf( arquivoPapeis, "%-*s%-*s\n", TAM_CODIGO*2-1, inicio->codigo, 
                     TAM_NOME_PREGAO, inicio->nomeDePregao );
            free( inicio );
            inicio = backup;}
        fprintf( arquivoConfig, "%d", dados.quantidade_de_papel ); }
    
    fclose( arquivoPapeis );
    fclose( arquivoConfig );
    return true;
}
bool recuperaPapeis( papel **head ){
    papel *atual,
          *proximo;
    FILE *arquivoPapeis = fopen( papeis, "r" ),
         *arquivoConfig = fopen( dadosConfig, "r" );
    
    if( arquivoPapeis && arquivoConfig ){
        fscanf( arquivoConfig, "%d", &dados.quantidade_de_papel );
        int fila = dados.quantidade_de_papel;
        
        if( fila > 0 ){
            atual = (papel*)malloc( sizeof(papel) );
            fscanf( arquivoPapeis, "%s%s", atual->codigo, atual->nomeDePregao);
            atual->next = NULL;
            *head = atual;
            fila--;
            
            do{ proximo = (papel*)malloc( sizeof(papel) );
                while( atual->next != NULL ){
                    atual = atual->next;}
                fscanf( arquivoPapeis, "%s%s",proximo->codigo, proximo->nomeDePregao);
                atual->next = proximo;
                proximo->next = NULL;
                fila--; 
            }while( fila > 0 );
            /*
            papel *teste = *head;
            while( teste != NULL ){
                printf( "%s\n", teste->codigo );
                teste = teste->next;}
            */
            fclose( arquivoConfig );
            fclose( arquivoPapeis );
            return true;}
    }return false;
}
bool listar_papeis( papel **head ){
    papel *primeiro;
    
    printf( "=========================================\n" 
            "\t\t\t\t PAPEIS\n\n%15s       %10s\t\t\n", 
            "CÓDIGO", "NOME");
    
    if( recuperaPapeis( head ) ){
        primeiro = *head; 
        do{ printf( "%14s             %-10s\n", primeiro->codigo, primeiro->nomeDePregao );
            primeiro = primeiro->next;
        }while( primeiro != NULL );
        
        return true;
    }else{ 
        return false; }
}
bool retira_papel( papel **head ){
    recuperaPapeis( head );
    
    printf( "=========================================\n" 
            "\t\t\t EXCLUINDO PAPEIS\n\n" 
            "DIGITE [0 PARA SAIR]:\n\n");
    
    papel *atual = *head,
          *backup = NULL;
          
    char codigo_temp[TAM_CODIGO];
    int quantidade_de_papel_backup = dados.quantidade_de_papel;
    
        do{ 
            printf( "CÓDIGO: " );
            fgets( codigo_temp, TAM_CODIGO, stdin );///validar
            
            if( codigo_temp[0] == '0' ){ 
                break;
            }else{
                limpaTexto( codigo_temp );
                while( atual->next != NULL ){
                    backup = atual;
                    atual = atual->next;
                    if( ( strcmp( codigo_temp, atual->codigo ) )  == 0 ){
                        puts( "teste");
                        printf( "%d", dados.quantidade_de_papel );
                        backup->next = atual->next;
                        dados.quantidade_de_papel--;
                        free( atual );
                        break;}
                }
            }
            if( quantidade_de_papel_backup < dados.quantidade_de_papel ){
                if( salvaPapeis( *head ) ){
                    return true;}
            }else return false; 
    }while( true );
    putchar('\n');
}
#endif