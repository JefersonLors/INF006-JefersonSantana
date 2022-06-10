#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "includes/papelConfig.h"
#include "includes/vendaConfig.h"
#include "includes/compraConfig.h"
#include "includes/carteiraConfig.h"
#include "includes/cotacoesConfig.h"

unsigned MENU_PRINCIPAL( void );
unsigned MENU_PAPEL( void );

bool inicializar( papel** );

int main( ){
    enum OPCOES{ SAIR = 0, COTACOES = 1, COMPRAR = 2, VENDER = 3, CARTEIRA = 4, PAPEIS = 5 };
    enum MANUTENCAO_PAPEIS{  ADICIONAR = 1, RETIRAR = 2, LISTAR = 3 };
    
    int resposta,
        subResposta;
    papel *primeiro = NULL;
    
    if( inicializar( &primeiro ) ){
        do{ resposta = MENU_PRINCIPAL( ); 
            switch( resposta ){
                case COTACOES: 
                break;
                
                case COMPRAR: 
                break;
    
                case VENDER:
                break;
    
                case CARTEIRA: 
                    CARTEIRA_INTERFACE(  );
                    break;
    
                case PAPEIS: 
                    do{ subResposta = MENU_PAPEL( );
                        switch( subResposta ){
                            case ADICIONAR: 
                                if( adiciona_papel( ) ){
                                    puts("\t\tPAPEIS ADICIONADOS COM SUCESSO!\n\n");
                                }else{
                                    puts("   OPS! OS PAPEIS NÃO FORAM ADICIONADOS.\n\n");    
                                }break;
                            case RETIRAR:
                                if( retira_papel( &primeiro ) ){
                                    puts("\t\tPAPEIS RETIRADOS COM SUCESSO!\n\n");
                                }else{
                                    puts("   OPS! OS PAPEIS NÃO FORAM RETIRADOS.\n\n");    
                                }break;
                            case LISTAR: 
                                if( !listar_papeis( &primeiro ) ){
                                    puts("\n\t  NÃO HÁ PAPEIS PARA NEGOCIAR!\n\n");
                                }break;}
                    }while( subResposta != SAIR );
            }
        }while( resposta != SAIR );
    }else{ puts( "\tNÃO FOI POSSÍVEL INICIALIZAR :(\n\n" ); }
    puts( "\t\t\tPROGRAMA ENCERRADO\n\n" );
    return 0;
}
unsigned MENU_PRINCIPAL(  ){
    int resposta;
    printf( "=========================================\n"
            "\t\t\tBOLSO DE VALORES\n\n" 
            "[1] COTAÇÕES\n"
            "[2] COMPRAR\n"
            "[3] VENDER\n"
            "[4] CARTEIRA\n"
            "[5] PAPEIS\n"
            "[0] SAIR\n\n"
            "[ ] <- " 
        );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta < 0 || resposta > 5 ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
     printf("[%d] ", resposta );
     switch( resposta ){
         case 0: puts( "SAIR\n" ); break;
         case 1: puts( "COTAÇÕES\n" ); break;
         case 2: puts( "COMPRAR\n" ); break;
         case 3: puts( "VENDER\n" ); break;
         case 4: puts( "CARTEIRA\n" ); break;
         case 5: puts( "PAPEIS\n" ); break;}
    return resposta;
}
unsigned MENU_PAPEL( ){
    int resposta;
    printf( "=========================================\n"
                "\t\t\t\t PAPEIS\n\n" 
                "[1] ADICIONAR\n"
                "[2] RETIRAR\n"
                "[3] LISTAR\n"
                "[0] SAIR\n\n"
                "[ ] <- " 
            );
        scanf( "%d", &resposta ); getchar( ); 
        while( resposta < 0 || resposta > 3 ){
            printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
                  "[ ] <- " ); 
            scanf( "%d", &resposta ); getchar( );}
         printf("[%d] ", resposta );
         switch( resposta ){
             case 0: puts( "SAIR\n" ); break;
             case 1: puts( "ADICIONAR\n" ); break;
             case 2: puts( "RETIRAR\n" ); break;
             case 3: puts( "LISTAR\n" ); break;}    
    return resposta;
}
bool inicializar( papel **head ){
    if( !criaArquivos( ) ){
        puts( "\tNÃO FOI POSSÍVEL CRIAR OS ARQUIVOS :(\n\n" );}
    if( !recuperaPapeis( head ) ){
        //puts( "\tLISTA DE AÇÕES VAZIA :(\n\n" );
        }
    return true;
}