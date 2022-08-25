#ifndef carteiraConfig_h
#define carteiraConfig_h
#include "gerais.h"
#include "ofertasConfig.h"
#include "transacoesConfig.h"

typedef struct movimentacao{
    papel identificacao;
    unsigned quantidade;
    float valor;
    char dataHoraCompra[30];
    bool operacao;
    struct movimentacao *next;
    struct movimentacao *prev;
}movimentacao;

typedef struct carteira{
    papel identificacao;
    unsigned quantidade;
    struct carteira *next;
    struct carteira *prev;
}carteira;

int listar_carteira( bool );
void limpa_lista_de_movimentacoes( movimentacao* ); 
void limpa_lista_de_acoes_na_carteira( carteira* );
bool cria_carteira( carteira** );
bool salva_carteira( carteira* );
bool recupera_carteira( carteira** );
void historico_de_transacao( char*, char* );
bool recupera_historico_de_transacao( movimentacao** );
void ajusta_carteira( carteira** );
int MENU_CARTEIRA( void );

int listar_carteira( bool seletor ){
    carteira *carteiraOrganizada = NULL,
             *acaoAtual = NULL;
    
    unsigned indice = 1;
    int escolha = 1,
        escolhaBackup = escolha;
    
    if( cria_carteira( &carteiraOrganizada ) ){
        do{ indice = 1;
    
            acaoAtual = carteiraOrganizada;
            
            printf( "\n#\t\tQTDE\t\tCÓDIGO\t\tNOME\n\n" ); 
            
            while( acaoAtual){
                printf( "%-*d%-*u%-*s%-*s\n\n", 8, indice++,
                        12, acaoAtual->quantidade, 
                        12, acaoAtual->identificacao.codigo, 
                        10, acaoAtual->identificacao.nomeDePregao );
                
                acaoAtual = acaoAtual->next;}

            escolhaBackup = escolha = MENU_CARTEIRA( );
            
            if( escolha ){
                acaoAtual = carteiraOrganizada;

                while( escolha > 1 ){
                    acaoAtual = acaoAtual->next;
                    escolha--;}

                if( seletor ){
                    historico_de_transacao( acaoAtual->identificacao.codigo,
                                            acaoAtual->identificacao.nomeDePregao );
                    
                    printf( "\t\t\t\t\t\t\t\t[ENTER PARA VOLTAR]\n" );
                    getchar( );
                }else{ break; }
            }else{break;} 
        }while( true );
        limpa_lista_de_acoes_na_carteira( carteiraOrganizada );
        return escolhaBackup;
    }else{ 
        return -1; }

}

void limpa_lista_de_movimentacoes( movimentacao *inicio ){
    while( inicio ){
        movimentacao *backup = inicio->next;
        free( inicio );
        inicio = backup;}
}
bool cria_carteira( carteira **carteiraOrganizada ){
    FILE *dadosGerais = fopen( dadosConfig, "r" );
    
    movimentacao *listaDeTransacoes = NULL,
                 *acaoAtual = NULL;

    carteira *inicioCarteiraOrganizada = NULL,
             *proximaAcao = NULL;
    
    recupera_historico_de_transacao( &listaDeTransacoes );
    acaoAtual = listaDeTransacoes;
    
    fscanf( dadosGerais, "%u%u%u%u", &dados.quantidade_de_papel, 
            &dados.quantidade_de_acoes, &dados.quantidade_de_transacoes,
            &dados.acoes_diferentes_na_carteira );
    
    dados.acoes_diferentes_na_carteira = 0;
    
    fclose( dadosGerais );
   
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
        dados.acoes_diferentes_na_carteira++;
        
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
                dados.acoes_diferentes_na_carteira++;
                backup = inicioCarteiraOrganizada;
                while( backup->next ){
                    backup = backup->next;}
                
                backup->next = proximaAcao;
                proximaAcao->next = NULL;
                proximaAcao->prev = backup;}
            acaoAtual = acaoAtual->next;}
        
        while( inicioCarteiraOrganizada ){
            acaoAtual = listaDeTransacoes;
            while( acaoAtual ){
                if( strcmp( inicioCarteiraOrganizada->identificacao.codigo,
                            acaoAtual->identificacao.codigo ) == 0 ){
                        if( acaoAtual->operacao ){
                            inicioCarteiraOrganizada->quantidade += acaoAtual->quantidade;
                        }else{
                            inicioCarteiraOrganizada->quantidade -= acaoAtual->quantidade;}}
                acaoAtual = acaoAtual->next;}
            inicioCarteiraOrganizada = inicioCarteiraOrganizada->next;}

        ajusta_carteira( carteiraOrganizada );
        limpa_lista_de_movimentacoes( listaDeTransacoes );
        salva_carteira( *carteiraOrganizada );
        if( *carteiraOrganizada ){
            return true;}
    }
    return false;
}

