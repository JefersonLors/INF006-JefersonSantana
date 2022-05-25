#ifndef papelConfig_h
#define papelConfig_h
#include "gerais.h"
#include "dadosConfig.h"

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

bool adiciona_papel( papel **head ){
    printf( "=========================================\n" 
            "\t\t\t ADICIONANDO PAPEIS\n\n" 
            "DIGITE [0 PARA SAIR]:\n\n");
    
    papel *primeiro = NULL,
          *atual = NULL,
          *novo = NULL;
    
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
    
    if( salvaPapeis( primeiro ) ){
        return true;
    }else { return false; }
}
bool salvaPapeis( papel *head ){
    papel *atual = head,
          *backup = NULL;
    FILE *arquivoPapeis = fopen( papeis, "a" ),
         *arquivoConfig = fopen( dadosConfig, "w" );

    if( !arquivoPapeis ){
        return false;
    }else{
        while( atual != NULL ){
            backup = atual->next; 
            fprintf( arquivoPapeis, "%-*s%-*s\n", TAM_CODIGO*2-1, atual->codigo, 
                     TAM_NOME_PREGAO, atual->nomeDePregao );
            free( atual );
            atual = backup;}
        fprintf( arquivoConfig, "%d", dados.quantidade_de_papel ); }
    
    fclose( arquivoPapeis );
    fclose( arquivoConfig );
    return true;
}
bool recuperaPapeis( papel **head ){
    papel *atual = *head,
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
            
            fclose( arquivoConfig );
            fclose( arquivoPapeis );
            return true;}
    }return false;
}
bool listar_papeis( papel **head ){
    papel *primeiro = *head;
    
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
    
    return true;
}
#endif