#ifndef transacoesConfig_h
#define transacoesConfig_h

#include "ofertasConfig.h"

bool transacao( unsigned );
bool valida_transacao( oferta*, oferta* );
void ajusta_lista_de_ofertas( oferta**, oferta**, acao*, acao* );
bool realiza_transacao( oferta*, oferta* );
void historico_de_transacoes( oferta*, oferta*, float );

bool transacao( unsigned posicaoPapel ){
    acao *inicioAcaoVenda = NULL,
         *inicioAcaoCompra = NULL,
         *acaoVendaAtual = NULL,
         *acaoCompraAtual = NULL;
    
    oferta *ofertaVendaAtual = NULL,
           *ofertaCompraAtual = NULL;
    
    unsigned backupPosicaoPapel = posicaoPapel,
             backupQuantidadeOfertadasCompra = 0;

    unsigned contador = 0;
    
    recupera_ofertas( &inicioAcaoVenda, &inicioAcaoCompra );
    acaoVendaAtual = inicioAcaoVenda;
    acaoCompraAtual = inicioAcaoCompra;
    
    while( posicaoPapel > 1 ){
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
                if( valida_transacao( ofertaVendaAtual, ofertaCompraAtual ) ){
                    if( realiza_transacao( ofertaVendaAtual, ofertaCompraAtual ) ){
                        contador++;
                        break;} 
                }ofertaVendaAtual = ofertaVendaAtual->next;
            }ofertaCompraAtual = ofertaCompraAtual->next;
        }
        
        ajusta_lista_de_ofertas( &acaoVendaAtual->valor, &acaoCompraAtual->valor, acaoVendaAtual, acaoCompraAtual );
 
        salva_ofertas( &inicioAcaoVenda, &inicioAcaoCompra );
        limpa_lista_de_acoes( &inicioAcaoVenda );
        limpa_lista_de_acoes( &inicioAcaoCompra );
        
        if( contador ){
            return true;}   
    }
    
    return false;
}

bool valida_transacao( oferta *venda, oferta *compra ){
    if( venda->valor <= compra->valor ){
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
            venda->quantidade -= compra->quantidade;}
        return true;
    }else if( venda->valor < compra->valor ){
        if( venda->quantidade == compra->quantidade ){
            compra->quantidade = venda->quantidade = 0;
            venda->valor = compra->valor = 0;
        }else if( venda->quantidade > compra->quantidade ){
            venda->quantidade -= compra->quantidade;}
        return true;}
    return false;
}
void ajusta_lista_de_ofertas( oferta **ofertaVendaAtual, oferta **ofertaCompraAtual, 
                               acao *acaoVendaAtual, acao *acaoCompraAtual ){
    oferta *ofertaVenda = *ofertaVendaAtual,
           *ofertaCompra = *ofertaCompraAtual,
           *ofertaVendaBackup = NULL,
           *ofertaCompraBackup = NULL;

    while( ofertaCompra->next && ofertaCompra->quantidade == 0 ){
        (*ofertaCompraAtual) = ofertaCompra->next;
        ofertaCompra->next->prev = NULL;
        free( ofertaCompra );
        acaoCompraAtual->quantidadeOfertado--;
        ofertaCompra = (*ofertaCompraAtual);}
       
    if( acaoCompraAtual->quantidadeOfertado == 1 ){
        if( ofertaCompra->quantidade == 0 ){
            free( (*ofertaCompraAtual) );
            (*ofertaCompraAtual) = NULL;}
            acaoCompraAtual->quantidadeOfertado--;
    }else{
        ofertaCompraBackup = ofertaCompra;
        ofertaCompra = ofertaCompra->next;
        
        while( ofertaCompra ){
          
            if( ofertaCompra->quantidade == 0 ){
                ofertaCompraBackup->next = ofertaCompra->next;
                
                if( ofertaCompra->next )
                    ofertaCompra->next->prev = ofertaCompraBackup;
                
                free( ofertaCompra );
                acaoCompraAtual->quantidadeOfertado--;
                ofertaCompra = ofertaCompraBackup->next;
            }else{
                ofertaCompra = ofertaCompra->next;
            }
        }
    }
   
    while( ofertaVenda->next && ofertaVenda->quantidade == 0 ){
        (*ofertaVendaAtual) = ofertaVenda->next;
        ofertaVenda->next->prev = NULL;
        free( ofertaVenda );
        acaoVendaAtual->quantidadeOfertado--;
        ofertaVenda = (*ofertaVendaAtual);
    }
    if( acaoVendaAtual->quantidadeOfertado == 1 ){
        if( ofertaVenda->quantidade == 0 ){
            free( (*ofertaVendaAtual) );
            (*ofertaVendaAtual) = NULL;}
            acaoVendaAtual->quantidadeOfertado--;
    }else{
        ofertaVendaBackup = ofertaVenda ;
        ofertaVenda = ofertaVenda->next;
        while( ofertaVenda ){
            if( ofertaVenda->quantidade == 0 ){
                ofertaVendaBackup->next = ofertaVenda->next;
                if( ofertaVenda->next )
                    ofertaVenda->next->prev = ofertaVendaBackup;
                free( ofertaVenda );
                acaoVendaAtual->quantidadeOfertado--;
                ofertaVenda = ofertaVendaBackup->next;
            }else{
                ofertaVenda = ofertaVenda->next;
            }
        }
    }
}
#endif