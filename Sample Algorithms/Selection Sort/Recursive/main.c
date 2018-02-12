// Selection Sort Recursive Implementation 
// Time complexity is O(n^2) && Omega(n^2) == Theta(n^2) found by using Arithmetic Series Sum

#include <stdlib.h>
#include <stdio.h>

void Swap(int* one, int* two){ // Receives the pointers of the array in these points and changes them
  int backup = *one;
  *one = *two;
  *two = backup;
}

void SelectionSort(int *array,int size,int startingLocation){
    int minNumber = array[startingLocation]; // We receieve a starting index ("subarray") to check from
    int minIndex = startingLocation;
    for(int i = startingLocation; i < size; i++){ // Loop through the array from starting point
        if(array[i] < minNumber){ // If we find a smaller number than the first one, set it and save index
            minNumber = array[i];
            minIndex = i;
        }
    }
    Swap(&array[minIndex],&array[startingLocation]); // Swap the value at the first index with smallet found
    if(startingLocation == size){ // If we iterated through all of the list, end the function
        return;
    }
    startingLocation++; // Increment the starting index by one
    return SelectionSort(array,size,startingLocation); // Call recursively with the next index
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
    int *array = malloc(arraySize * sizeof(int)); // Allocates dynamic memory for our array according to input
    if(array == NULL){ // Checks if we allocated properly
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
    SelectionSort(array,arraySize,0); // First call of the selection sort function, starts at index zero
    PrintArray(array,arraySize);
}
