#ifndef carteiraConfig_h
#define carteiraConfig_h
#include "gerais.h"
#include "ofertasConfig.h"

void listar_carteira(  );
void listar_carteira( ){
    printf( "========================================="
            "=========================================\n" 
            "\t\t\t\t\t\t\t\t\tCARTEIRA" );
    do{
        printf( "\n\nATIVO\t\t\t\t\tDATA-COMPRA\t\t"
                "HORA-COMPRA\t\tVALOR-COMPRA\t\tQTDE\n\n\n" ); 
        
        
        printf( "VALOR-ATUAL\t\t\t\tTOTAL-COMPRA\t"
                "TOTAL-ATUAL\t\tLUCRO/PREJUIZO\t\t  %%\n\n" );
        printf( "========================================="
                "=========================================\n\n");
    }while( false );
    printf( "\n\t\t\t\t\t\t\t\t[ENTER PARA SAIR]\n");
    getchar( );
}
#endif