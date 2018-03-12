// Write a recursive program that calculates the sum of all the elements in an array

#include <stdio.h>


int calcSum(int array[],int n){
    if (n < 0){
        return 0;
    }
    return array[n] + calcSum(array,n-1);
}

void main() {
    int a[] = {1,2,3};
    int sum = calcSum(a,sizeof(a)/sizeof(a[0])-1);
    printf("%d",sum);
}