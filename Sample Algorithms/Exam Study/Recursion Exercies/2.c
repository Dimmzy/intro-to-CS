// Write a recursive program that returns the number of times the character 'c' appears in a string

#include <stdio.h>

int countC(char arr[],int n){
    if (n < 0){
        return 0;
    }
    if (arr[n] == 'c'){
        return 1 + countC(arr,n-1);
    }
    else {
        return 0 + countC(arr,n-1);
    }
}

void main () {
    char array[] = "czczcz lolezc";
    int arrSize = (sizeof(array) / sizeof(array[0]) -1);
    printf("number of C's: %d",countC(array,arrSize));
}