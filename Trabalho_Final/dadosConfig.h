#ifndef dadosConfig_h
#define dadosConfig_h

char *papeis = "papeis.txt";
char *dadosConfig = "dadosConfig.txt"; 

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
    return true;
}
bool salvaDados( ){

    return true;
}
#endif