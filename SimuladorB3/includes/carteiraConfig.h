#ifndef carteiraConfig_h
#define carteiraConfig_h
#include "gerais.h"
#include "ofertasConfig.h"

typedef struct carteira{
    papel identificacao;
    unsigned quantidade;
    float valor;
    char dataHoraCompra[30];
    bool operacao;
    struct carteira *next;
    struct carteira *prev;
}carteira;

bool listar_carteira( void );
void historico_de_compra( carteira*, char*, char* );
bool recupera_carteira( carteira** );
void limpar_lista_de_acoes_na_carteira( carteira* ); 
void organizador_de_acoes( carteira*, carteira** );
int MENU_CARTEIRA( unsigned );

bool listar_carteira( ){
    carteira *carteiraInicio = NULL,
             *carteiraAtual = NULL,
             *carteiraOrganizada = NULL;
    
    unsigned indice = 1;
    int escolha = 1;
    
    if( recupera_carteira( &carteiraInicio ) ){
        do{ indice = 1;
            carteiraAtual = carteiraInicio;
    
            organizador_de_acoes( carteiraInicio, &carteiraOrganizada );
            
            carteiraAtual = carteiraOrganizada;
            
            printf( "==========================="
                    "===========================\n" 
                    "\t\t\t\t\t  CARTEIRA\n\n"
                    );
            printf( "\n#\t\tQTDE\t\tCÓDIGO\t\tNOME\n\n" ); 
            while( carteiraAtual ){
                printf( "%-*d%-*u%-*s%-*s\n\n", 8, indice++,
                        12, carteiraAtual->quantidade, 
                        12, carteiraAtual->identificacao.codigo, 
                        10, carteiraAtual->identificacao.nomeDePregao );
                
                carteiraAtual = carteiraAtual->next;}
            printf( "==========================="
                    "===========================\n\n" );
            
            escolha = MENU_CARTEIRA( --indice );
            
            if( escolha ){
                carteiraAtual = carteiraOrganizada;

                while( escolha > 1 ){
                    carteiraAtual = carteiraAtual->next;
                    escolha--;}
                
                historico_de_compra( carteiraInicio, carteiraAtual->identificacao.codigo,
                                     carteiraAtual->identificacao.nomeDePregao );
                
                printf( "\t\t\t\t\t\t\t\t[ENTER PARA VOLTAR]\n" );
                getchar( );
            }else{break;} 
        }while( true );
        
        limpar_lista_de_acoes_na_carteira( carteiraInicio );
        return true;
    }else return false;

}
bool recupera_carteira( carteira **carteiraInicio ){
    carteira *primeiraAcaoCarteira = NULL,
             *proximaAcaoCarteira = NULL;
    
    unsigned operacaoTemp;
    
    FILE *carteiraUsuario = fopen( carteiraConfig, "r" ),
         *dadosGerais = fopen( dadosConfig, "r" );

    fscanf( dadosGerais, "%u%u%u", &dados.quantidade_de_papel, 
            &dados.quantidade_de_acoes,
            &dados.quantidade_de_acoes_compradas );

    unsigned quantidade_de_acoes_compradas = dados.quantidade_de_acoes_compradas;
    
    if( carteiraUsuario && dadosGerais ){
        primeiraAcaoCarteira = (carteira*)malloc( sizeof(carteira) );
       
        fscanf( carteiraUsuario, "%s%f%u%f%s%s%u", 
                primeiraAcaoCarteira->dataHoraCompra,
                &(primeiraAcaoCarteira->identificacao.cotacao),
                &(primeiraAcaoCarteira->quantidade), 
                &(primeiraAcaoCarteira->valor), 
                primeiraAcaoCarteira->identificacao.codigo,
                primeiraAcaoCarteira->identificacao.nomeDePregao,
                &operacaoTemp );
        primeiraAcaoCarteira->operacao = operacaoTemp;
        
        *carteiraInicio = primeiraAcaoCarteira;
        primeiraAcaoCarteira->next = NULL;
        primeiraAcaoCarteira->prev = NULL;
        quantidade_de_acoes_compradas--;
        
        while( quantidade_de_acoes_compradas > 0 ){
            while( primeiraAcaoCarteira->next ){
                primeiraAcaoCarteira = primeiraAcaoCarteira->next;}
            
            proximaAcaoCarteira = (carteira*)malloc( sizeof(carteira) );
         
            fscanf( carteiraUsuario, "%s%f%u%f%s%s%u", 
                    proximaAcaoCarteira->dataHoraCompra,
                    &(proximaAcaoCarteira->identificacao.cotacao), 
                    &(proximaAcaoCarteira->quantidade),
                    &(proximaAcaoCarteira->valor),
                    proximaAcaoCarteira->identificacao.codigo, 
                    proximaAcaoCarteira->identificacao.nomeDePregao,
                    &operacaoTemp );
            proximaAcaoCarteira->operacao = operacaoTemp;
            
            primeiraAcaoCarteira->next = proximaAcaoCarteira;
            proximaAcaoCarteira->next = NULL;
            proximaAcaoCarteira->prev = primeiraAcaoCarteira;
            
            quantidade_de_acoes_compradas--;
        }
        fclose( carteiraUsuario );
        fclose( dadosGerais );
        return true;
    }else{
        fclose( carteiraUsuario );
        fclose( dadosGerais );
        return false;
    }
}
void limpar_lista_de_acoes_na_carteira( carteira *inicio ){
    while( inicio ){
        carteira *backup = inicio->next;
        free( inicio );
        inicio = backup;}
}
void organizador_de_acoes( carteira *inicioCarteira, carteira **carteiraOrganizada ){
    carteira *acaoAtual = inicioCarteira,
             *inicioCarteiraOrganizada = NULL,
             *proximaAcao = NULL;

    if( acaoAtual ){
        inicioCarteiraOrganizada = (carteira*)malloc( sizeof(carteira) );
        
        strcpy( inicioCarteiraOrganizada->identificacao.codigo, 
                acaoAtual->identificacao.codigo );
        
        strcpy( inicioCarteiraOrganizada->identificacao.nomeDePregao, 
                acaoAtual->identificacao.nomeDePregao );
        inicioCarteiraOrganizada->quantidade = 0;

        inicioCarteiraOrganizada->next = NULL;
        inicioCarteiraOrganizada->prev = NULL;
        *carteiraOrganizada = inicioCarteiraOrganizada;
        
        acaoAtual = acaoAtual->next;
        
        while( acaoAtual ){
            proximaAcao = (carteira*)malloc( sizeof(carteira) );
            proximaAcao->next = NULL;
            proximaAcao->prev = NULL;
            
            strcpy( proximaAcao->identificacao.codigo, 
                    acaoAtual->identificacao.codigo );
            
            strcpy( proximaAcao->identificacao.nomeDePregao, 
                    acaoAtual->identificacao.nomeDePregao );
            
            proximaAcao->quantidade = 0;
            
            carteira *backup = inicioCarteiraOrganizada;

            while( backup ){
                if( strcmp( backup->identificacao.codigo, 
                            acaoAtual->identificacao.codigo ) == 0 ){
                    free( proximaAcao );
                    proximaAcao = NULL;
                    break;}    
                backup = backup->next;}
        
            if( proximaAcao != NULL ){
                backup = inicioCarteiraOrganizada;
                while( backup->next ){
                    backup = backup->next;}
                
                backup->next = proximaAcao;
                proximaAcao->next = NULL;
                proximaAcao->prev = backup;}
            
            acaoAtual = acaoAtual->next;
        }
        
        acaoAtual = inicioCarteira;

        while( inicioCarteiraOrganizada ){
            acaoAtual = inicioCarteira;
            while( acaoAtual ){
                if( strcmp( inicioCarteiraOrganizada->identificacao.codigo,
                            acaoAtual->identificacao.codigo ) == 0 ){
                    inicioCarteiraOrganizada->quantidade += acaoAtual->quantidade;}
                acaoAtual = acaoAtual->next;}
            inicioCarteiraOrganizada = inicioCarteiraOrganizada->next;}
    }
}
int MENU_CARTEIRA( unsigned quantidadeDeOpcao ){
    unsigned resposta;
             
    if( quantidadeDeOpcao ){
        printf( "[0] SAIR\n\n"
                "[ ] <- " 
              );
        scanf( "%d", &resposta ); getchar( ); 
        while( resposta < 0 || resposta > quantidadeDeOpcao ){
            printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
                  "[ ] <- " ); 
            scanf( "%d", &resposta ); getchar( );}
        printf("[%d] ", resposta );
        switch( resposta ){
            case 0: puts( "SAIR\n" ); break;
            default: puts( "ESCOLHIDA\n" ); break;}
        return resposta;
    }return -1;
}
void historico_de_compra( carteira *historicoCompleto, char *codigo, char *nome ){
    carteira *acaoAtual = historicoCompleto;
    printf( "======================================="
            "=======================================\n"
            "NOME: %s\nCÓDIGO: %s\n"
            "======================================="
            "=======================================\n"
            "\t\t\t\t\t\t\tHISTÓRICO DE TRANSAÇÃO\n\n", nome, codigo
            );
    printf( "\t\tDATA/HORA\t\t\t\tCOTAÇÃO\t\tQTDE\t\tVALOR\t\tOPERAÇÃO\n\n" ); 
    
    while( acaoAtual ){
        if( strcmp( acaoAtual->identificacao.codigo, codigo ) == 0 ){
            printf( "%-*sR$%-*.2f%-*uR$%-*.2f%*c\n\n",
                    32, acaoAtual->dataHoraCompra, 
                    10, acaoAtual->identificacao.cotacao,
                    12, acaoAtual->quantidade, 
                    10, acaoAtual->valor, 
                    4, ((acaoAtual->operacao) ? ('+') : ('-') ) );}
        
        acaoAtual = acaoAtual->next;}

    printf( "======================================="
            "=======================================\n\n" );
    
    
}

#endif