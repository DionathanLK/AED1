double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {

    double  heaplucro   [classesSize];
    int     heappassou  [classesSize];
    int     heaptotal   [classesSize];

    for ( int i = 0; i < classesSize; i++ ) {

        double p = classes [i] [0]; //total que passaram
        double t = classes [i] [1]; //total de alunos

        double lucro = ( ( p + 1 ) / ( t + 1 )  ) - ( p / t ); //para testar quanto melhor fica com +1 extra

        heaplucro   [i] = lucro;
        heappassou  [i] = p;
        heaptotal   [i] = t; 

        int filho = i;

        while ( filho > 0 ) {
            
            int pai = ( filho - 1 ) / 2; // formula do pai

            // testa se filho tem mais lucro que pai
            if ( heaplucro [filho] > heaplucro [pai] ) {
            
            // troca o lucro
            double tempLucro = heaplucro[filho];
            heaplucro[filho] = heaplucro[pai];
            heaplucro[pai]  = tempLucro;

            // troca o Passou 
            int tempPass = heappassou[filho];
            heappassou[filho] = heappassou[pai];
            heappassou[pai] = tempPass;

            // troca o total
            int tempTotal = heaptotal[filho];
            heaptotal[filho] = heaptotal[pai];
            heaptotal[pai] = tempTotal;

            // O filho subiu
            filho = pai;

            } else {

            break; 

            }
        }
    }

    while ( extraStudents > 0 ) {
        
        // o indice com maior lucro recebe um aluno extra
        heappassou[0]++;
        heaptotal[0]++;

        // recalcular o lucro, quanto de lucro se der +1 para o elemento '0'
        double p = (double)heappassou[0];
        double t = (double)heaptotal[0];
        heaplucro[0] = ( ( p + 1 ) / ( t + 1 ) ) - ( p / t );

        // pai é a posição 0
        int pai = 0;
        
        while ( 1 ) {

            int esquerda = 2 * pai + 1;
            int direita = 2 * pai + 2;
            int maior = pai; // presumindo que pai é maior

            // testa se existe esquerda e se é maior que pai
            if ( esquerda < classesSize && heaplucro[esquerda] > heaplucro[maior] ) {
                maior = esquerda;
            }

            // testa se existe direita e compara com quem for maior (pai ou esquerda)
            if ( direita < classesSize && heaplucro[direita] > heaplucro[maior] ) {
                maior = direita;
            }

            // se pai for maior ta organizado
            if (maior == pai) {
                break; //para o loop
            } 
            //se passou pra cá, não tá e precisa troca o pai com filho que ganhou
    
            // troca lucro
            double tempLucro = heaplucro[pai];
            heaplucro[pai] = heaplucro[maior];
            heaplucro[maior] = tempLucro;

            // troca passou
            int tempPass = heappassou[pai];
            heappassou[pai] = heappassou[maior];
            heappassou[maior] = tempPass;

            // troca total
            int tempTotal = heaptotal[pai];
            heaptotal[pai] = heaptotal[maior];
            heaptotal[maior] = tempTotal;

            // pai vira filho e repete o laço
            pai = maior;
        }

        extraStudents--; // retirar aluno extra pos alocar
    }

    // calcular media
    double somaTotal = 0.0;
    
    for ( int i = 0; i < classesSize; i++ ) {
        somaTotal += (double) heappassou[i] / heaptotal[i];
    }

    return somaTotal / classesSize;
}    

