#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

unsigned MENU_PRINCIPAL( void );

int main( ){
    enum OPCOES { SAIR = 0, COMPRAR = 1, VENDER = 2, CARTEIRA = 3, PAPEIS = 4 };
    int resposta;
    
    do{ resposta = MENU_PRINCIPAL( ); 
        
            
    
    }while( resposta != SAIR );
    
    
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
        puts( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <-  " ); 
        scanf( "%d", &resposta ); getchar( );}
    return resposta;
 }