// Bubble Sort Iterative Implementation 

#include <stdlib.h>
#include <stdio.h>

void Swap(int* one, int* two){ // Receives the pointers of the array in these points and changes them
  int backup = *one;
  *one = *two;
  *two = backup;
}

void BubbleSort(int* array,int arraySize){
    int swapped;
    while(swapped != 0){
        swapped = 0;
        for (int i = 0; i < arraySize - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                swapped = 1;
                Swap(&array[i], &array[i + 1]);
            }
    }
    if(swapped == 0){
        return;
    }
    }
}


void PrintArray(int *array,int size){
    for(int i = 0; i < size; i++){
        printf("Number at %d: %d\n",i,array[i]);
    }
}


int main() {
    int arraySize;
    printf("Please enter the size of your array:\n");
    scanf("%d",&arraySize);
    int *array = malloc(arraySize * sizeof(int)); // Allocates a dynamic array according to given input
    if(array == NULL){ // Makes sure we allocated properly
        printf("Error allocating memory! \n");
        return 1;
    }
    int numInsert = 0;
    for(int i = 0; i<arraySize; i++){
        printf("Please enter a number to insert at index: %d\n", i);
        scanf("%d",&numInsert);
        array[i] = numInsert;
    }
    PrintArray(array,arraySize);
    BubbleSort(array,arraySize);
    PrintArray(array,arraySize);
    free(array); // Gotta free that sweet memory
}
