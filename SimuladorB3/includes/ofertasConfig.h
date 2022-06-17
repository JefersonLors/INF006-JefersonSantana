#ifndef ofertasConfig_h
#define ofertasConfig_h

#include <time.h>
#include <string.h>
#include "papelConfig.h"

typedef struct qtd_valores{
    int quantidade;
    float valor;
    struct qtd_valores *prev;
    struct qtd_valores *next;
}qtd_valores;

typedef struct acoes{
    papel identificacao;
    qtd_valores *valor;
    unsigned quantidadeOfertado;
    struct acoes *prev;
    struct acoes *next;
}acao;

bool gerador_de_ofertas( void );
bool gerador_de_lista_de_oferta( qtd_valores**, acao* );
bool gerador_de_quantidade_de_acoes( qtd_valores* );
bool gerador_de_valor_de_venda( qtd_valores* );
bool gerador_de_valor_de_compra( qtd_valores* );
unsigned gerador_de_quantidade_de_oferta( void );

void ordena_ofertas_de_venda( qtd_valores*, unsigned );
void ordena_ofertas_de_compra( qtd_valores*, unsigned );

bool preenche_ofertas( acao**, bool );

bool obtem_nome_e_codigo( acao* );

bool recupera_ofertas( acao**, acao** );
bool recupera_lista_de_oferta( qtd_valores**, unsigned, FILE* );

bool atualiza_ofertas( unsigned );
bool retira_oferta( void );
bool exclui_lista_de_oferta( qtd_valores** );
void limpa_lista_de_acoes( acao** );
bool salva_ofertas( acao**, acao** );

bool visualizar_ofertas_acao( unsigned );

///adicionar cotacao quando transacoes forem inseridas

