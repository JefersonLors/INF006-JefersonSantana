#ifndef menus_interfaces_h
#define menus_interfaces_h

#include "compraConfig.h"
#include "ofertasConfig.h"
#include "gerais.h"

unsigned MENU_PRINCIPAL( void );
unsigned MENU_PAPEL( void );
int MENU_COTACOES( void );
void VENDA_INTERFACE( );
void COMPRA_INTERFACE( void );
unsigned SUB_MENU_COTACOES( void );

unsigned MENU_PRINCIPAL(  ){
    unsigned resposta;
    printf( "======================================================\n"
            "\t\t\t\t\tSIMULADOR B3\n\n" 
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
    unsigned resposta;
    printf( "======================================================\n\n"
            "[1] ADICIONAR\n"
            "[2] RETIRAR\n"
            "[0] SAIR\n\n"
            "[ ] <- " 
            );
        scanf( "%d", &resposta ); getchar( ); 
        while( resposta < 0 || resposta > 2 ){
            printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
                  "[ ] <- " ); 
            scanf( "%d", &resposta ); getchar( );}
        printf("[%d] ", resposta );
        switch( resposta ){
            case 0: puts( "SAIR\n" ); break;
            case 1: puts( "ADICIONAR\n" ); break;
            case 2: puts( "RETIRAR\n" ); break;}    
    return resposta;
}

int MENU_COTACOES(  ){
    unsigned resposta;
    printf( "======================================================\n" 
            "\t\t\t\t\tESCOLHA A AÇÃO\n\n"
            "#\t\t   CODIGO\t\t\t  NOME DE PREGÃO\n\n"
            );

    if( listar_papeis( ) ){
        printf( "[0] SAIR\n\n"
                "[ ] <- " 
              );
        scanf( "%d", &resposta ); getchar( ); 
        while( resposta < 0 || resposta > dados.quantidade_de_papel ){
            printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
                  "[ ] <- " ); 
            scanf( "%d", &resposta ); getchar( );}
        printf("[%d] ", resposta );
        switch( resposta ){
            case 0: puts( "SAIR\n" ); break;
            default: puts( "ESCOLHIDA\n" ); break;}
        return resposta;
    }return -1;
}
unsigned SUB_MENU_COTACOES(  ){
    unsigned resposta;

    printf( "[0] SAIR\n"
            "[1] ATUALIZAR\n\n"
            "[ ] <- " 
            );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta != 0 && resposta != 1 ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
    printf("[%d] ", resposta );
    switch( resposta ){
        case 0: puts( "SAIR\n" ); break;
        case 1: puts( "ATUALIZAR\n" ); break;}
    return resposta;
}
void COMPRA_INTERFACE( ){
    int resposta;
    printf( "======================================================\n" 
            "\t\t\t\t\tOFERTA DE COMPRA\n\n" );

    resposta = MENU_COTACOES( );    
    
    if( resposta > 0 ){
    
        int respostaBackup = resposta,
            quantidadeTemp = 0;
        float valorTemp = 0.0; 
        
        papel *inicio = NULL;
        
        recupera_papeis( &inicio );

        while( resposta > 1 ){ inicio = inicio->next; resposta--; }
        
        printf( "======================================================\n" 
                "\t\t\t\t\tOFERTA DE COMPRA\n\n" );
        
        printf( "Acão: %s - %s\n", inicio->codigo, inicio->nomeDePregao );
        printf( "\nPreço: " );
        
        scanf( "%f", &valorTemp );
        if( valorTemp != 0 ){
            while( valorTemp < 0 ){
                puts( "\n\t\t\tvalor inválido!\n");
                printf( "\nPreço: R$" );
                scanf( "%f", &valorTemp );
            }
            printf( "\nQuantidade: " );
            scanf("%d", &quantidadeTemp );
            while( quantidadeTemp < 0 ){
                puts( "\n\t\t\tquantidade inválida!\n");
                printf( "\nQuantidade: " );
                scanf( "%d", &quantidadeTemp );
            }
            acao *nova = (acao*)malloc( sizeof(acao) );
         
            strcpy( nova->identificacao.codigo, inicio->codigo );
            strcpy( nova->identificacao.nomeDePregao, inicio->nomeDePregao );
           
            nova->quantidadeOfertado = 1;
            (nova->valor) = (qtd_valores*)malloc( sizeof(qtd_valores) );
            (nova->valor)->quantidade = quantidadeTemp;
            (nova->valor)->valor = valorTemp;
            nova->next = NULL;
            nova->prev = NULL;
            
            limpa_lista_de_papeis( &inicio );
            if( incluir_oferta_de_compra( nova ) ){
                puts( "\n\t\t\tOferta inlcuída com sucesso!\n\n");
            }else{
                puts( "\t\t\t\nOps! não foi possível inserir a oferta!\n\n");
            }
        }
    }else if ( resposta == -1 ){
        puts("\n\t\t\tNÃO HÁ PAPEIS PARA NEGOCIAR!\n\n");}
}
#endif