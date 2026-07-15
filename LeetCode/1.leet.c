#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize);

int main() {
    int vec[] = {2, 7, 11, 15};
    int size = 4;
    int target = 9;
    int returnSize;

    int* result;

    result = twoSum(vec, size, target, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", *(result + i));
    }

    return 0;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result;
    *returnSize = 0;

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (*(nums + i) + *(nums + j) == target) {
                result = (int*)malloc(2 * sizeof(int));
                *(result+0) = i;
                *(result+1) = j;
                *returnSize = 2;

                return result;
            }
        }
    }

    return 0;
}