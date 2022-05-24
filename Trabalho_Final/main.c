#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "agregados.h"

int main( ){
    enum OPCOES{ SAIR = 0, COMPRAR = 1, VENDER = 2, CARTEIRA = 3, PAPEIS = 4 };
    enum MANUTENCAO_PAPEIS{  ADICIONAR = 1, RETIRAR = 2, LISTAR = 3 };
    
    int resposta,
        subResposta;
    papel *primeiro = NULL;
    
    if( inicializar( &primeiro ) ){
        do{ resposta = MENU_PRINCIPAL( ); 
            switch( resposta ){
                case COMPRAR: 
                break;
    
                case VENDER:
                break;
    
                case CARTEIRA:
                break;
    
                case PAPEIS: 
                    switch( MENU_PAPEL( ) ){
                        case ADICIONAR: 
                            if( adiciona_papel( &primeiro ) ){
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
            "[1] COMPRAR\n"
            "[2] VENDER\n"
            "[3] CARTEIRA\n"
            "[4] PAPEIS\n"
            "[0] SAIR\n\n"
            "[ ] <- " 
        );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta < 0 || resposta > 4 ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
     printf("[%d] ", resposta );
     switch( resposta ){
         case 0: puts( "SAIR\n" ); break;
         case 1: puts( "COMPRAR\n" ); break;
         case 2: puts( "VENDER\n" ); break;
         case 3: puts( "CARTEIRA\n" ); break;
         case 4: puts( "PAPEIS\n" ); break;}
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
