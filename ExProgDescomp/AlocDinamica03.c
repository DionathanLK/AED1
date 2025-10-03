#include <stdio.h>
#include <stdlib.h>

int main() {
    int *vetor;
    int tamanho;
    int par = 0;
    int impar = 0;

    printf ( "Digite o tamanho do vetor: " );
    scanf ( "%d" , &tamanho );

    vetor = ( int * ) malloc ( tamanho * sizeof ( int ) );

    if ( vetor == NULL ) {
        printf ( "Erro" );
        return 1;
    }

    printf ( "Digite os %d valores do vetor:\n" , tamanho) ;
    for ( int i = 0; i < tamanho; i++ ) {
        printf ( "Posicao %d: ", i+1 );
        scanf ( "%d", &vetor[i] );
    }

    for ( int i = 0; i < tamanho; i++ ) {

        if ( vetor[i] % 2 == 0 ) {
            par++;
        } else {
            impar++;
        }
    }
    
    printf ( "pares: %d\n" , par );
    printf ( "impar: %d\n" , impar );

    free ( vetor );

    vetor = NULL;

    return 0;
}

//3. Fac¸a um programa que leia do usuario o tamanho de um vetor a ser lido e fac¸a a alocac¸ ´ ao˜
//dinamica de mem ˆ oria. Em seguida, leia do usu ´ ario seus valores e mostre quantos dos ´
//numeros s ´ ao pares e quantos s ˜ ao˜ ´ımpares.