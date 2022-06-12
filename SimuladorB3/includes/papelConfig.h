#ifndef papelConfig_h
#define papelConfig_h

#include "gerais.h"
#include "dadosConfig.h"

#define TAM_NOME_PREGAO 20
#define TAM_CODIGO 8

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
    papel *primeiro = NULL,
          *atual = NULL,
          *inicio = NULL,
          *inicioBackup = NULL,
          *novo = NULL;

    recuperaPapeis( &inicio );

    FILE *quantidadePapel = fopen( papeis, "r" );
    
    fscanf( quantidadePapel, "%d", &dados.quantidade_de_papel );
    fclose( quantidadePapel );
    
    do{ if( primeiro == NULL ){
            primeiro = (papel*)malloc( sizeof(papel) );
            printf( "NOME: " );
            fgets( primeiro->nomeDePregao, TAM_NOME_PREGAO, stdin );///validar
            formata_texto( primeiro->nomeDePregao );
        
            if( primeiro->nomeDePregao[0] == '0' ){ 
                free(primeiro);
                primeiro = NULL;
                break;
            }else{
                printf( "CÓDIGO: " );
                fgets( primeiro->codigo, TAM_CODIGO, stdin );///validar
                formata_texto( primeiro->codigo );
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
            formata_texto( novo->nomeDePregao );
        
            if( novo->nomeDePregao[0] == '0'){ 
                free(novo);
                novo = NULL;
                break;
            }else{          
                printf( "CÓDIGO: " );
                fgets( novo->codigo, TAM_CODIGO, stdin );///validar
                formata_texto( novo->codigo );
                atual->next = novo;
                novo->next = NULL;
                dados.quantidade_de_papel++;
                putchar('\n');}}
    }while( true );
    putchar('\n');

    if( inicio != NULL ){
        inicioBackup = inicio;
        while( inicioBackup->next != NULL ){
            inicioBackup = inicioBackup->next;}
        inicioBackup->next = primeiro;
          
        if( salvaPapeis( inicio ) ){
            return true;}
    }else{
        if( salvaPapeis( primeiro ) ){
            return true;}}
    return false;
}
bool salvaPapeis( papel *head ){
    papel *atual = head,
          *backup = NULL;

    FILE *arquivoPapeis = fopen( papeis, "w" ),
         *arquivoConfig = fopen( dadosConfig, "w" );

    if( !arquivoPapeis ){
        return false;
    }else{
        atual = head;
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

            fclose( arquivoConfig );
            fclose( arquivoPapeis );
            return true;}
    }return false;
}
bool listar_papeis( papel **head ){
    papel *primeiro;
    int contador = 1;
    
    if( recuperaPapeis( head ) ){
        primeiro = *head; 
        do{ printf( "%-*d%*s             %-*s\n\n",
            3, contador++, 14, primeiro->codigo, TAM_NOME_PREGAO, 
            primeiro->nomeDePregao );
            primeiro = primeiro->next;
        }while( primeiro != NULL );
        
        return true;
    }else{ 
        return false; }
}
bool retira_papel( papel **head ){
    recuperaPapeis( head );
    
    papel *atual = *head,
          *backup = NULL;
          
    char codigo_temp[TAM_CODIGO];
    int quantidade_de_papel_backup = dados.quantidade_de_papel;

    if( *head ){
        do{ printf( "CÓDIGO: " );
            fgets( codigo_temp, TAM_CODIGO, stdin );///validar
            
            if( codigo_temp[0] == '0' ){ 
                break;
            }else{
                formata_texto( codigo_temp );
                if( ( strcmp( codigo_temp, atual->codigo ) ) == 0 ){
                    backup = atual->next;
                    free( atual );
                    *head = backup;
                    dados.quantidade_de_papel--;
                }else{
                    while( atual != NULL ){ 
                        backup = atual;
                        atual = atual->next;
                        if( ( strcmp( codigo_temp, atual->codigo ) ) == 0 ){
                            if( atual->next != NULL ){
                                backup->next = atual->next;
                            }else{
                                backup->next = NULL; }
                            dados.quantidade_de_papel--;
                            free( atual );
                            break;}}}}
            if( quantidade_de_papel_backup > dados.quantidade_de_papel ){
                if( salvaPapeis( *head ) ){
                    return true;}}
        }while( true );
    }else return false;
    putchar('\n');
}
#endif