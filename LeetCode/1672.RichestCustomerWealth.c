int maximumWealth(int** accounts, int accountsSize, int* accountsColSize) {
    int rico = 0;

    for ( int i = 0; i < accountsSize; i++ ) {
        int soma = 0;

        for ( int j = 0; j < accountsColSize[i]; j++ ) {
            soma += accounts[i][j];
        }

        if ( soma > rico ) {
            rico = soma;
        }
    }

    return rico;
}