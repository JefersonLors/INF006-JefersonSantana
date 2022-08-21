#ifndef carteiraConfig_h
#define carteiraConfig_h
#include "gerais.h"
#include "ofertasConfig.h"


typedef struct carteira{
    papel identificacao;
    unsigned quantidade;
    float valor;
    char dataHoraCompra[30];
    struct carteira *next;
    struct carteira *prev;
}carteira;

void listar_carteira(  );
void recupera_carteira( carteira** );

void listar_carteira( ){
    carteira *carteiraInicio = NULL,
             *carteiraAtual = NULL;
    
    recupera_carteira( &carteiraInicio );
    carteiraAtual = carteiraInicio;
    
    printf( "============================================="
            "=============================================\n" 
            "\t\t\t\t\t\t\t\t\t\tCARTEIRA" );

    printf( "\n\n\t\tDATA/HORA\t\t\t COTAÇÃO\t\tQTDE\t\tVALOR\t\tCÓDIGO\t\tNOME\n\n" ); 

    while( carteiraAtual ){
        printf( "%-*s%-*.2f%-*u%-*.2f%-*s%-*s\n", 
                29, carteiraAtual->dataHoraCompra, 
                15, carteiraAtual->identificacao.cotacao,
                12, carteiraAtual->quantidade, 
                12, carteiraAtual->valor, 
                12, carteiraAtual->identificacao.codigo, 
                TAM_NOME_PREGAO, carteiraAtual->identificacao.nomeDePregao );
        
        carteiraAtual = carteiraAtual->next;}
    
    printf( "============================================="
            "=============================================\n\n" );
   
    printf( "\n\t\t\t\t\t\t\t\t\t[ENTER PARA SAIR]\n");
    getchar( );
}
void recupera_carteira( carteira **carteiraInicio ){
    carteira *primeiraAcaoCarteira = NULL,
             *proximaAcaoCarteira = NULL;

    FILE *carteiraUsuario = fopen( carteiraConfig, "r" ),
         *dadosGerais = fopen( dadosConfig, "r" );

    fscanf( dadosGerais, "%u%u%u", &dados.quantidade_de_papel, 
            &dados.quantidade_de_acoes,
            &dados.quantidade_de_acoes_compradas );

    unsigned quantidade_de_acoes_compradas = dados.quantidade_de_acoes_compradas;
    
    if( carteiraUsuario && dadosGerais ){
        primeiraAcaoCarteira = (carteira*)malloc( sizeof(carteira) );
       
        fscanf( carteiraUsuario, "%s%f%u%f%s%s", 
                primeiraAcaoCarteira->dataHoraCompra,
                &(primeiraAcaoCarteira->identificacao.cotacao),
                &(primeiraAcaoCarteira->quantidade), 
                &(primeiraAcaoCarteira->valor), 
                primeiraAcaoCarteira->identificacao.codigo,
                primeiraAcaoCarteira->identificacao.nomeDePregao );
      
        *carteiraInicio = primeiraAcaoCarteira;
        primeiraAcaoCarteira->next = NULL;
        primeiraAcaoCarteira->prev = NULL;
        quantidade_de_acoes_compradas--;
        
        while( quantidade_de_acoes_compradas > 0 ){
            while( primeiraAcaoCarteira->next ){
                primeiraAcaoCarteira = primeiraAcaoCarteira->next;}
            
            proximaAcaoCarteira = (carteira*)malloc( sizeof(carteira) );
         
            fscanf( carteiraUsuario, "%s%f%u%f%s%s", 
                    proximaAcaoCarteira->dataHoraCompra,
                    &(proximaAcaoCarteira->identificacao.cotacao), 
                    &(proximaAcaoCarteira->quantidade),
                    &(proximaAcaoCarteira->valor),
                    proximaAcaoCarteira->identificacao.codigo, 
                    proximaAcaoCarteira->identificacao.nomeDePregao );
            
            primeiraAcaoCarteira->next = proximaAcaoCarteira;
            proximaAcaoCarteira->next = NULL;
            proximaAcaoCarteira->prev = primeiraAcaoCarteira;
            
            quantidade_de_acoes_compradas--;
        }
    }
    fclose( carteiraUsuario );
    fclose( dadosGerais );
}
#endif