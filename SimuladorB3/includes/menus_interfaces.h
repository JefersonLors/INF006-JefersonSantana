#ifndef menus_interfaces_h
#define menus_interfaces_h

unsigned MENU_PRINCIPAL( void );
unsigned MENU_PAPEL( void );
unsigned MENU_COTACOES( void );
void CARTEIRA_INTERFACE( void );
unsigned SUB_MENU_COTACOES( void );

unsigned MENU_PRINCIPAL(  ){
    unsigned resposta;
    printf( "======================================================\n"
            "\t\t\t\t\tSIMULADOR B3\n\n" 
            "[1] COTAÇÕES\n"
            "[2] COMPRAR\n"
            "[3] VENDER\n"
            "[4] CARTEIRA\n"
            "[5] PAPEIS\n"
            "[0] SAIR\n\n"
            "[ ] <- " 
        );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta < 0 || resposta > 5 ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
    printf("[%d] ", resposta );
    switch( resposta ){
        case 0: puts( "SAIR\n" ); break;
        case 1: puts( "COTAÇÕES\n" ); break;
        case 2: puts( "COMPRAR\n" ); break;
        case 3: puts( "VENDER\n" ); break;
        case 4: puts( "CARTEIRA\n" ); break;
        case 5: puts( "PAPEIS\n" ); break;}
    return resposta;
}
unsigned MENU_PAPEL( ){
    unsigned resposta;
    printf( "======================================================\n\n"
            "[1] ADICIONAR\n"
            "[2] RETIRAR\n"
            "[0] SAIR\n\n"
            "[ ] <- " 
            );
        scanf( "%d", &resposta ); getchar( ); 
        while( resposta < 0 || resposta > 2 ){
            printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
                  "[ ] <- " ); 
            scanf( "%d", &resposta ); getchar( );}
        printf("[%d] ", resposta );
        switch( resposta ){
            case 0: puts( "SAIR\n" ); break;
            case 1: puts( "ADICIONAR\n" ); break;
            case 2: puts( "RETIRAR\n" ); break;}    
    return resposta;
}
void CARTEIRA_INTERFACE( ){
    
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
unsigned MENU_COTACOES(  ){
    unsigned resposta;
    printf( "======================================================\n" 
            "\t\t\t\t\tESCOLHA A AÇÃO\n\n"
            "#\t\t   CODIGO\t\t\t  NOME DE PREGÃO\n\n"
            );

    listar_papeis( );
    printf( "[0] SAIR\n\n"
            "[ ] <- " 
          );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta < 0 || resposta > dados.quantidade_de_papel ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
    printf("[%d] ", resposta );
    switch( resposta ){
        case 0: puts( "SAIR\n" ); break;
        default: puts( "ESCOLHIDA\n" ); break;}
    return resposta;
}
unsigned SUB_MENU_COTACOES(  ){
    unsigned resposta;

    printf( "[0] SAIR\n"
            "[1] ATUALIZAR\n\n"
            "[ ] <- " 
            );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta != 0 && resposta != 1 ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
    printf("[%d] ", resposta );
    switch( resposta ){
        case 0: puts( "SAIR\n" ); break;
        case 1: puts( "ATUALIZAR\n" ); break;}
    return resposta;
}
#endif