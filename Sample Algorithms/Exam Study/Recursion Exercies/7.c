// Write a recursive function that arranges the elements in the array in order

#include <stdio.h>
#define SWAPPED 1

void Swap(int* a,int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

void Sort(int* array,int size,int current,int flag){
    if (current < 1){
        if(flag){
            return Sort(array,size,size-1,0);
        }
        return;
    }
    if(array[current] < array[current-1]){
        Swap(&array[current],&array[current-1]);
        return Sort(array,size,current,SWAPPED);
    }
    return Sort(array,size,--current,flag);
}



void main() {
    int arr[] = {1,23,6456,-22,4324,121};
    int arraySize = (sizeof(arr)/sizeof(arr[0]));
    Sort(arr,arraySize,arraySize-1,0);
    for(int i = 0; i < arraySize;i++){
      printf("[%d]",arr[i]);
    }
}