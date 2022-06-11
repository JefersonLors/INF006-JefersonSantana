#ifndef cotacoesConfig_h
#define cotacoesConfig_h

#include <time.h>
#include <string.h>

typedef struct acoes{
    char nome[TAM_NOME_PREGAO],
         codigo[TAM_CODIGO];
    int quantidade;
    float valor;
}acao;

bool gerador_de_cotacoes( papel*, acao* );
int gerador_de_quantidade( void );
float gerador_de_valor( void );
bool obtem_nome_e_codigo( papel*, acao* );

bool gerador_de_cotacoes( papel *inicioPapel, acao *inicioAcao ){

    

    
    
    
    
    return true;
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
bool obtem_codigo( papel *inicioPapel, acao *inicioAcao ){ 

}


#endif