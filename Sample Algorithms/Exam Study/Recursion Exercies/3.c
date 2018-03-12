// Write a recursive program that inverts the order of the elements in the array

#include <stdio.h>

void inverseArray(char arr[],int start,int end){
    if (start == end || start > end){
        return ;
    }
    printf("Switching: %c with %c\n",arr[start],arr[end]);
    char temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
    inverseArray(arr,start+1,end-1);
}

void main () {
    char array[] = "domo arigatou mr.robato";
    int arrSize = (sizeof(array)/sizeof(array[0]) -2);
    inverseArray(array,0,arrSize);
    printf("Inversed Array: %s",array);
}