#ifndef dadosConfig_h
#define dadosConfig_h

#include <dirent.h>

char *papeis = "arquivos/papeis.txt";
char *dadosConfig = "arquivos/dadosConfig.txt"; 
char *historicoTransacao = "arquivos/historicoTransacao.txt";
char *acoesValorVenda = "arquivos/acoesValorVenda.txt";
char *carteiraConfig = "arquivos/carteiraConfig.txt";
char *acoesValorCompra = "arquivos/acoesValorCompra.txt";

struct{
    unsigned quantidade_de_papel,
             quantidade_de_acoes,
             quantidade_de_transacoes,
             acoes_diferentes_na_carteira;
}dados;

bool cria_arquivos( );
bool salva_dados( );

bool cria_arquivos( ){
    FILE *arquivo;
    
    if( ( arquivo = fopen( papeis, "r" ) ) == NULL ){
        if( ( arquivo = fopen( papeis, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    if( ( arquivo = fopen( dadosConfig, "r" ) ) == NULL ){
        if( ( arquivo = fopen( dadosConfig, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    if( ( arquivo = fopen( historicoTransacao, "r" ) ) == NULL ){
        if( ( arquivo = fopen( historicoTransacao, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    if( ( arquivo = fopen( carteiraConfig, "r" ) ) == NULL ){
        if( ( arquivo = fopen( carteiraConfig, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    if( ( arquivo = fopen( acoesValorVenda, "r" ) ) == NULL ){
        if( ( arquivo = fopen( acoesValorVenda, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    if( ( arquivo = fopen( acoesValorCompra, "r" ) ) == NULL ){
        if( ( arquivo = fopen( acoesValorCompra, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    return true;
}
bool salva_dados( ){

    return true;
}
#endif