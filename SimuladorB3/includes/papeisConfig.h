#ifndef papelConfig_h
#define papelConfig_h

#define teste puts("teste");
#include "gerais.h"
#include "dadosConfig.h"

#define TAM_NOME_PREGAO 20
#define TAM_CODIGO 8
#define TAM_COT 8

typedef struct papel{
    char nomeDePregao[TAM_NOME_PREGAO],
         codigo[TAM_CODIGO];   
    float cotacao;
    struct papel *next; 
}papel;

bool adiciona_papel( void );
bool salva_papeis( papel* );
bool recupera_papeis( papel** );

bool listar_papeis( void );
bool retira_papel( void );
void limpa_lista_de_papeis( papel** );

bool adiciona_papel( ){
    papel *primeiro = NULL,
          *atual = NULL,
          *inicio = NULL,
          *inicioBackup = NULL,
          *novo = NULL;

    recupera_papeis( &inicio );
    ///impedir de colocar papal repetido
    FILE *quantidadePapel = fopen( papeis, "r" );
    
    fscanf( quantidadePapel, "%d%d%d%d%d", &dados.quantidade_de_papel, 
            &dados.quantidade_de_acoes, 
            &dados.quantidade_de_transacoes,
            &dados.acoes_diferentes_na_carteira,
            &dados.acoes_diferentes_na_carteira);
    fclose( quantidadePapel );
    
    if( primeiro == NULL ){
        primeiro = (papel*)malloc( sizeof(papel) );
        printf( "NOME: " );
        fgets( primeiro->nomeDePregao, TAM_NOME_PREGAO, stdin );///validar
        formata_texto( primeiro->nomeDePregao );
    
        if( primeiro->nomeDePregao[0] == '0' ){ 
            free(primeiro);
            primeiro = NULL;
            return false;
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
            return false;
        }else{          
            printf( "CÓDIGO: " );
            fgets( novo->codigo, TAM_CODIGO, stdin );///validar
            formata_texto( novo->codigo );
            atual->next = novo;
            novo->next = NULL;
            dados.quantidade_de_papel++;
            putchar('\n');}}
    putchar('\n');

    if( inicio != NULL ){
        inicioBackup = inicio;
        while( inicioBackup->next != NULL ){
            inicioBackup = inicioBackup->next;}
        inicioBackup->next = primeiro;
          
        if( salva_papeis( inicio ) ){
            return true;}
    }else{
        if( salva_papeis( primeiro ) ){
            return true;}}
    return false;
}
bool salva_papeis( papel *head ){
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
            fprintf( arquivoPapeis, "%-*s%-*s%-*.2f\n", TAM_CODIGO*2-1, atual->codigo, 
                     TAM_NOME_PREGAO, atual->nomeDePregao, TAM_COT, atual->cotacao );
            free( atual );
            atual = backup;}
        
        fprintf( arquivoConfig, "%u\n%u\n%u\n%u", dados.quantidade_de_papel, dados.quantidade_de_acoes, 
                 dados.quantidade_de_transacoes, dados.acoes_diferentes_na_carteira ); 
        
    }
 
    fclose( arquivoPapeis );
   
    fclose( arquivoConfig );
  
    return true;
}
bool recupera_papeis( papel **head ){
    papel *atual,
          *proximo;
    FILE *arquivoPapeis = fopen( papeis, "r" ),
         *arquivoConfig = fopen( dadosConfig, "r" );
    
    if( arquivoPapeis && arquivoConfig ){
        fscanf( arquivoConfig, "%d%d%d%d", &dados.quantidade_de_papel,
                &dados.quantidade_de_acoes, &dados.quantidade_de_transacoes,
                &dados.acoes_diferentes_na_carteira);
        int fila = dados.quantidade_de_papel;
        
        if( fila > 0 ){
            atual = (papel*)malloc( sizeof(papel) );
            fscanf( arquivoPapeis, "%s%s%f", atual->codigo, atual->nomeDePregao, &atual->cotacao );
            atual->next = NULL;
            *head = atual;
            fila--;
            
            while( fila > 0 ){ 
                proximo = (papel*)malloc( sizeof(papel) );
                while( atual->next != NULL ){
                    atual = atual->next;}
                fscanf( arquivoPapeis, "%s%s%f",proximo->codigo, proximo->nomeDePregao, &proximo->cotacao );
                atual->next = proximo;
                proximo->next = NULL;
                fila--;}

            fclose( arquivoConfig );
            fclose( arquivoPapeis );
            return true;}
    }return false;
}
bool listar_papeis( ){
    papel *primeiro = NULL,
          *head = NULL;
    int contador = 1;
    
    if( recupera_papeis( &head ) ){
        primeiro = head; 
        printf( "#%17s        %10s        %11s\t\t\n", 
                "COTAÇÃO", "CÓDIGO", "NOME\n" );
        do{ printf( "%-*dR$%-*.2f%-*s%-*s\n\n",
            9, contador++, TAM_COT+8, primeiro->cotacao, 20, primeiro->codigo, TAM_NOME_PREGAO, 
            primeiro->nomeDePregao );
            primeiro = primeiro->next;
        }while( primeiro != NULL );
        limpa_lista_de_papeis( &head );
        return true;
    }else{ 
        return false; }
}
bool retira_papel(  ){
    papel *head = NULL;
    
    recupera_papeis( &head );
    
    papel *atual = head,
          *backup = NULL;
          
    char codigo_temp[TAM_CODIGO];

    if( head ){
        do{ printf( "CÓDIGO: " );
            fgets( codigo_temp, TAM_CODIGO, stdin );///validar
            
            if( codigo_temp[0] == '0' ){ 
                break;
            }else{
                formata_texto( codigo_temp );
                if( ( strcmp( codigo_temp, atual->codigo ) ) == 0 ){
                    backup = atual->next;
                    free( atual );
                    head = backup;
                    dados.quantidade_de_papel--;
                    if( salva_papeis( head ) ){
                        return true;
                    }else{ break; }
                }else{
                    backup = atual;
                    atual = atual->next;
                    while( atual != NULL ){ 
                        if( ( strcmp( codigo_temp, atual->codigo ) ) == 0 ){
                            backup->next = atual->next;
                            dados.quantidade_de_papel--;
                            free( atual );
                            if( salva_papeis( head ) ){
                                return true;
                            }else{ break; }}
                        backup = atual;
                        atual = atual->next;}}
                break;}
        }while( true );}
    putchar('\n');
    return false;   
}
void limpa_lista_de_papeis( papel **inicio ){
    papel *atual = *inicio;
    
    while( atual != NULL ){
        papel *backup = atual->next;
        free( atual );
        atual = NULL;
        atual = backup;}
    *inicio = atual;
}
#endif