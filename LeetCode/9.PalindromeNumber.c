bool isPalindrome(int x) {

    long rev = 0; //estava dando erro de armazenamento para um tipo int
    int num = x;

    if  ( x < 0 ) { //verifica se o num é negativo
        return false;

    } else  {
    
        if ( x == 0) {
            return true;

        }
    }

    while ( num != 0 ) {
        rev = (rev * 10) + (num % 10); //move o reverso para a esquerda, pega o ultimo numero de x, assim pegamos oque falta da divisão
        num = num / 10; //tirar o ultimo numero que pegamos de x
    }

    if ( x == (int)rev ) { //transforma o reverso em inteiro de volta para testar
        return true;

    }   else {
        return false;
        
    }

}