bool gerador_de_ofertas(  ){
    acao *novoVenda = NULL,
         *novoCompra = NULL;
    
    novoVenda = (acao*)(malloc(sizeof(acao) ) );
    novoVenda->valor = NULL;
    gerador_de_lista_de_oferta( &novoVenda->valor, novoVenda );
    preenche_ofertas( &novoVenda, true );
    novoVenda->prev = NULL;
    novoVenda->next = NULL;
    
    novoCompra = (acao*)(malloc(sizeof(acao) ) );
    novoCompra->valor = NULL;
    gerador_de_lista_de_oferta( &novoCompra->valor, novoCompra );
    preenche_ofertas( &novoCompra, false );
    novoCompra->prev = NULL;
    novoCompra->next = NULL;

    acao *primeirasAcoesVenda = NULL,
         *primeirasAcoesCompra = NULL,
         *ultimaAcaoVenda = NULL,
         *ultimaAcaoCompra = NULL;
    
    if( recupera_ofertas( &primeirasAcoesVenda, &primeirasAcoesCompra ) ){
        dados.quantidade_de_acoes++;
        ultimaAcaoVenda = primeirasAcoesVenda;
        ultimaAcaoCompra = primeirasAcoesCompra;
        
        while( ultimaAcaoVenda->next != NULL && ultimaAcaoCompra->next != NULL ){
            ultimaAcaoVenda = ultimaAcaoVenda->next;
            ultimaAcaoCompra = ultimaAcaoCompra->next;}
        ultimaAcaoVenda->next = novoVenda; 
        novoVenda->prev = ultimaAcaoVenda;
        ultimaAcaoCompra->next = novoCompra;
        novoCompra->prev = ultimaAcaoCompra;
        
        if( salva_ofertas( &primeirasAcoesVenda, &primeirasAcoesCompra ) ){
            limpa_lista_de_acoes( &primeirasAcoesVenda );
            limpa_lista_de_acoes( &primeirasAcoesCompra );
            return true; }
    }else{
        dados.quantidade_de_acoes++;
        if( salva_ofertas( &novoVenda, &novoCompra ) ){
            limpa_lista_de_acoes( &novoVenda );
            limpa_lista_de_acoes( &novoCompra );
            return true;}}
   
    return false;
}
bool gerador_de_lista_de_oferta( qtd_valores **inicio, acao *acao ){
    unsigned quantidade = acao->quantidadeOfertado = gerador_de_quantidade_de_oferta( );
             
    qtd_valores *atual = *inicio,
                *novo = NULL;
   
    while( quantidade > 0){
        if( atual == NULL ){
            atual = (qtd_valores*)( malloc( sizeof( qtd_valores) ) );
            atual->next = NULL;
            atual->prev = NULL;
            *inicio = atual;
        }else{
            while( atual->next != NULL ){
                atual = atual->next;}
            novo = (qtd_valores*)( malloc( sizeof( qtd_valores) ) );
            atual->next = novo;
            novo->prev = atual;
            novo->next = NULL;}
        quantidade--;}

    if( quantidade == 0 )
        return true;
    else return false;
}
unsigned gerador_de_quantidade_de_oferta( ){
    srand( time(NULL) );
    return 2 + rand( ) % 6;
}
bool preenche_ofertas( acao **acao, bool sinal ){
    if( obtem_nome_e_codigo( *acao ) ){
        if( gerador_de_quantidade_de_acoes( (*acao)->valor ) ){
            if( sinal ){
                if( gerador_de_valor_de_compra( (*acao)->valor ) ){
                    ordena_ofertas_de_compra( (*acao)->valor, (*acao)->quantidadeOfertado );
                    return true;}
            }else{
                if( gerador_de_valor_de_venda( (*acao)->valor ) ){
                    ordena_ofertas_de_venda( (*acao)->valor, (*acao)->quantidadeOfertado );
                    return true;}}
        }    
    }
    return false; 
}
bool obtem_nome_e_codigo( acao *acao ){
    papel *papelAtual = NULL,
          *primeiroPapel = NULL;
    
    recupera_papeis( &primeiroPapel );
    papelAtual = primeiroPapel;

    if( papelAtual != NULL ){
        while( papelAtual->next != NULL ){
            papelAtual = papelAtual->next;}
        strcpy( acao->identificacao.nomeDePregao, papelAtual->nomeDePregao );
        strcpy( acao->identificacao.codigo, papelAtual->codigo );
        limpa_lista_de_papeis( &primeiroPapel );
        return true;
    }
    limpa_lista_de_papeis( &primeiroPapel );
    return false;
}
bool gerador_de_quantidade_de_acoes( qtd_valores *inicioLista ){
    qtd_valores *atual = inicioLista;
    srand( time( NULL) );
    
    while( atual != NULL ){
        atual->quantidade = 1 + rand( ) % 1000;
        atual = atual->next;}
    return true;
}
bool gerador_de_valor_de_venda( qtd_valores *inicioLista ){
    qtd_valores *atual = inicioLista;
    
    srand( time( NULL) );

    int inteiro;
    float decimal;
    
    while( atual != NULL ){
        inteiro = 1 + rand( ) % 1000;
        decimal = ( 0 + rand( ) % 99 ) * 0.1;
        atual->valor = inteiro + decimal;  
        atual = atual->next;}
    
    return true;
}
bool gerador_de_valor_de_compra( qtd_valores *inicioLista ){
    qtd_valores *atual = inicioLista;
              
    srand( time( NULL) );

    int inteiro;
    float decimal;
    
    while( atual != NULL ){
        inteiro = 1 + rand( ) % 1000;
        decimal = ( 0 + rand( ) % 99 ) * 0.1;
        atual->valor = inteiro + decimal;  
        atual = atual->next;}

    //if( inicioLista->next ){
        //ordena_ofertas_de_compra( inicioLista );}
    
    return true;
}
bool visualizar_ofertas_acao( unsigned posicao ){
    acao *atualVenda = NULL,
         *atualCompra = NULL,
         *inicioVenda = NULL,
         *inicioCompra = NULL;

    if( recupera_ofertas( &atualVenda, &atualCompra ) ){
 
        inicioVenda = atualVenda;
        inicioCompra = atualCompra;
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
        limpa_lista_de_acoes( &inicioVenda );
        limpa_lista_de_acoes( &inicioCompra);
        return true;
    }else return false;
}
bool recupera_ofertas( acao **inicioAcaoVenda, acao **inicioAcaoCompra ){
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
                        atualAcaoVenda->identificacao.codigo, &atualAcaoVenda->quantidadeOfertado );
                recupera_lista_de_oferta( &atualAcaoVenda->valor, atualAcaoVenda->quantidadeOfertado, 
                                          arquivoAcoesValorVenda );
                atualAcaoVenda->next = NULL;
                *inicioAcaoVenda = atualAcaoVenda;
            }else{
                while( atualAcaoVenda->next != NULL ){
                    atualAcaoVenda = atualAcaoVenda->next;}
                
                novoAcaoVenda = (acao*)(malloc(sizeof(acao) ) );
                novoAcaoVenda->valor = NULL;
                fscanf( arquivoAcoesValorVenda, "%s%s%d", novoAcaoVenda->identificacao.nomeDePregao, 
                        novoAcaoVenda->identificacao.codigo, &novoAcaoVenda->quantidadeOfertado );

                recupera_lista_de_oferta( &novoAcaoVenda->valor, novoAcaoVenda->quantidadeOfertado,
                                          arquivoAcoesValorVenda );
                 
                novoAcaoVenda->next = NULL;
                atualAcaoVenda->next = novoAcaoVenda;
            }
            if( atualAcaoCompra == NULL ){
                atualAcaoCompra = (acao*)(malloc(sizeof(acao) ) );
                atualAcaoCompra->valor = NULL;
                fscanf( arquivoAcoesValorCompra, "%s%s%d", atualAcaoCompra->identificacao.nomeDePregao, 
                        atualAcaoCompra->identificacao.codigo, &atualAcaoCompra->quantidadeOfertado );
                
                recupera_lista_de_oferta( &atualAcaoCompra->valor, atualAcaoCompra->quantidadeOfertado,
                                          arquivoAcoesValorCompra );
                atualAcaoCompra->next = NULL;
                *inicioAcaoCompra = atualAcaoCompra;
            }else{
                while( atualAcaoCompra->next != NULL ){
                    atualAcaoCompra = atualAcaoCompra->next;}
                novoAcaoCompra = (acao*)(malloc(sizeof(acao) ) );
                novoAcaoCompra->valor = NULL;
                fscanf( arquivoAcoesValorCompra, "%s%s%d", novoAcaoCompra->identificacao.nomeDePregao, 
                        novoAcaoCompra->identificacao.codigo, &novoAcaoCompra->quantidadeOfertado );
                recupera_lista_de_oferta( &novoAcaoCompra->valor, novoAcaoCompra->quantidadeOfertado,
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
bool retira_oferta( ){
     acao *inicioAcaoVenda = NULL, 
          *inicioAcaoCompra = NULL;
    
    papel *atual = NULL,
          *primeiro = NULL;

    if( recupera_papeis( &primeiro ) ){
        atual = primeiro;
     
        recupera_ofertas( &inicioAcaoVenda, &inicioAcaoCompra );
            
        acao *atualVenda = inicioAcaoVenda,
             *atualCompra = inicioAcaoCompra,
             *atualVendaBackup = NULL,
             *atualCompraBackup = NULL;
    
        //retira o primeiro elemento da lista
        if( strcmp( atual->codigo, atualVenda->identificacao.codigo ) != 0 ){
            dados.quantidade_de_acoes--;
            exclui_lista_de_oferta( &atualVenda->valor );
            exclui_lista_de_oferta( &atualCompra->valor );
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
                    dados.quantidade_de_acoes--;
                    exclui_lista_de_oferta( &atualVenda->valor );
                    exclui_lista_de_oferta( &atualCompra->valor );
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
                dados.quantidade_de_acoes--;
                exclui_lista_de_oferta( &atualVenda->valor );
                exclui_lista_de_oferta( &atualCompra->valor );
                free( atualVenda );
                free( atualCompra );
                atualVenda = NULL;
                atualCompra = NULL;
                atualVendaBackup->next = NULL; 
                atualCompraBackup->next = NULL; 
                }
        }
    }else{ dados.quantidade_de_acoes--; }
    if ( salva_ofertas( &inicioAcaoVenda, &inicioAcaoCompra ) ){
        limpa_lista_de_papeis( &primeiro );
        limpa_lista_de_acoes( &inicioAcaoVenda );
        limpa_lista_de_acoes( &inicioAcaoCompra ); 
        return true;}
    return false;
}
bool salva_ofertas( acao **inicioVenda, acao **inicioCompra ){
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
                     atualVenda->identificacao.codigo, atualVenda->quantidadeOfertado ); 
            
            while( atualV != NULL  ){
                fprintf( arquivoAcoesValorVenda, "%-6d%-6.2f\n", atualV->quantidade, atualV->valor );
                atualV = atualV->next; }
            fprintf( arquivoAcoesValorCompra, "%s\n%s\n%d\n", 
                     atualCompra->identificacao.nomeDePregao, 
                     atualCompra->identificacao.codigo, atualCompra->quantidadeOfertado );
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
bool atualiza_ofertas( unsigned posicao ){
    acao *antigaAcaoVenda = NULL,
         *antigaAcaoCompra = NULL,
         *inicioAcaoVenda = NULL,
         *inicioAcaoCompra = NULL; 

    recupera_ofertas( &antigaAcaoVenda, &antigaAcaoCompra );

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
                            if( gerador_de_valor_de_venda( antigaAcaoVenda->valor ) ){
                                ordena_ofertas_de_venda( antigaAcaoVenda->valor, antigaAcaoVenda->quantidadeOfertado );
                                if( gerador_de_valor_de_compra( antigaAcaoCompra->valor ) ){ 
                                    ordena_ofertas_de_compra( antigaAcaoCompra->valor, antigaAcaoCompra->quantidadeOfertado);
                                    if( salva_ofertas( &inicioAcaoVenda, &inicioAcaoCompra ) ){ 
                                        limpa_lista_de_acoes( &inicioAcaoVenda );
                                        limpa_lista_de_acoes( &inicioAcaoCompra );
                                        return true;}}}}}}}}}
    limpa_lista_de_acoes( &inicioAcaoVenda );
    limpa_lista_de_acoes( &inicioAcaoCompra );
    return false;
}
void limpa_lista_de_acoes( acao **inicio ){
    acao *atual = *inicio; 
    while( atual != NULL ){
        acao *backup = atual->next;
        exclui_lista_de_oferta( &atual->valor );
        free( atual );
        atual = NULL;
        atual = backup;
    }
    *inicio = atual;
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
void ordena_ofertas_de_venda( qtd_valores *inicio, unsigned tamanho ){
    qtd_valores *atual = inicio;
    int i = 0,
        j = 0;
        
    float valorAtual;
    float *listaTemp = (float*)malloc( tamanho*sizeof(float) );
    
    while( atual != NULL ){
        listaTemp[i++] = atual->valor;
        atual = atual->next;}

    for (int x = 1; x < tamanho; x++) {
        valorAtual = listaTemp[x];
        j = x - 1;
        while (j >= 0 && listaTemp[j] < valorAtual) {
            listaTemp[j + 1] = listaTemp[j];
            j = j - 1;}
        listaTemp[j + 1] = valorAtual;}

    i = 0;
    atual = inicio;

    while( atual != NULL ){
        atual->valor = listaTemp[i++];
        atual = atual->next;}
    free( listaTemp );
}
void ordena_ofertas_de_compra( qtd_valores *inicio, unsigned tamanho ){
    qtd_valores *atual = inicio;
    int i = 0,
        j = 0;
        
    float valorAtual;
    float *listaTemp = (float*)malloc( tamanho*sizeof(float) );
    
    while( atual != NULL ){
        listaTemp[i++] = atual->valor;
        atual = atual->next;}

    for (int x = 1; x < tamanho; x++) {
        valorAtual = listaTemp[x];
        j = x - 1;
        while (j >= 0 && listaTemp[j] > valorAtual) {
            listaTemp[j + 1] = listaTemp[j];
            j = j - 1;}
        listaTemp[j + 1] = valorAtual;}

    i = 0;
    atual = inicio;

    while( atual != NULL ){
        atual->valor = listaTemp[i++];
        atual = atual->next;}
    free( listaTemp );
}
#endif