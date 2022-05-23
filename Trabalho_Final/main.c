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
                                puts("\t\tPROBLEMAS COM A LISTA DE PAPEIS!\n\n");
                            }break;}
            }
        }while( resposta != SAIR );
    }else{ puts( "\tNÃO FOI POSSÍVEL INICIALIZAR :(\n\n" ); }
    puts( "\t\t\tPROGRAMA ENCERRADO\n\n" );
    return 0;
}
