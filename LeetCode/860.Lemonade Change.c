bool lemonadeChange(int* bills, int billsSize) {
    int b5 = 0;  // notas de 5
    int b10 = 0; // notas de 10

    for ( int i = 0; i < billsSize; i++ ) {
        
        switch ( bills[i] )  {
            
            case 5: //recebeu nota de 5
                b5++;
                break; 

            case 10: //recebeu nota de 10

                if ( b5 >= 1 ) { // testa se tem uma nota de 5 para dar troco
                    b5--;  
                    b10++; 
                } else {
                    return false;
                }
                break;


            case 20: 

                if ( b10 >= 1 && b5 >= 1 ) { //testa se tem 1 nota de 10 e outra de 5 para troco
                    b10--;
                    b5--;  
                }

                else if ( b5 >= 3 ) { // se não tiver notas de 10 testa se tem notas de 5
                    b5 = b5 - 3; 
                }

                else {
                    return false;
                }
                break;

        }
    
    }

    return true;
}