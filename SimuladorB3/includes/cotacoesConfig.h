#ifndef cotacoesConfig_h
#define cotacoesConfig_h

#include <time.h>
#include <string.h>

typedef struct qtd_valores{
    int quantidade;
    float valor;
    struct qtd_valores *next;
}qtd_valores;

typedef struct acoes{
    papel identificao;
    qtd_valores valor;
    struct acoes *next;
}acao;

bool gerador_de_cotacoes( papel*, acao**, acao** );
bool recupera_cotacoes( acao**, acao** );
bool atualiza_cotacoes( acao**, acao** );
bool salva_cotacoes( acao**, acao** );
bool retira_cotacoes( acao**, acao** );
bool obtem_nome_e_codigo( papel*, acao* );
int gerador_de_quantidade( void );
float gerador_de_valor( void );
int gerador_de_oferta( void );

bool gerador_de_cotacoes( papel *inicioPapel, acao **inicioAcaoVenda, acao **inicioAcaoCompra  ){
    acao *atualVenda = *inicioAcaoVenda,
         *atualCompra = *inicioAcaoCompra,
         *novoVenda = NULL,
         *novoCompra = NULL;

    unsigned quantidadeAcoes = dados.quantidade_de_papel;
    unsigned quantidadeOferta = 0;
    
    if( inicioPapel ){
        while( quantidadeAcoes > 0 ){
            if( atualVenda == NULL ){
                quantidadeOferta = gerador_de_oferta( );
                atualVenda = (acao*)(malloc(sizeof(acao) ) );
                atualVenda->next = NULL;
            }else{
                quantidadeOferta = gerador_de_oferta( );
                while( atualVenda->next != NULL ){
                    atualVenda = atualVenda->next;}
                novoVenda = (acao*)(malloc(sizeof(acao) ) );
                novoVenda->next = NULL;
                atualVenda->next = novoVenda;
            }
            if( atualCompra == NULL ){
                quantidadeOferta = gerador_de_oferta( );
                atualCompra = (acao*)(malloc(sizeof(acao) ) );
                atualCompra->next = NULL;
            }else{
                quantidadeOferta = gerador_de_oferta( );
                while( atualCompra->next != NULL ){
                    atualCompra = atualCompra->next;}
                novoCompra = (acao*)(malloc(sizeof(acao) ) );
                novoCompra->next = NULL;
                atualCompra->next = novoCompra;
            }
            quantidadeAcoes--;}
        
    }else return false;
}
int gerador_de_quantidade( ){
    srand( time(NULL) );
    return 1 + rand( ) % 1000;
}
float gerador_de_valor( ){
    srand( time(NULL) );
    int inteiro = 1 + rand( ) % 1000,
        decimal = 0 + rand( ) % 99;
    return inteiro + ( decimal % 100 );
}
int gerador_de_oferta(  ){
    srand( time(NULL) );
    return 1 + rand( ) % 10;
}
bool obtem_nome_e_codigo( papel *inicioPapel, acao *inicioAcao ){
    papel *papelAtual = inicioPapel;
    acao *acaoAtual = inicioAcao;

    while( papelAtual != NULL ){
        strcpy( acaoAtual->identificao.nomeDePregao, papelAtual->nomeDePregao );
        strcpy( acaoAtual->identificao.codigo, papelAtual->codigo );
        papelAtual = papelAtual->next;
        acaoAtual = acaoAtual->next;}
}
bool recupera_cotacoes( acao **inicioAcaoVenda, acao **inicioAcaoCompra ){

    
}
bool retira_cotacoes( acao **inicioAcaoVenda, acao **inicioAcaoCompra  ){
    
}
bool salva_cotacoes( acao **inicioVenda, acao **inicioCompra ){

    
}

#endif