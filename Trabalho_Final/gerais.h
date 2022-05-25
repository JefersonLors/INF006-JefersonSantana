#ifndef gerais_h
#define gerais_h

void limpaTexto( char* );


void limpaTexto( char *texto ){
    for( int caracter = 0; texto[caracter] != '\0'; caracter++ ){
        if( texto[caracter+1] == '\0' )
            texto[caracter] = '\0';}
}


#endif