#ifndef cotacoesConfig_h
#define cotacoesConfig_h

#include <time.h>
#include <string.h>
#include "papelConfig.h"

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

bool gerador_de_cotacoes( );
bool gerador_de_lista_de_oferta( qtd_valores**, acao* );

bool preenche_cotacoes( acao**  );
bool retira_cotacoes(  );
bool obtem_nome_e_codigo( acao* );

bool gerador_de_quantidade_de_acoes( qtd_valores* );
bool gerador_de_valor( qtd_valores* );
unsigned gerador_de_quantidade_de_oferta( void );

bool recupera_cotacoes( acao**, acao** );
bool recupera_lista_de_oferta( qtd_valores**, unsigned, FILE* );

bool atualiza_cotacoes( unsigned );
bool exclui_lista_de_oferta( qtd_valores** );

bool salva_cotacoes( acao**, acao** );

bool visualizar_ofertas_acao( unsigned );

bool gerador_de_cotacoes(  ){
    acao *atualVenda = NULL,
         *atualCompra = NULL,
         *novoVenda = NULL,
         *novoCompra = NULL;
    
    unsigned quantidadeAcoes = dados.quantidade_de_papel - dados.quantidade_de_acoes;

    while( quantidadeAcoes > 0 ){
        if( atualVenda == NULL ){
            atualVenda = (acao*)(malloc(sizeof(acao) ) );
            atualVenda->valor = NULL;
            gerador_de_lista_de_oferta( &atualVenda->valor, atualVenda );
            preenche_cotacoes( &atualVenda );
            atualVenda->next = NULL;
        }else{
            while( atualVenda->next != NULL ){
                atualVenda = atualVenda->next;}
            novoVenda = (acao*)(malloc(sizeof(acao) ) );
            novoVenda->valor = NULL;
            gerador_de_lista_de_oferta( &novoVenda->valor, novoVenda );
            preenche_cotacoes( &novoVenda );
            novoVenda->next = NULL;
            atualVenda->next = novoVenda;
        }
        if( atualCompra == NULL ){
            atualCompra = (acao*)(malloc(sizeof(acao) ) );
            atualCompra->valor = NULL;
            gerador_de_lista_de_oferta( &atualCompra->valor, atualCompra );
            preenche_cotacoes( &atualCompra );
            atualCompra->next = NULL;
        }else{
            while( atualCompra->next != NULL ){
                atualCompra = atualCompra->next;}
            novoCompra = (acao*)(malloc(sizeof(acao) ) );
            novoCompra->valor = NULL;
            gerador_de_lista_de_oferta( &novoCompra->valor, novoCompra );
            preenche_cotacoes( &novoCompra );
            novoCompra->next = NULL;
            atualCompra->next = novoCompra;
        }
        quantidadeAcoes--;}
        
    acao *primeirasAcoesVenda = NULL,
         *primeirasAcoesCompra = NULL;

    if( recupera_cotacoes( &primeirasAcoesVenda, &primeirasAcoesCompra ) ){
       dados.quantidade_de_acoes += dados.quantidade_de_papel - dados.quantidade_de_acoes;
        while( primeirasAcoesVenda->next != NULL && primeirasAcoesCompra != NULL ){
            primeirasAcoesVenda = primeirasAcoesVenda->next;
            primeirasAcoesCompra = primeirasAcoesCompra->next;}
        primeirasAcoesVenda->next = atualVenda;
        primeirasAcoesCompra->next = atualCompra;
        if( quantidadeAcoes == 0 ){
            if( salva_cotacoes( &primeirasAcoesVenda, &primeirasAcoesCompra ) ){
                return true;   
            }}
    }else{
        dados.quantidade_de_acoes += dados.quantidade_de_papel - dados.quantidade_de_acoes;
        if( quantidadeAcoes == 0 ){
            if( salva_cotacoes( &atualVenda, &atualCompra ) ){
                return true;   
            }}}
   
    return false;
}
bool preenche_cotacoes( acao **acao ){
    if( obtem_nome_e_codigo( *acao ) ){
        if( gerador_de_quantidade_de_acoes( (*acao)->valor ) ){
            if( gerador_de_valor( (*acao)->valor ) ){
                    return true;}}}
    return false; 
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
bool obtem_nome_e_codigo( acao *acao ){
    papel *papelAtual = NULL;
    
    recuperaPapeis( &papelAtual );

    if( papelAtual != NULL ){
        
        while( papelAtual->next != NULL ){
            papelAtual = papelAtual->next;}
        strcpy( acao->identificacao.nomeDePregao, papelAtual->nomeDePregao );
        strcpy( acao->identificacao.codigo, papelAtual->codigo );
        return true;
    }return false;
    
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
bool visualizar_ofertas_acao( unsigned posicao ){
    acao *atualVenda = NULL,
         *atualCompra = NULL;

    recupera_cotacoes( &atualVenda, &atualCompra );
    
    while( posicao > 1 ){
        posicao--;
        atualCompra = atualCompra->next;
        atualVenda = atualVenda->next;}
    
    printf( "%s\n%s\n\n", atualVenda->identificacao.nomeDePregao, 
            atualVenda->identificacao.codigo );
    printf( "%30s\n\n", "OFERTAS" );
    
    qtd_valores *ofertaVendaAtual = atualVenda->valor,
                *ofertaCompraAtual = atualCompra->valor;
    
    printf( "%10s%11s%21s%11s\n\n", "Quantidade", "Valor", "Quantidade", "Valor" );
    while( ofertaVendaAtual != NULL ){
        printf( "%10d%11.2f\t\t", ofertaVendaAtual->quantidade, ofertaVendaAtual->valor );
                ofertaVendaAtual = ofertaVendaAtual->next;
        while( ofertaCompraAtual != NULL ){
            printf( "%14d%11.2f", ofertaCompraAtual->quantidade, ofertaCompraAtual->valor );
            ofertaCompraAtual = ofertaCompraAtual->next;
            break;}
        puts( "\n" );}
    
    printf( "%15s%33s\n\n", "VENDA", "COMPRA" );
}
bool recupera_cotacoes( acao **inicioAcaoVenda, acao **inicioAcaoCompra ){
acao *atualAcaoVenda = *inicioAcaoVenda,
         *atualAcaoCompra = *inicioAcaoCompra,
         *novoAcaoCompra = NULL,
         *novoAcaoVenda = NULL;

    FILE *arquivoAcoesValorVenda = fopen( acoesValorVenda, "r" ),
         *arquivoAcoesValorCompra = fopen( acoesValorCompra, "r" ),
         *arquivoDadosConfig = fopen( dadosConfig, "r" );

    fscanf( arquivoDadosConfig, "%d%d", &dados.quantidade_de_papel, &dados.quantidade_de_acoes);
    unsigned quantidadeAcoes = dados.quantidade_de_acoes;
    
    if( dados.quantidade_de_acoes > 0 ){
        while( quantidadeAcoes > 0 ){
            if( atualAcaoVenda == NULL ){
                atualAcaoVenda = (acao*)(malloc(sizeof(acao) ) );
                atualAcaoVenda->valor = NULL;
                fscanf( arquivoAcoesValorVenda, "%s%s%d", atualAcaoVenda->identificacao.nomeDePregao, 
                        atualAcaoVenda->identificacao.codigo, &atualAcaoVenda->quantidadeCotado );
                recupera_lista_de_oferta( &atualAcaoVenda->valor, atualAcaoVenda->quantidadeCotado, 
                                          arquivoAcoesValorVenda );
                atualAcaoVenda->next = NULL;
                *inicioAcaoVenda = atualAcaoVenda;
            }else{
                while( atualAcaoVenda->next != NULL ){
                    atualAcaoVenda = atualAcaoVenda->next;}
                
                novoAcaoVenda = (acao*)(malloc(sizeof(acao) ) );
                novoAcaoVenda->valor = NULL;
                fscanf( arquivoAcoesValorVenda, "%s%s%d", novoAcaoVenda->identificacao.nomeDePregao, 
                        novoAcaoVenda->identificacao.codigo, &novoAcaoVenda->quantidadeCotado );

                recupera_lista_de_oferta( &novoAcaoVenda->valor, atualAcaoVenda->quantidadeCotado,
                                          arquivoAcoesValorVenda );
                 
                novoAcaoVenda->next = NULL;
                atualAcaoVenda->next = novoAcaoVenda;
               
            }
            if( atualAcaoCompra == NULL ){
                atualAcaoCompra = (acao*)(malloc(sizeof(acao) ) );
                atualAcaoCompra->valor = NULL;
                fscanf( arquivoAcoesValorCompra, "%s%s%d", atualAcaoCompra->identificacao.nomeDePregao, 
                        atualAcaoCompra->identificacao.codigo, &atualAcaoCompra->quantidadeCotado );
                
                recupera_lista_de_oferta( &atualAcaoCompra->valor, atualAcaoCompra->quantidadeCotado,
                                          arquivoAcoesValorCompra );
                atualAcaoCompra->next = NULL;
                *inicioAcaoCompra = atualAcaoCompra;
            }else{
                while( atualAcaoCompra->next != NULL ){
                    atualAcaoCompra = atualAcaoCompra->next;}
                novoAcaoCompra = (acao*)(malloc(sizeof(acao) ) );
                novoAcaoCompra->valor = NULL;
                fscanf( arquivoAcoesValorCompra, "%s%s%d", novoAcaoCompra->identificacao.nomeDePregao, 
                        novoAcaoCompra->identificacao.codigo, &novoAcaoCompra->quantidadeCotado );
                recupera_lista_de_oferta( &novoAcaoCompra->valor, novoAcaoCompra->quantidadeCotado,
                                          arquivoAcoesValorCompra );
                novoAcaoCompra->next = NULL;
                atualAcaoCompra->next = novoAcaoCompra;
            }
            quantidadeAcoes--;}
            fclose( arquivoAcoesValorVenda );
            fclose( arquivoAcoesValorCompra );   
            fclose( arquivoDadosConfig );
            if( quantidadeAcoes == 0 ){
                return true;}
    }
    fclose( arquivoAcoesValorVenda );
    fclose( arquivoAcoesValorCompra );   
    fclose( arquivoDadosConfig );
    return false; 
}
bool recupera_lista_de_oferta( qtd_valores **inicio, unsigned quantidade,  FILE *arquivoAcoesValor ){        
    qtd_valores *atual = *inicio,
                *novo = NULL;

    while( quantidade > 0){
        if( atual == NULL ){
            atual = (qtd_valores*)( malloc( sizeof( qtd_valores) ) );
            fscanf( arquivoAcoesValor , "%d%f", &atual->quantidade, &atual->valor  );
            atual->next = NULL;
            *inicio = atual;
        }else{
            while( atual->next != NULL ){
                atual = atual->next;}
            novo = (qtd_valores*)( malloc( sizeof( qtd_valores) ) );
            fscanf( arquivoAcoesValor, "%d%f", &novo->quantidade, &novo->valor  );
            atual->next = novo;
            novo->next = NULL;}
        quantidade--;}
    if( quantidade == 0 )
        return true;
    else return false;
}
bool retira_cotacoes( ){
     acao *inicioAcaoVenda = NULL, 
          *inicioAcaoCompra = NULL;
    
    papel *atual;
    
    recuperaPapeis( &atual );
    recupera_cotacoes( &inicioAcaoVenda, &inicioAcaoCompra );
        
    acao *atualVenda = inicioAcaoVenda,
         *atualCompra = inicioAcaoCompra,
         *atualVendaBackup = NULL,
         *atualCompraBackup = NULL;

    ///liberar a segunda lista de valores e quantidades
    //retira o primeiro elemento da lista
    if( strcmp( atual->codigo, atualVenda->identificacao.codigo ) != 0 ){
        dados.quantidade_de_papel--;
        atualVendaBackup = atualVenda->next;
        atualCompraBackup = atualCompra->next;
        free( atualVenda );
        free( atualCompra );
        atualVenda = NULL;
        atualCompra = NULL;
        inicioAcaoVenda = atualVendaBackup;
        inicioAcaoCompra = atualCompraBackup;
    }else{
        ///retira elementos centrais da lista
        atualVendaBackup = atualVenda;
        atualCompraBackup = atualCompra;
        atualVenda = atualVenda->next;
        atualCompra = atualCompra->next;
        atual = atual->next;
        
        while( atual != NULL ){
            if( strcmp( atual->codigo, atualVenda->identificacao.codigo ) != 0 ){
                dados.quantidade_de_papel--;
                atualVendaBackup->next = atualVenda->next;
                atualCompraBackup->next = atualCompra->next; 
                free( atualVenda );
                free( atualCompra );
                atualVenda = NULL;
                atualCompra = NULL;
                break;}
           
            atualVendaBackup = atualVenda;
            atualCompraBackup = atualCompra;
            atualVenda = atualVenda->next;
            atualCompra = atualCompra->next;
            atual = atual->next;
        }
        ///retira o último elemento da lista
        if( atual == NULL && atualCompra != NULL || atualVenda != NULL ){
            atualVendaBackup->next = atualVenda->next;
            atualCompraBackup->next = atualCompra->next; 
            free( atualVenda );
            free( atualCompra );
            atualVenda = NULL;
            atualCompra = NULL;}
    }
    salva_cotacoes( &inicioAcaoVenda, &inicioAcaoCompra );
}
bool salva_cotacoes( acao **inicioVenda, acao **inicioCompra ){
    acao *atualVenda = *inicioVenda,
         *atualCompra = *inicioCompra;

    FILE *arquivoAcoesValorVenda = fopen( acoesValorVenda, "w" ),
         *arquivoAcoesValorCompra = fopen( acoesValorCompra, "w" ),
         *arquivoDadosConfig = fopen( dadosConfig, "w" );

    fprintf( arquivoDadosConfig, "%d\n%d", dados.quantidade_de_papel, dados.quantidade_de_acoes );
    
    if( arquivoAcoesValorVenda && arquivoAcoesValorVenda ){
        while( atualVenda != NULL ||  atualCompra != NULL ){
            qtd_valores *atualV = atualVenda->valor,
                        *atualC = atualCompra->valor;
            
            fprintf( arquivoAcoesValorVenda, "%s\n%s\n%d\n", 
                     atualVenda->identificacao.nomeDePregao, 
                     atualVenda->identificacao.codigo, atualVenda->quantidadeCotado ); 
            
            while( atualV != NULL  ){
                fprintf( arquivoAcoesValorVenda, "%-6d%-6.2f\n", atualV->quantidade, atualV->valor );
                atualV = atualV->next; }
            
            fprintf( arquivoAcoesValorCompra, "%s\n%s\n%d\n", 
                     atualCompra->identificacao.nomeDePregao, 
                     atualCompra->identificacao.codigo, atualCompra->quantidadeCotado );
            while( atualC != NULL ){
                fprintf( arquivoAcoesValorCompra, "%-6d%-6.2f\n", atualC->quantidade, atualC->valor ); 
                atualC = atualC->next;}
            
            atualVenda = atualVenda->next;
            atualCompra = atualCompra->next;
        }
        fclose( arquivoAcoesValorVenda );
        fclose( arquivoAcoesValorCompra );
        fclose( arquivoDadosConfig );
        return true;
    }else{ return false;} 
}
bool atualiza_cotacoes( unsigned posicao ){
    acao *antigaAcaoVenda = NULL,
         *antigaAcaoCompra = NULL,
         *inicioAcaoVenda = NULL,
         *inicioAcaoCompra = NULL; 

    recupera_cotacoes( &antigaAcaoVenda, &antigaAcaoCompra );

    inicioAcaoVenda = antigaAcaoVenda;
    inicioAcaoCompra = antigaAcaoCompra;
    
    while( posicao > 1 ){
        antigaAcaoVenda = antigaAcaoVenda->next;
        antigaAcaoCompra = antigaAcaoCompra->next;
        posicao--;}
    
    if( exclui_lista_de_oferta( &antigaAcaoVenda->valor ) ){
        if( exclui_lista_de_oferta( &antigaAcaoCompra->valor ) ){ 
            if( gerador_de_lista_de_oferta( &antigaAcaoVenda->valor, antigaAcaoVenda ) ){ 
                if( gerador_de_lista_de_oferta( &antigaAcaoCompra->valor, antigaAcaoCompra ) ){ 
                   if( gerador_de_quantidade_de_acoes( antigaAcaoVenda->valor ) ){ 
                        if( gerador_de_quantidade_de_acoes( antigaAcaoCompra->valor ) ){ 
                            if( gerador_de_valor( antigaAcaoVenda->valor ) ){ 
                                if( gerador_de_valor( antigaAcaoCompra->valor ) ){ 
                                    if( salva_cotacoes( &inicioAcaoVenda, &inicioAcaoCompra ) ){ 
                                        return true;}}}}}}}}}
    return false;
}
bool exclui_lista_de_oferta( qtd_valores **inicio ){      
    qtd_valores *atual = *inicio;
    
    while( atual != NULL ){
        qtd_valores *backup = atual->next;
        free( atual );
        atual = NULL;
        atual = backup;}
    
    *inicio = atual;

    if( *inicio == NULL ){
        return true;
    }else return false;
}
#endif