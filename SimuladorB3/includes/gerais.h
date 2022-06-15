#ifndef gerais_h
#define gerais_h

#include <string.h>
#include <ctype.h>

#define teste puts("teste");
#define delay getchar( );

void formata_texto( char* );


void formata_texto( char *texto ){
    for( int caracter = 0; texto[caracter] != '\0'; caracter++ ){
        texto[caracter] = toupper( texto[caracter] );
        if( texto[caracter+1] == '\0' )
            texto[caracter] = '\0';
        if( texto[caracter] == ' ' ) 
            texto[caracter] = '_';
        if( ( isalnum( texto[caracter] ) ) == 0 && texto[caracter] != '\0' )
            texto[caracter] = '_';
    }
}


#endif