char* largestNumber(int* nums, int numsSize) {

    //para guardar os int
    char s1[50];
    char s2[50];
    int temp;

    for ( int i = 0; i < numsSize; i++ ) {
        for ( int j = 0; j < numsSize - i - 1; j++) {
            sprintf ( s1, "%d%d", nums[j], nums[j+1]); //combinar o primeiro com segundo
            sprintf ( s2, "%d%d", nums[j+1], nums[j]); //combinar segundo com primeiro

            if ( strcmp (s2, s1) > 0) { //teste se s1+s2 e maior, para inverter
                temp        = nums[j];
                nums[j]     = nums [j+1];
                nums[j+1]   = temp;

            }
        }
    }

    if ( nums[0] == 0 ) { //testa se e zero
        char* zero = (char*)malloc(2); //
        strcpy ( zero, "0" );
        return zero;

    }

    char* output = (char*)malloc(1500 * sizeof(char));

    output[0] = '\0'; //começar vazio

    char buffer[20];

    for ( int i = 0; i < numsSize; i++ ) {
        sprintf ( buffer, "%d", nums[i] );
        strcat ( output, buffer );

    }

    return output;
        
}