#ifndef dadosConfig_h
#define dadosConfig_h

#include <dirent.h>

char *papeis = "arquivos/papeis.txt";
char *dadosConfig = "arquivos/dadosConfig.txt"; 
char *carteiraConfig = "arquivos/carteiraConfig.txt";

struct{
    int quantidade_de_papel;
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
    return true;
}
bool salvaDados( ){

    return true;
}
#endif