#include <stdio.h>

int maior( int v1, int v2 ){
  printf( "\n  %d é o maior \n\n", ( v1 > v2 ? v1 : v2 ) );
}

int main() {
    int valor1, valor2;
    printf( "\nDigite dois valores para saber o maior\n");
    printf ("  1 valor = ");
    scanf("%d", &valor1);
    printf("  2 valor = ");
    scanf("%d", &valor2);

    maior( valor1, valor2 );

    return 0;
}
  