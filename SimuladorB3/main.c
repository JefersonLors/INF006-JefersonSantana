#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "includes/papelConfig.h"
#include "includes/gerais.h"
#include "includes/vendaConfig.h"
#include "includes/compraConfig.h"
#include "includes/carteiraConfig.h"
#include "includes/cotacoesConfig.h"
#include "includes/menus_interfaces.h"

bool inicializar( papel**, acao**, acao** );

int main( ){
    enum OPCOES{ SAIR = 0, COTACOES = 1, COMPRAR = 2, 
                 VENDER = 3, CARTEIRA = 4, PAPEIS = 5 };
    enum MANUTENCAO_PAPEIS{ ADICIONAR = 1, RETIRAR = 2, LISTAR = 3 };
    
    int resposta,
        subResposta;
    
    papel *primeiro = NULL;
    
    acao *primeiraVenda = NULL,
         *primeiraCompra = NULL;
    
    if( inicializar( &primeiro, &primeiraVenda, &primeiraCompra ) ){
        do{ resposta = MENU_PRINCIPAL( ); 
            switch( resposta ){
                case COTACOES:
                    do{ subResposta = MENU_COTACOES( );
                        if( subResposta != SAIR ){
                            printf( "==========================="
                                    "===========================\n" 
                                    "\t\t\t\t\t\tAÇÃO\n\n" );
                            if( visualizar_ofertas_acao( subResposta ) ){
                                while( SUB_MENU_COTACOES(  ) ){
                                    atualiza_cotacoes( subResposta );
                                    printf( "==========================="
                                            "===========================\n" 
                                            "\t\t\t\t\t\tAÇÃO\n\n" );
                                    visualizar_ofertas_acao( subResposta );}  
                            }else{
                                puts("   OPS! NÃO HÁ COTAÇÕES.\n\n"); 
                            }

                        }else{ break;}
                    }while( true );   
                    break;
        
                case COMPRAR: 
                break;
    
                case VENDER:
                break;
    
                case CARTEIRA: 
                    CARTEIRA_INTERFACE(  );
                    break;
    
                case PAPEIS: 
                    do{ 
                        printf( "======================================================\n" 
                            "\t\t\t\t PAPEIS ATIVOS\n\n#%17s        %10s\t\t\n", 
                            "CÓDIGO", "NOME\n");
                        if( !listar_papeis(  ) ){
                            puts("\n\t  NÃO HÁ PAPEIS PARA NEGOCIAR!\n\n");}
                        
                        subResposta = MENU_PAPEL( );
                        
                        switch( subResposta ){
                            case ADICIONAR: 
                                printf( "======================================================\n" 
                                        "\t\t\t ADICIONANDO PAPEIS\n\n" 
                                        "DIGITE [0 PARA SAIR]:\n\n");
                                if( adiciona_papel( ) ){
                                    if( gerador_de_cotacoes( ) ){
                                        puts("\t\tPAPEIS ADICIONADOS COM SUCESSO!\n\n");
                                    }else{
                                         puts("   OPS! AS COTAÇÕES NÃO FORAM GERADAS.\n\n");   
                                    }
                                }else{
                                    puts("   OPS! OS PAPEIS NÃO FORAM ADICIONADOS.\n\n");    
                                }break;
                            case RETIRAR: 
                                printf( "======================================================\n" 
                                        "\t\t\t\t  EXCLUINDO PAPEIS\n\n" 
                                        "DIGITE [0 PARA SAIR]:\n\n");
                                if( retira_papel( ) && retira_cotacoes( ) ){
                                        puts("\t\tPAPEIS RETIRADOS COM SUCESSO!\n\n");
                                }else {
                                    puts("   OPS! OS PAPEIS NÃO FORAM RETIRADOS.\n\n"); }     
                                break;}
                    }while( subResposta != SAIR );
            }
        }while( resposta != SAIR );
    }else{ puts( "\tNÃO FOI POSSÍVEL INICIALIZAR :(\n\n" ); }
    puts( "\t\t\tPREGÃO ENCERRADO\n\n" );
    return 0;
}
bool inicializar( papel **headPapel, acao **headVenda, acao **headCompra  ){
    if( !cria_arquivos( ) ){
        puts( "\tNÃO FOI POSSÍVEL CRIAR OS ARQUIVOS :(\n\n" );}
    if( recupera_papeis( headPapel ) ){
        if( !recupera_cotacoes( headVenda, headCompra) ){
            }
    }
    return true;
}