void historico_de_transacao( char *codigo, char *nome ){
    movimentacao *historicoCompleto = NULL,
                 *acaoAtual = NULL;
    recupera_historico_de_transacao( &historicoCompleto );
    acaoAtual = historicoCompleto;
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
bool recupera_historico_de_transacao( movimentacao **carteiraInicio ){
    movimentacao *primeiraAcaoCarteira = NULL,
                 *proximaAcaoCarteira = NULL;
    
    unsigned operacaoTemp;
    
    FILE *carteiraUsuario = fopen( historicoTransacao, "r" ),
         *dadosGerais = fopen( dadosConfig, "r" );

    fscanf( dadosGerais, "%u%u%u%u", &dados.quantidade_de_papel, 
            &dados.quantidade_de_acoes,
            &dados.quantidade_de_transacoes,
            &dados.acoes_diferentes_na_carteira);

    unsigned quantidade_de_transacoes = dados.quantidade_de_transacoes;
    
    if( carteiraUsuario && dadosGerais && quantidade_de_transacoes > 0 ){
        primeiraAcaoCarteira = (movimentacao*)malloc( sizeof(movimentacao) );
       
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
        quantidade_de_transacoes--;
        
        while( quantidade_de_transacoes > 0 ){
            while( primeiraAcaoCarteira->next ){
                primeiraAcaoCarteira = primeiraAcaoCarteira->next;}
            
            proximaAcaoCarteira = (movimentacao*)malloc( sizeof(movimentacao) );
         
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
            
            quantidade_de_transacoes--;
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
bool salva_carteira( carteira *carteiraInicio ){
    carteira *acaoAtual = carteiraInicio;

    FILE *CARTEIRA = fopen( carteiraConfig, "w" ),
         *dadosGerais = fopen( dadosConfig, "w" );

    if( CARTEIRA ){
        if( acaoAtual ){
            while( acaoAtual ){
                fprintf( CARTEIRA, "%-*u\t%-*s\t%-*s\n", 
                         8, acaoAtual->quantidade, 
                         TAM_CODIGO*2-1,acaoAtual->identificacao.codigo, 
                         TAM_NOME_PREGAO, acaoAtual->identificacao.nomeDePregao );
                acaoAtual = acaoAtual->next;
            }
        }
        fprintf( dadosGerais, "%u\n%u\n%u\n%u\n", dados.quantidade_de_papel, 
                 dados.quantidade_de_acoes, dados.quantidade_de_transacoes,
                 dados.acoes_diferentes_na_carteira );
        fclose( CARTEIRA );
        fclose( dadosGerais );
        return true;
    }else return false;
}
bool recupera_carteira( carteira **inicioCarteira ){         
    carteira *primeiraAcao = NULL,
             *proximaAcao = NULL;
        
    FILE *CARTEIRA = fopen( carteiraConfig, "r" ),
         *dadosGerais = fopen( dadosConfig, "r" );

    fscanf( dadosGerais, "%u%u%u%u", &dados.quantidade_de_papel, 
            &dados.quantidade_de_acoes,
            &dados.quantidade_de_transacoes,
            &dados.acoes_diferentes_na_carteira );

    unsigned fila = dados.acoes_diferentes_na_carteira;
    
    if( CARTEIRA && dadosGerais ){
        primeiraAcao = (carteira*)malloc( sizeof(carteira) );
        primeiraAcao->next = NULL;
        primeiraAcao->prev = NULL;

        fscanf( CARTEIRA, "%u%s%s", &primeiraAcao->quantidade,
                primeiraAcao->identificacao.codigo, primeiraAcao->identificacao.nomeDePregao );
       
        *inicioCarteira = primeiraAcao;
        
        fila--;
        while( fila > 0 ){
            while( primeiraAcao->next ){
                primeiraAcao = primeiraAcao->next;}
            
            proximaAcao = (carteira*)malloc( sizeof(carteira) );
            fscanf( CARTEIRA, "%u%s%s", &proximaAcao->quantidade,
                    proximaAcao->identificacao.codigo, proximaAcao->identificacao.nomeDePregao );
            
            primeiraAcao->next = proximaAcao;
            proximaAcao->prev = primeiraAcao;

            fila--;}
        
        fclose( CARTEIRA );
        fclose( dadosGerais );
        return true;
    }else{
        fclose( CARTEIRA );
        fclose( dadosGerais );
        return false;}
}
int MENU_CARTEIRA( ){
    unsigned resposta;
             
    printf( "[0] SAIR\n\n"
            "[ ] <- " 
          );
    scanf( "%d", &resposta ); getchar( ); 
    while( resposta < 0 || resposta > dados.acoes_diferentes_na_carteira ){
        printf( "\t\t\tOPÇÃO INVÁLIDA!\n\n"
              "[ ] <- " ); 
        scanf( "%d", &resposta ); getchar( );}
    printf("[%d] ", resposta );
    switch( resposta ){
        case 0: puts( "SAIR\n" ); break;
        default: puts( "ESCOLHIDA\n" ); break;}
    return resposta;
   
}
void limpa_lista_de_acoes_na_carteira( carteira *inicioCarteira ){
    while(inicioCarteira){
        carteira *backup = inicioCarteira->next;
        free( inicioCarteira );
        inicioCarteira = NULL;
        inicioCarteira = backup;
    }
    inicioCarteira = NULL;
}
void ajusta_carteira( carteira **inicioCarteira ){
    carteira *acaoCarteira = *inicioCarteira,
             *acaoCarteiraBackup = NULL;

    unsigned acoesNaCarteira = dados.acoes_diferentes_na_carteira;

    while( acoesNaCarteira > 0 ){
        acaoCarteira = *inicioCarteira;
        if( acaoCarteira->quantidade == 0 ){
            *inicioCarteira = acaoCarteira->next; 
            if( *inicioCarteira ){
                (*inicioCarteira)->prev = NULL;}
            free( acaoCarteira );
            acaoCarteira = NULL;
            acoesNaCarteira = dados.acoes_diferentes_na_carteira--;
        }else{
            acaoCarteiraBackup = acaoCarteira;
            acaoCarteira = acaoCarteira->next;
            while( acaoCarteira ){
                if( acaoCarteira->quantidade == 0 ){
                    acaoCarteiraBackup->next = acaoCarteira->next;
                    if( acaoCarteira->next ){
                        acaoCarteira->next->prev = acaoCarteiraBackup;}
                    free( acaoCarteira );
                    acoesNaCarteira = dados.acoes_diferentes_na_carteira--;
                    break;}
                acaoCarteiraBackup = acaoCarteira;
                acaoCarteira = acaoCarteira->next;}
        }acoesNaCarteira--;} 
}
#endif