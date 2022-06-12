#ifndef cotacoesConfig_h
#define cotacoesConfig_h

#include <time.h>
#include <string.h>

typedef struct qtd_valores{
    int quantidade;
    float valor;
    struct qtd_valores *next;
}qtd_valores;

typedef struct acoes{
    papel identificacao;
    qtd_valores *valor;
    unsigned quantidadeCotado;
    struct acoes *next;
}acao;

bool gerador_de_lista_de_cotacoes( acao**, acao** );
bool gerador_de_lista_de_oferta( qtd_valores**, acao* );
bool gerador_de_cotacoes( papel**, acao**, acao** );

bool preenche_cotacoes( papel**, acao**, acao** );
bool retira_cotacoes( acao**, acao** );
bool obtem_nome_e_codigo( papel*, acao* );

bool gerador_de_quantidade_de_acoes( qtd_valores* );
bool gerador_de_valor( qtd_valores* );
unsigned gerador_de_quantidade_de_oferta( void );

bool recupera_cotacoes( acao**, acao** );
bool atualiza_cotacoes( acao**, acao** );
bool salva_cotacoes( acao**, acao** );

bool visualizar_ofertas_acao( unsigned, acao*, acao* );

bool gerador_de_cotacoes( papel **inicioPapel, acao **inicioAcaoVenda, acao **inicioAcaoCompra  ){
    if( *inicioPapel ){
       if( gerador_de_lista_de_cotacoes( inicioAcaoVenda, inicioAcaoCompra ) ){
            if( preenche_cotacoes( inicioPapel, inicioAcaoVenda, inicioAcaoCompra ) ){ 
                if( salva_cotacoes( inicioAcaoVenda, inicioAcaoCompra ) ){
                    return true;}}}
    }else return false;
}
bool preenche_cotacoes( papel **inicioPapel, acao **inicioAcaoVenda, acao **inicioAcaoCompra ){
    acao *atualAcaoV = *inicioAcaoVenda,
         *atualAcaoC = *inicioAcaoCompra;
    
    if( obtem_nome_e_codigo( *inicioPapel, *inicioAcaoVenda) ){
        if( obtem_nome_e_codigo( *inicioPapel, *inicioAcaoCompra ) ){
            while( atualAcaoV != NULL ){
                if( gerador_de_quantidade_de_acoes( atualAcaoV->valor ) ){
                    if( gerador_de_quantidade_de_acoes( atualAcaoC->valor ) ){
                        if( gerador_de_valor( atualAcaoV->valor ) ){
                            if( gerador_de_valor( atualAcaoC->valor ) ){
                            }else return false;
                        }else return false;
                    }else return false;    
                }else return false;
                atualAcaoV = atualAcaoV->next;
                atualAcaoC = atualAcaoC->next;
            }return true;
        }return false;
    }return false;
}
bool gerador_de_lista_de_cotacoes( acao **inicioAcaoVenda, acao **inicioAcaoCompra ){
    acao *atualVenda = *inicioAcaoVenda,
         *atualCompra = *inicioAcaoCompra,
         *novoVenda = NULL,
         *novoCompra = NULL;

    unsigned quantidadeAcoes = dados.quantidade_de_papel;
    
    while( quantidadeAcoes > 0 ){
        if( atualVenda == NULL ){
            atualVenda = (acao*)(malloc(sizeof(acao) ) );
            atualVenda->valor = NULL;
            gerador_de_lista_de_oferta( &atualVenda->valor, atualVenda );
            atualVenda->next = NULL;
            *inicioAcaoVenda = atualVenda;
        }else{
            while( atualVenda->next != NULL ){
                atualVenda = atualVenda->next;}
            novoVenda = (acao*)(malloc(sizeof(acao) ) );
            novoVenda->valor = NULL;
            gerador_de_lista_de_oferta( &novoVenda->valor, novoVenda );
            novoVenda->next = NULL;
            atualVenda->next = novoVenda;
        }
        if( atualCompra == NULL ){
            atualCompra = (acao*)(malloc(sizeof(acao) ) );
            atualCompra->valor = NULL;
            gerador_de_lista_de_oferta( &atualCompra->valor, atualCompra );
            atualCompra->next = NULL;
            *inicioAcaoCompra = atualCompra;
        }else{
            while( atualCompra->next != NULL ){
                atualCompra = atualCompra->next;}
            novoCompra = (acao*)(malloc(sizeof(acao) ) );
            novoCompra->valor = NULL;
            gerador_de_lista_de_oferta( &novoCompra->valor, novoCompra );
            novoCompra->next = NULL;
            atualCompra->next = novoCompra;
        }
        quantidadeAcoes--;}

    if( quantidadeAcoes == 0 )
        return true;
    else return false;
}
bool gerador_de_lista_de_oferta( qtd_valores **inicio, acao *acao ){
    unsigned quantidade = acao->quantidadeCotado = gerador_de_quantidade_de_oferta( );
             
    qtd_valores *atual = *inicio,
                *novo = NULL;
   
    while( quantidade > 0){
        if( atual == NULL ){
            atual = (qtd_valores*)( malloc( sizeof( qtd_valores) ) );
            atual->next = NULL;
            *inicio = atual;
        }else{
            while( atual->next != NULL ){
                atual = atual->next;}
            novo = (qtd_valores*)( malloc( sizeof( qtd_valores) ) );
            atual->next = novo;
            novo->next = NULL;}
        quantidade--;}

    if( quantidade == 0 )
        return true;
    else return false;
}
bool obtem_nome_e_codigo( papel *inicioPapel, acao *inicioAcao ){
    papel *papelAtual = inicioPapel;
    acao *acaoAtual = inicioAcao;
    
    while( papelAtual != NULL ){
        strcpy( acaoAtual->identificacao.nomeDePregao, papelAtual->nomeDePregao );
        strcpy( acaoAtual->identificacao.codigo, papelAtual->codigo );
        papelAtual = papelAtual->next;
        acaoAtual = acaoAtual->next;
    }
    return true;
}
bool gerador_de_quantidade_de_acoes( qtd_valores *inicioLista ){
    qtd_valores *atual = inicioLista;
    srand( time(NULL) );
    
    while( atual != NULL ){
        atual->quantidade = 1 + rand( ) % 1000;
        atual = atual->next;}
    return true;
}
bool gerador_de_valor( qtd_valores *inicioLista ){
    qtd_valores *atual = inicioLista;
    srand( time( NULL) );

    int inteiro;
    float decimal;
    
    while( atual != NULL ){
        inteiro = 1 + rand( ) % 1000;
        decimal = ( 0 + rand( ) % 99 ) * 0.1 ;
        atual->valor = inteiro + decimal ;    
        atual = atual->next;}
    return true;
}
unsigned gerador_de_quantidade_de_oferta( ){
    srand( time(NULL) );
    return 1 + rand( ) % 5;
}
bool visualizar_ofertas_acao( unsigned posicao, acao *inicioVenda, acao *inicioCompra ){
    acao *atualVenda = inicioVenda,
         *atualCompra = inicioCompra;
 
    posicao--;
    
    while( posicao > 0 ){
        posicao--;
        atualCompra = atualCompra->next;
        atualVenda = atualVenda->next;}
    
    printf( "%s\n%s\n\n", atualVenda->identificacao.nomeDePregao, 
            atualVenda->identificacao.codigo );
    printf( "\t\t\t\t\tOFERTAS\n\n" );
    
    qtd_valores *ofertaVendaAtual = atualVenda->valor,
                *ofertaCompraAtual = atualCompra->valor;
    
    printf( "quantidade\tvalor\t\t\tquantidade\tvalor\n\n");
    do{
        printf( "%d\t%.2f\t\t", ofertaVendaAtual->quantidade, ofertaVendaAtual->valor );
                ofertaVendaAtual = ofertaVendaAtual->next;
        while( ofertaCompraAtual != NULL ){
            printf( "%d\t%.2f", ofertaCompraAtual->quantidade, ofertaCompraAtual->valor );
            ofertaCompraAtual = ofertaCompraAtual->next;
            break;}
        puts( "\n" );
    }while( ofertaVendaAtual != NULL );

    printf( "\t\tVENDA\t\t\t\t\t\tCOMPRA\n\n");
}
bool recupera_cotacoes( acao **inicioAcaoVenda, acao **inicioAcaoCompra ){

    
}
bool retira_cotacoes( acao **inicioAcaoVenda, acao **inicioAcaoCompra  ){
    
}
bool salva_cotacoes( acao **inicioVenda, acao **inicioCompra ){

    return true;
}
#endif