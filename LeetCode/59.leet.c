/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    
    int** matriz = malloc ( n * sizeof (int*) );
    *returnColumnSizes = malloc ( n * sizeof (int) );

    for ( int i = 0; i < n; i++ ) {
        matriz[i] = malloc ( n * sizeof (int) );
        ( *returnColumnSizes ) [i] = n;
    }

    *returnSize = n;

    int ncima       = 0;        
    int ndireita    = n - 1;    
    int nbaixo      = n - 1;
    int nesquerda   = 0;

    int o = 1;

    while ( ncima <= nbaixo && nesquerda <= ndireita ) {

       
        for ( int i = nesquerda; i <= ndireita; i++ ) {
            matriz [ ncima ] [ i ] = o;
            o++; 
        }
        ncima++; 

        for ( int j = ncima; j <= nbaixo; j++ ) {
            matriz [ j ] [ ndireita ] = o;
            o++;
        }
        ndireita--; 

        if ( nbaixo >= ncima ) {
            for ( int i = ndireita; i >= nesquerda; i--) {
                matriz [ nbaixo ] [ i ] = o;
                o++;
            }
            nbaixo--; 
        }

        if ( nesquerda <= ndireita ) {
            // 3. Mudado para i >= ncima (estava i <= ncima num loop decrescente)
            for ( int i = nbaixo; i >= ncima; i-- ) {
                matriz [ i ] [ nesquerda ] = o;
                o++;
            }
            nesquerda++; 
        }
    }

    return matriz;
}