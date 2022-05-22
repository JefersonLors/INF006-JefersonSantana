#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tipo{
	int info;
	struct tipo *prox;
}Paciente;

Paciente *inicio = NULL;

Paciente *inserir_lista( Paciente *l, int i ){
	Paciente *novo = malloc( sizeof(Paciente) );
    novo->info = i;
    novo->prox = l; 
	return novo;
}
void consultar_lista( Paciente *inicio ){
	Paciente *referencia;
	for( referencia = inicio; referencia != NULL; referencia = referencia->prox){
		printf("%d\n", referencia->info);}
}
Paciente *retiraInicio( Paciente *LISTA ){
	if( LISTA == NULL ){
		printf("Lista ja esta vazia\n");
		return NULL;
	}else{
		Paciente *tmp = LISTA->prox;
        free( LISTA );
		return tmp;}
}
Paciente *retiraFim( Paciente *LISTA ){
	if( LISTA == NULL ){
		printf( "Lista ja vazia\n\n" );
		return NULL;
	}else{
		Paciente *penultimo = NULL,
		         *ultimo = LISTA;
        if( ultimo->prox == NULL ){
            return NULL;
        }else{
    		while( ultimo->prox != NULL ){
    			penultimo = ultimo;
    			ultimo = ultimo->prox;}
            free( ultimo );
            penultimo->prox = NULL;
            return LISTA;
        }
	}
}
Paciente *BuscaDado(int dado, Paciente *ptr){
    while (ptr !=NULL) {
        if (ptr->info == dado){
    		return (ptr);
    	}else{
    		ptr = ptr->prox;} 
    }return NULL;
}

bool RemoveDado( int dado, Paciente **ptr ){
	Paciente *busca = *ptr; 
	Paciente *anterior = NULL;
	
    while( busca != NULL){
		if( busca->info == dado ){
			if( anterior != NULL ){
				anterior->prox = busca->prox;
			}else{
				*ptr = busca->prox;}
            free(busca);
            return 1;}
		anterior = busca;
		busca = busca->prox;
	}return 0;
}

int main() {
	int opcao = 0,
        elemento = 0;
	Paciente *lista = NULL;

	do{
    	printf( "\nDIGITE ( -1 encerra ):\n"
                "0 - Inserir Elemento\n"
                "1 - Excluir no fim\n"
                "2 - Excluir no inicio\n"
                "3 - Excluir um elemento pesquisado\n"
                "4 - Buscar um elemento na lista\n"
                "5 - Listar elementos\n"
                "\n  = " );

    	scanf( "%d", &opcao );

        if( opcao == 0 ){
            int valor = 0;
            printf( "\nDigite os valores para inserir ( -1 encerra )\n" );
            do{
                printf( "- " );
                scanf( "%d", &valor );
                    if( valor != -1 ){
                        lista = inserir_lista( lista, valor );
                    }else break;
            }while( 1 );
        }else if( opcao == 1 ){ 
            lista = retiraFim( lista );
            printf( "\nLista atualizada:\n" );
            consultar_lista(lista);
        }else if( opcao == 2 ){ 
            lista = retiraInicio( lista );
            printf( "\nLista atualizada:\n" );
            consultar_lista(lista);
        }else if( opcao == 3 ){ 
            int valor = 0;
        
    		do{
                printf( "\nDigite o valor para ser excluido ( -1 encerra )\n" );
                printf( "\n- " );
                scanf( "%d", &valor );
                    if( valor != -1 ){
                		if( RemoveDado( valor, &lista ) ){
                			printf("\ndepois da exclusao pelo elemento pesquisado.....: \n");
                			consultar_lista(lista);
                		}else{
                			printf("\nnao foi possivel remover, elemento nao encontrado\n");}
                    }else break;
            }while( 1 );
        }else if( opcao == 4 ){ 
            int valor = 0;
            
            do{
                printf( "\nDigite o valor para busca ( -1 encerra )\n" );
                printf( "\n- " );
                scanf( "%d", &valor );
                    if( valor != -1 ){
                		if( BuscaDado( valor,lista ) == NULL ){
                			printf("\nelemento nao encontrado\n");
                		}else{
                			printf("\ncontem o elemento pesquisado\n");}
                    }else break;
            }while( 1 );
        }else if( opcao == 5 ){
            consultar_lista( lista ); 
        }else{
            printf( "\nOpcao Invalida!\n");}
	}while( opcao != -1 );
    printf( "\n\tPrograma Encerrado\n" );
    return 0;
}