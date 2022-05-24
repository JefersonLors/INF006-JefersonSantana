#ifndef AGREGADOS_h
#define AGREGADOS_h

#include <string.h>

char *papeis = "papeis.txt";
char *dadosConfig = "dadosConfig.txt"; 

#define TAM_NOME_PREGAO 15   
#define TAM_CODIGO 9

typedef struct papel{
    char nomeDePregao[TAM_NOME_PREGAO],
         codigo[TAM_CODIGO];
    struct papel *next; 
}papel;

struct{
    int quantidade_de_papel;
}dados;

unsigned MENU_PRINCIPAL( void );
bool criaArquivos( );
bool salvaPapeis( papel* );
bool recuperaPapeis( papel** );
bool salvaDados( );
unsigned MENU_PAPEL( );
bool adiciona_papel( );
bool retira_papel( papel** );
bool listar_papeis( papel** );
void limpaTexto( char* );
bool inicializar( papel** );


bool criaArquivos( ){
    FILE *arquivo;

    if( ( arquivo = fopen( papeis, "r" ) ) == NULL ){
        if( ( arquivo = fopen( papeis, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    if( ( arquivo = fopen( dadosConfig, "r" ) ) == NULL ){
        if( ( arquivo = fopen( dadosConfig, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    return true;
}
bool salvaPapeis( papel *head ){
    papel *atual = head,
          *backup = NULL;
    FILE *arquivoPapeis = fopen( papeis, "a" ),
         *arquivoConfig = fopen( dadosConfig, "w" );

    if( !arquivoPapeis ){
        fclose( arquivoPapeis );
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
bool salvaDados( ){

    return true;
}
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
bool retira_papel( papel **head ){
    
    return true;
}
bool listar_papeis( papel **head ){
    papel *primeiro = *head;
    
    printf( "=========================================\n" 
            "\t\t\t\t PAPEIS\n\n%15s       %10s\t\t\n", 
            "CÓDIGO", "NOME");
    
    if( primeiro != NULL ){
        do{ printf( "%14s             %-10s\n", primeiro->codigo, primeiro->nomeDePregao );
            primeiro = primeiro->next;
        }while( primeiro != NULL );
        return true;
    }else{ 
        recuperaPapeis( head );
        if( *head ){
            primeiro = *head; 
            do{ printf( "%14s             %-10s\n", primeiro->codigo, primeiro->nomeDePregao );
                primeiro = primeiro->next;
            }while( primeiro != NULL );
            return true;
        }else{
            return false; }
    }
}
void limpaTexto( char *texto ){
    for( int caracter = 0; texto[caracter] != '\0'; caracter++ ){
        if( texto[caracter+1] == '\0' )
            texto[caracter] = '\0';}
}
bool inicializar( papel **head ){
    if( !criaArquivos( ) ){
        puts( "\tNÃO FOI POSSÍVEL CRIAR OS ARQUIVOS :(\n\n" );}
    if( !recuperaPapeis( head ) ){
        //puts( "\tLISTA DE AÇÕES VAZIA :(\n\n" );
        }
    
    return true;
}
#endif