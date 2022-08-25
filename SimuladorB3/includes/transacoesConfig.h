 #ifndef transacoesConfig_h
#define transacoesConfig_h

#include "ofertasConfig.h"
#include "carteiraConfig.h"
#include <time.h>

bool transacao( unsigned );
bool valida_transacao( oferta*, oferta* );
void ajusta_lista_de_ofertas( oferta**, oferta**, acao*, acao* );
bool realiza_transacao( oferta*, oferta*, papel*, bool );
void registra_transacao_usuario( float, float, int, char*, char*, bool );

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
                if( valida_transacao( ofertaVendaAtual, ofertaCompraAtual ) ){
                    if( realiza_transacao( ofertaVendaAtual, ofertaCompraAtual, papelAtual, true ) ){
                        contador++;
                        break;} 
                }ofertaVendaAtual = ofertaVendaAtual->next;
            }ofertaCompraAtual = ofertaCompraAtual->next;}
       
        ajusta_lista_de_ofertas( &acaoVendaAtual->valor, &acaoCompraAtual->valor, acaoVendaAtual, acaoCompraAtual );
    
        if( acaoVendaAtual->valor != NULL ){
            ofertaVendaAtual = acaoVendaAtual->valor;}
       
        if( acaoCompraAtual->valor != NULL ){
            ofertaCompraAtual = acaoCompraAtual->valor;}
            
       
        while( ofertaVendaAtual != NULL ){
            ofertaCompraAtual = acaoCompraAtual->valor;
            while( ofertaCompraAtual != NULL ){
                if( valida_transacao( ofertaCompraAtual, ofertaVendaAtual ) ){
                    if( realiza_transacao( ofertaCompraAtual, ofertaVendaAtual, papelAtual, false ) ){
                        contador++;
                        break;} 
                }ofertaCompraAtual = ofertaCompraAtual->next;
            }ofertaVendaAtual = ofertaVendaAtual->next;}
           
        ajusta_lista_de_ofertas( &acaoVendaAtual->valor, &acaoCompraAtual->valor, acaoVendaAtual, acaoCompraAtual );
        salva_ofertas( &inicioAcaoVenda, &inicioAcaoCompra );
        
        limpa_lista_de_acoes( &inicioAcaoVenda );
        limpa_lista_de_acoes( &inicioAcaoCompra );
        
        if( contador > 0 ){
            return true;}   
    }return false;
}

bool valida_transacao( oferta *venda, oferta *compra ){
    if( venda->valor <= compra->valor ){
        return true;
    }else{
        return false;}
}
bool realiza_transacao( oferta *venda, oferta *compra, papel *acaoAtual, bool sinalizador ){
    ///colocar nomes melhores para as variaveis venda e compra, pois 
    ///uma também pode lista corresponder a outra, isto é, a lista de
    ///venda é passada como de compra e o contrário também.
    if( venda->valor == compra->valor ){
        if( venda->quantidade == compra->quantidade ){
            if( compra->user ){
                registra_transacao_usuario( acaoAtual->cotacao, compra->valor, compra->quantidade, 
                                         acaoAtual->nomeDePregao, acaoAtual->codigo, sinalizador );
            }
            venda->valor = compra->valor = 0;
            compra->quantidade = venda->quantidade = 0;

            return true;
        }else if( venda->quantidade > compra->quantidade  ){
            if( compra->user ){
                registra_transacao_usuario( acaoAtual->cotacao, compra->valor, compra->quantidade, 
                                         acaoAtual->nomeDePregao, acaoAtual->codigo, sinalizador );}
            venda->quantidade -= compra->quantidade;
            compra->quantidade = 0;
            compra->valor = 0;
            return true;}
    }else if( venda->valor < compra->valor ){
        if( venda->quantidade == compra->quantidade ){
            if( compra->user ){
                registra_transacao_usuario( acaoAtual->cotacao, (compra->valor + venda->quantidade)/2,
                                         compra->quantidade, acaoAtual->nomeDePregao, acaoAtual->codigo, sinalizador );}
            compra->quantidade = venda->quantidade = 0;
            venda->valor = compra->valor = 0;
            return true;
        }else if( venda->quantidade > compra->quantidade ){
            if( compra->user ){
                registra_transacao_usuario( acaoAtual->cotacao, (compra->valor + venda->quantidade)/2, 
                                         compra->quantidade, acaoAtual->nomeDePregao, acaoAtual->codigo, sinalizador );}
            venda->quantidade -= compra->quantidade;
            compra->quantidade = 0;
            compra->valor = 0;
            return true;}
    }return false;
}
void registra_transacao_usuario( float cotacaoAtual, float valor, int quantidade, 
                                 char *nome, char *codigo, bool sinalizador ){
    const unsigned tamanhoDataAtual = 30;  
    time_t dataAtualEmSegundos; 
    struct tm *horaDataAtualSemFormato = NULL;
    char dataAtualFormatada[tamanhoDataAtual]; 
    FILE *TRANSACOES = fopen( historicoTransacao, "a+" ),
         *dadosGerais = fopen( dadosConfig, "r" );

    fscanf( dadosGerais, "%u%u%u%u", &dados.quantidade_de_papel, 
            &dados.quantidade_de_acoes, &dados.quantidade_de_transacoes,
            &dados.acoes_diferentes_na_carteira);
    
    fclose( dadosGerais );

    dadosGerais = fopen( dadosConfig, "w" );
    
    time( &dataAtualEmSegundos );
    
    horaDataAtualSemFormato = localtime( &dataAtualEmSegundos );

    strftime( dataAtualFormatada, tamanhoDataAtual, "%c", horaDataAtualSemFormato );

    if( TRANSACOES ){
        tira_espacos_vazios( dataAtualFormatada );
        fprintf( TRANSACOES, "%-*s\t%-*.2f\t%-*d\t%-*.2f\t%-*s\t%-*s\t%u\n", 
                 tamanhoDataAtual, dataAtualFormatada, 4,cotacaoAtual, 4,
                 quantidade, 4,valor, TAM_CODIGO, codigo, TAM_NOME_PREGAO, nome, sinalizador  );
    }
    dados.quantidade_de_transacoes++;

    fprintf( dadosGerais, "%u%u%u%u", dados.quantidade_de_papel, 
            dados.quantidade_de_acoes, dados.quantidade_de_transacoes,
            dados.acoes_diferentes_na_carteira);
    
    fclose( dadosGerais );
    fclose( TRANSACOES );
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