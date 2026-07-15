#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int romanToInt(char* s);

int main() {
    printf("%d\n", romanToInt("MCMXCIV"));
    return 0;
}

int romanToInt(char* s) {
    if(s==NULL) return 0;
    int len = strlen(s);
    int nums[len];
    int total = 0;
    int lastValue = 0, currentValue;

    for (int i = len - 1; i >= 0; i--) {
        switch (s[i]) {
            case 'I':
                nums[i] = 1;
                break;
            case 'V':
                nums[i] = 5;
                break;
            case 'X':
                nums[i] = 10;
                break;
            case 'L':
                nums[i] = 50;
                break;
            case 'C':
                nums[i] = 100;
                break;
            case 'D':
                nums[i] = 500;
                break;
            case 'M':
                nums[i] = 1000;
                break;
        }

        currentValue = nums[i];

        if (lastValue > currentValue)
            total -= currentValue;
        else
            total += currentValue;

        lastValue = currentValue;
    }

    return total;
}