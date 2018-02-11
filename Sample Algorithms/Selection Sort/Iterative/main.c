// Selection Sort Iterative Implementation 
// Time complexity is O(n^2) && Omega(n^2) == Theta(n^2) found by two nested loops

#include <stdlib.h>
#include <stdio.h>

void Swap(int* one, int* two){ // Receives the pointers of the array in these points and changes them
  int backup = *one;
  *one = *two;
  *two = backup;
}

void SelectionSort(int *array,int size){
    int minIndex;
    for (int i = 0 ;i < size - 1; i++){ // checks every index until size -1
        minIndex = i;
        for(int j = i + 1; j < size; j++){ // Compares every element of the list to find the smallest one
            if(array[j] < array[minIndex])
                minIndex = j;
        }
        Swap(&array[minIndex],&array[i]); // Swaps the number in the i index with the smallest one found
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
    SelectionSort(array,arraySize);
    PrintArray(array,arraySize);
    free(array); // Gotta free that sweet memory
}
