#include <stdio.h>

int ordenar( int v1, int v2 ){
  int soma, primeiro;
  soma = v2+v1;
  primeiro = ( v1 > v2 ? v1 : v2 );
  printf( "\n  %d  %d \n", primeiro, (soma-primeiro) );

}

int main() {
    int valor1, valor2;
    printf( "\nDigite dois valores para ordernar crescentemente\n");
    printf ("  1 valor = ");
    scanf("%d", &valor1);
    printf("  2 valor = ");
    scanf("%d", &valor2);

    ordenar( valor1, valor2 );

    return 0;
}
  