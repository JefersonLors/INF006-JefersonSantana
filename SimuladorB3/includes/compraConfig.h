#ifndef compraConfig_h
#define compraConfig_h

#include "ofertasConfig.h"

bool incluir_oferta_de_compra( acao* );

///incluir subMenu para possibilitar tirar ofertas de compra do usuário

bool incluir_oferta_de_compra( acao *nova ){
    acao *ofertasCompraLista = NULL,
         *ofertasVendaLista = NULL,
         *novaOfertaCompra = NULL;
  
    recupera_ofertas( &ofertasVendaLista, &ofertasCompraLista );   
    novaOfertaCompra = ofertasCompraLista;
    
    while( strcmp( novaOfertaCompra->identificacao.codigo, nova->identificacao.codigo) != 0 ){
        novaOfertaCompra = novaOfertaCompra->next;}
    
    if( novaOfertaCompra->valor ){
   
        novaOfertaCompra->quantidadeOfertado += nova->quantidadeOfertado;
        
        oferta *ultimaOferta = novaOfertaCompra->valor;
    
        while( ultimaOferta->next != NULL ){ 
            ultimaOferta = ultimaOferta->next; }    
    
        ultimaOferta->next = nova->valor;
        nova->valor->prev = ultimaOferta;
        nova->valor->next = NULL;
        
        ordena_ofertas_de_compra( novaOfertaCompra->valor, novaOfertaCompra->quantidadeOfertado );
    }else{
        papel *inicio = NULL;
        
        recupera_papeis( &inicio );

        while( strcmp( inicio->codigo, nova->identificacao.codigo) != 0 ){
            inicio = inicio->next;}
        
        novaOfertaCompra->quantidadeOfertado += nova->quantidadeOfertado;
        ofertasCompraLista->valor = nova->valor;
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