#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "agregados.h"

int main( ){
    enum OPCOES{ SAIR = 0, COMPRAR = 1, VENDER = 2, CARTEIRA = 3, PAPEIS = 4 };
    enum MANUTENCAO_PAPEIS{  ADICIONAR = 1, RETIRAR = 2, LISTAR = 3 };
    
    int resposta,
        subResposta;
    
    if( criaArquivos( ) ){
        if( recuperaDados( ) ){
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
                                if( adiciona_papel( ) ){
                                    puts("\t\tPAPEIS ADICIONADOS COM SUCESSO!\n\n");
                                }else{
                                    puts("   OPS! OS PAPEIS NÃO FORAM ADICIONADOS.\n\n");    
                                }break;
                            case RETIRAR: retira_papel( ); break;
                            case LISTAR: listar_papeis( ); break;}
                }
            }while( resposta != SAIR );
        }else{ puts( "\tNÃO FOI POSSÍVEL RECUPERAR OS DADOS :(\n\n" ); }
    }else{ puts( "   NÃO FOI POSSÍVEL CRIAR ARQUIVO DE PAPEIS :(\n\n" ); }
    puts( "\t\t\tPROGRAMA ENCERRADO\n\n" );
    return 0;
}
