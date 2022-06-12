#ifndef dadosConfig_h
#define dadosConfig_h

#include <dirent.h>

char *papeis = "arquivos/papeis.txt";
char *dadosConfig = "arquivos/dadosConfig.txt"; 
char *carteiraConfig = "arquivos/carteiraConfig.txt";
char *acoesValorVenda = "arquivos/acoesValorVenda.txt";
char *acoesValorCompra = "arquivos/acoesValorCompra.txt";

struct{
    unsigned quantidade_de_papel,
             quantidade_de_acoes;
}dados;

bool criaArquivos( );
bool salvaDados( );

bool criaArquivos( ){
    FILE *arquivo;
    
    if( ( arquivo = fopen( papeis, "r" ) ) == NULL ){
        if( ( arquivo = fopen( papeis, "w" ) ) == NULL ){
            return false;}
    }fclose(arquivo);
    if( ( arquivo = fopen( dadosConfig, "r" ) ) == NULL ){
        if( ( arquivo = fopen( dadosConfig, "w" ) ) == NULL ){
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
bool salvaDados( ){

    return true;
}
#endif