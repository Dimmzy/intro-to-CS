// Write a recursive function that divides a number array into two arrays, even and odds

#include <stdio.h>
#include <stdlib.h>

void divideArray(int* array,int** arrsPtr,int n,int countE,int countO){
    if(n < 0){
        return;
    }
    if(array[n] % 2 == 0){
        arrsPtr[0][countE] = array[n];
        divideArray(array,arrsPtr,n-1,++countE,countO);
    }
    else{
        arrsPtr[1][countO] = array[n];
        divideArray(array,arrsPtr,n-1,countE,++countO);
    }
}

int** create2DArray(int numElements){
    int** p;
    p = (int**)malloc(2 * sizeof(int*));
    p[0] = (int*)malloc(numElements * sizeof(int));
    p[1] = (int*)malloc(numElements * sizeof(int));
    return p;
}

void main() {
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int arrSize = sizeof(arr)/sizeof(arr[0]) -1;
    int** twoDArr = create2DArray((int)(arrSize/2)+1);
    divideArray(arr,twoDArr,arrSize,0,0);
    int j = 1;
    for(int i = (int)(arrSize/2)+1;i > 0 ;i--){
        if(twoDArr[0][i] != 0){
        printf("Even #%d : %d\n",j,twoDArr[0][i]);
        j++;
        }
    }
    j = 1;
    for(int i = (int)(arrSize/2)+1;i > 0 ;i--){
        if(twoDArr[0][i] != 0){
        printf("Odd #%d : %d\n",j,twoDArr[1][i]);
        j++;
        }
    }
    free(twoDArr);
}