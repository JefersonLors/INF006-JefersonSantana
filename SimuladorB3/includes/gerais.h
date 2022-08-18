#ifndef gerais_h
#define gerais_h

#include <string.h>
#include <ctype.h>

#define teste puts("teste");
#define delay getchar( );
#define aqui puts( "aqui" );

void formata_texto( char* );
void DELAY( unsigned );

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
void DELAY( unsigned seg ){
    for ( int cronometro = 1; cronometro <= seg; cronometro++ ){      //estrutura de cronometro que conta até aproximadamente 15 segundos
        for ( int timer = 0; timer <= 100000000 ; timer++ ){         //conta até cem bilhões em aproximadamente 1 s.
            //if ( timer == 500000000 ){}                                  //A cada 1 s, aproximadamente, imprime um tracinho na tela
    
    }}
   
}

#endif