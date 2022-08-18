#ifndef transacoesConfig_h
#define transacoesConfig_h

#include "ofertasConfig.h"

bool transacao( unsigned );
bool valida_transacao( oferta*, oferta*, papel* );
void ajusta_lista_de_ofertas( oferta**, oferta**, acao*, acao* );
bool realiza_transacao( oferta*, oferta* );
void historico_de_transacoes( oferta*, oferta*, float );

bool transacao( unsigned posicaoPapel ){
    acao *inicioAcaoVenda = NULL,
         *inicioAcaoCompra = NULL,
         *acaoVendaAtual = NULL,
         *acaoCompraAtual = NULL;

    papel *inicioPapel = NULL,
          *papelAtual = NULL;
        
    oferta *ofertaVendaAtual = NULL,
           *ofertaCompraAtual = NULL;
    
    unsigned backupPosicaoPapel = posicaoPapel,
             backupQuantidadeOfertadasCompra = 0;

    unsigned contador = 0;
    
    recupera_ofertas( &inicioAcaoVenda, &inicioAcaoCompra );
    recupera_papeis( &inicioPapel );
    
    acaoVendaAtual = inicioAcaoVenda;
    acaoCompraAtual = inicioAcaoCompra;
    papelAtual = inicioPapel;
    
    while( posicaoPapel > 1 ){
        papelAtual = papelAtual->next;
        acaoVendaAtual = acaoVendaAtual->next;
        acaoCompraAtual = acaoCompraAtual->next;
        posicaoPapel--;}
    
    if( acaoVendaAtual->valor != NULL ){
          ofertaVendaAtual = acaoVendaAtual->valor;}
   
    if( acaoCompraAtual->valor != NULL ){
         ofertaCompraAtual = acaoCompraAtual->valor;}

    if( ofertaVendaAtual != NULL && ofertaCompraAtual != NULL ){
        while( ofertaCompraAtual != NULL ){
            ofertaVendaAtual = acaoVendaAtual->valor;
            while( ofertaVendaAtual != NULL ){
                if( valida_transacao( ofertaVendaAtual, ofertaCompraAtual, papelAtual ) ){
                    if( realiza_transacao( ofertaVendaAtual, ofertaCompraAtual ) ){
                        contador++;
                        break;} 
                }ofertaVendaAtual = ofertaVendaAtual->next;
            }ofertaCompraAtual = ofertaCompraAtual->next;}
        
        ajusta_lista_de_ofertas( &acaoVendaAtual->valor, &acaoCompraAtual->valor, acaoVendaAtual, acaoCompraAtual );
        salva_ofertas( &inicioAcaoVenda, &inicioAcaoCompra );
        salva_papeis( inicioPapel );
        limpa_lista_de_acoes( &inicioAcaoVenda );
        limpa_lista_de_acoes( &inicioAcaoCompra );
        
        if( contador > 0 ){
            return true;}   
    }return false;
}

bool valida_transacao( oferta *venda, oferta *compra, papel *papelAtual ){
    if( venda->valor <= compra->valor ){
        papelAtual->cotacao = venda->valor;
        return true;
    }else{
        return false;}
}
bool realiza_transacao( oferta *venda, oferta *compra ){
    if( venda->valor == compra->valor ){
        if( venda->quantidade == compra->quantidade ){
            venda->valor = compra->valor = 0;
            compra->quantidade = venda->quantidade = 0;
        }else if( venda->quantidade > compra->quantidade  ){
            venda->quantidade -= compra->quantidade;
            compra->quantidade = 0;
            compra->valor = 0;}
    }else if( venda->valor < compra->valor ){
        if( venda->quantidade == compra->quantidade ){
            compra->quantidade = venda->quantidade = 0;
            venda->valor = compra->valor = 0;
        }else if( venda->quantidade > compra->quantidade ){
            venda->quantidade -= compra->quantidade;
            compra->quantidade = 0;
            compra->valor = 0;}
    }else return false;
    return true;
}
void ajusta_lista_de_ofertas( oferta **ofertaVendaAtual, oferta **ofertaCompraAtual, acao *acaoVendaAtual, acao *acaoCompraAtual ){
    oferta *ofertaVenda = *ofertaVendaAtual,
           *ofertaCompra = *ofertaCompraAtual,
           *ofertaVendaBackup = NULL,
           *ofertaCompraBackup = NULL;

    unsigned quantidadeDeOfertas = acaoCompraAtual->quantidadeOfertado;

    while( quantidadeDeOfertas > 0 ){
        ofertaCompra = *ofertaCompraAtual;
        if( ofertaCompra->quantidade == 0 ){
            *ofertaCompraAtual = ofertaCompra->next; 
            if( *ofertaCompraAtual ){
                (*ofertaCompraAtual)->prev = NULL;}
            free( ofertaCompra );
            ofertaCompra = NULL;
            quantidadeDeOfertas = acaoCompraAtual->quantidadeOfertado--;
        }else{
            ofertaCompraBackup = ofertaCompra;
            ofertaCompra = ofertaCompra->next;
            while( ofertaCompra ){
                if( ofertaCompra->quantidade == 0 ){
                    ofertaCompraBackup->next = ofertaCompra->next;
                    if( ofertaCompra->next ){
                        ofertaCompra->next->prev = ofertaCompraBackup;}
                    free( ofertaCompra );
                    quantidadeDeOfertas = acaoCompraAtual->quantidadeOfertado--;
                    break;}
                ofertaCompraBackup = ofertaCompra;
                ofertaCompra = ofertaCompra->next;}
        }quantidadeDeOfertas--;}

    quantidadeDeOfertas = acaoVendaAtual->quantidadeOfertado;
    
    while( quantidadeDeOfertas > 0 ){
        ofertaVenda = *ofertaVendaAtual;
        if( ofertaVenda->quantidade == 0 ){
            *ofertaVendaAtual = ofertaVenda->next;
            if( *ofertaVendaAtual ){
                (*ofertaVendaAtual)->prev = NULL;}
            free( ofertaVenda );
            ofertaVenda = NULL;
            quantidadeDeOfertas = acaoVendaAtual->quantidadeOfertado--;
        }else{
            ofertaVendaBackup = ofertaVenda;
            ofertaVenda = ofertaVenda->next;
            while( ofertaVenda ){
                if( ofertaVenda->quantidade == 0 ){
                    ofertaVendaBackup->next = ofertaVenda->next;
                    if( ofertaVenda->next ){
                        ofertaVenda->next->prev = ofertaVendaBackup;}
                    free( ofertaVenda );
                    quantidadeDeOfertas = acaoVendaAtual->quantidadeOfertado--;
                    break;}
                ofertaVendaBackup = ofertaVenda;
                ofertaVenda = ofertaVenda->next;}
        }quantidadeDeOfertas--;}
}
#endif