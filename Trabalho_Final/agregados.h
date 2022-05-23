#ifndef AGREGADOS_h
#define AGREGADOS_h

char *papeis = "papeis.txt";
#define TAM_NOME_PREGAO 15   
#define TAM_CODIGO 9

typedef struct papel{
    char nomeDePregao[TAM_NOME_PREGAO],
         codigo[6];
    struct papel *next; 
}papel;

unsigned MENU_PRINCIPAL( void );
bool criaArquivos( );
bool salvaPapeis( papel* );
bool recuperaPapeis( );
bool recuperaDados( );
bool salvaDados( );
unsigned MENU_PAPEL( );
bool adiciona_papel( );
bool retira_papel( );
bool listar_papeis( );

 unsigned MENU_PRINCIPAL(  ){
    int resposta;
    printf( "=========================================\n"
            "\t\t\tBOLSO DE VALORES\n\n" 
            "[1] COMPRAR\n"
            "[2] VENDER\n"
            "[3] CARTEIRA\n"
            "[4] PAPEIS\n"
            "[0] SAIR\n\n"
            "[ ] <- " 
        );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta < 0 || resposta > 4 ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
     printf("[%d] ", resposta );
     switch( resposta ){
         case 0: puts( "SAIR\n" ); break;
         case 1: puts( "COMPRAR\n" ); break;
         case 2: puts( "VENDER\n" ); break;
         case 3: puts( "CARTEIRA\n" ); break;
         case 4: puts( "PAPEIS\n" ); break;}
    return resposta;
}
unsigned MENU_PAPEL( ){
    int resposta;
    printf( "=========================================\n"
                "\t\t\t\t  PAPEIS\n\n" 
                "[1] ADICIONAR\n"
                "[2] RETIRAR\n"
                "[3] LISTAR\n"
                "[0] SAIR\n\n"
                "[ ] <- " 
            );
        scanf( "%d", &resposta ); getchar( ); 
        while( resposta < 0 || resposta > 3 ){
            printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
                  "[ ] <- " ); 
            scanf( "%d", &resposta ); getchar( );}
         printf("[%d] ", resposta );
         switch( resposta ){
             case 0: puts( "SAIR\n" ); break;
             case 1: puts( "ADICIONAR\n" ); break;
             case 2: puts( "RETIRAR\n" ); break;
             case 3: puts( "LISTAR\n" ); break;}    
    return resposta;
}
bool criaArquivos( ){
    FILE *arquivo;

    if( ( arquivo = fopen( papeis, "r" ) ) == NULL ){
        if( ( arquivo = fopen( papeis, "w" ) ) == NULL ){
            return false;
        }else{ 
            fprintf( arquivo, "\t\t\t\t\tPAPEIS\n\n|\t\tCÓDIGO\t\t|\t\tNOME\t\t|\n\n" ); }
    fclose(arquivo);}
    return true;
}
bool salvaPapeis( papel *head ){
    papel *atual = head;
    FILE *arquivoPapeis = fopen( papeis, "a+" );

    if( !arquivoPapeis ){
        return false;
    }else{
        
        while( head != NULL ){
            printf( "head->codigo = %s\n", head->codigo);
            fprintf( arquivoPapeis, "%s%s", 
                      head->codigo, head->nomeDePregao );
            head = head->next;
        }
    }
    return true;
}
bool recuperaPapeis( ){

    return true;
}
bool recuperaDados( ){

    return true;
}
bool salvaDados( ){

    return true;
}
bool adiciona_papel( ){
    printf( "=========================================\n" 
            "\t\t\t ADICIONANDO PAPEIS\n\n" 
            "DIGITE [0 PARA SAIR]:\n\n");
    
    papel *primeiro = NULL,
          *atual = NULL,
          *novo = NULL;
    
    do{ if( primeiro == NULL ){
            primeiro = (papel*)malloc( sizeof(papel) );
            printf( "NOME: " );
            fgets( primeiro->nomeDePregao, TAM_NOME_PREGAO, stdin );
            
            if( primeiro->nomeDePregao[0] == '0' ){ 
                free(primeiro);
                break;
            }else{
                printf( "CÓDIGO: " );
                fgets( primeiro->codigo, TAM_CODIGO, stdin );
                primeiro->next = NULL;
                putchar('\n');}
        }else{
            atual = primeiro;
            while( atual->next != NULL ){
                atual = atual->next;}
            
            novo = (papel*)malloc( sizeof(papel) );
            printf( "NOME: " );
            fgets( novo->nomeDePregao, TAM_NOME_PREGAO, stdin );
            
            if( novo->nomeDePregao[0] == '0'){ 
                free(novo);
                break;
            }else{          
                printf( "CÓDIGO: " );
                fgets( novo->codigo, TAM_CODIGO, stdin );
                atual->next = novo;
                novo->next = NULL;
                putchar('\n');}}
    }while( true );
    putchar('\n');
    
    if( salvaPapeis( primeiro ) ){
        return true;
    }else { return false; }
}
bool retira_papel( ){
    return true;
}
bool listar_papeis( ){
    return true;
}
#endif