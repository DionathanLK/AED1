#include <stdio.h>
#include <stdlib.h> 

int main() {
    int *array;
    int tamanho = 5;

    array = ( int *) malloc ( tamanho * sizeof ( int ) );

    if ( array == NULL ) {
        printf ( "Erro" );
        return 1;
    }

    printf ( "Digite 5 numeros:\n" );
    for ( int i = 0; i < tamanho; i++ ) {
        printf ( "Numero: " );
        scanf ( "%d" , &array[i] );
    }

    printf ( "Os numeros sao:\n" );
    for ( int i = 0; i < tamanho; i++ ) {
        printf ( "%d " , array[i] );
    }
    
    free ( array );

    array = NULL;

    return 0;
}

// 1. Crie um programa que:
//(a) Aloque dinamicamente um array de 5 numeros inteiros, ´
//(b) Pec¸a para o usuario digitar os 5 n ´ umeros no espac¸o alocado, ´
//(c) Mostre na tela os 5 numeros, ´
//(d) Libere a memoria alocada. 