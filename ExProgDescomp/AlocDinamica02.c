#include <stdio.h>
#include <stdlib.h>

int main() {
    int *vetor; 
    int tamanho; 

    printf ( "Digite o tamanho: " );
    scanf ( "%d" , &tamanho );

    vetor = ( int * ) malloc ( tamanho * sizeof ( int ) );

    if ( vetor == NULL ) {
        printf ( "Erro" );
        return 1;
    }

    printf ( "Digite os %d valores do vetor:\n" , tamanho );
    for (int i = 0; i < tamanho; i++) {
        printf ( "Posicao %d: " , i );
        scanf ( "%d" , &vetor[i] );
    }

    printf ( "O vetor lido foi:\n " );

    for ( int i = 0; i < tamanho; i++ ) {
        printf ( "%d, " , vetor[i] );
    }

    free ( vetor );

    vetor = NULL;

    return 0;
}

//2. Fac¸a um programa que leia do usuario o tamanho de um vetor a ser lido e fac¸a a alocac¸ ´ ao˜
//dinamica de mem ˆ oria. Em seguida, leia do usu ´ ario seus valores e imprima o vetor lido.