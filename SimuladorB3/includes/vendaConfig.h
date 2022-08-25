#ifndef vendaConfig_h
#define vendaConfig_h

#include "ofertasConfig.h"
#include "carteiraConfig.h"

bool incluir_oferta_de_venda( acao* );

bool incluir_oferta_de_venda( acao *nova ){
    acao *ofertasCompraLista = NULL,
         *ofertasVendaLista = NULL,
         *novaOfertaVenda = NULL;
  
    recupera_ofertas( &ofertasVendaLista, &ofertasCompraLista );   
    novaOfertaVenda = ofertasVendaLista;
    
    while( strcmp( novaOfertaVenda->identificacao.codigo, nova->identificacao.codigo) != 0 ){
        novaOfertaVenda = novaOfertaVenda->next;}
    
    if( novaOfertaVenda->valor ){
   
        novaOfertaVenda->quantidadeOfertado += nova->quantidadeOfertado;
        
        oferta *ultimaOferta = novaOfertaVenda->valor;
    
        while( ultimaOferta->next != NULL ){ 
            ultimaOferta = ultimaOferta->next; }    
    
        ultimaOferta->next = nova->valor;
        nova->valor->prev = ultimaOferta;
        nova->valor->next = NULL;
        
        ordena_ofertas_de_venda( novaOfertaVenda->valor, novaOfertaVenda->quantidadeOfertado );
    }else{
        novaOfertaVenda->quantidadeOfertado += nova->quantidadeOfertado;
        ofertasVendaLista->valor = nova->valor;
    }
    if( salva_ofertas( &ofertasVendaLista, &ofertasCompraLista  ) ){
        limpa_lista_de_acoes( &ofertasVendaLista );
        limpa_lista_de_acoes( &ofertasCompraLista );
        return true;
    }else{
        limpa_lista_de_acoes( &ofertasVendaLista );
        limpa_lista_de_acoes( &ofertasCompraLista );
        return false;}
}

#endif