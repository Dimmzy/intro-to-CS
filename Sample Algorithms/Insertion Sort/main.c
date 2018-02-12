// Insertion Sort Iterative Implementation 
// Time complexity at worst case: O(n^2) - when reversed
// Time complexity at best case: Omega(n) - when ordered completely

#include <stdlib.h>
#include <stdio.h>


void InsertionSort(int* array, int arraySize){
	int i, key, j;
	for(i = 1; i < arraySize; i++){ // Iterates through the array from the first index to the end
		key = array[i]; // We set the "key" to be our i'th value
		j = i-1; // j is going to be used as an index prior to i
		while (j >= 0 && array[j] > key){ // we check if the value of j'th elements are larger than the key
			array[j+1] = array[j]; // if they are we insert them forward
			j--;
		}
		array[j+1] = key; // and eventually we insert our i'th number (the key) into it's correct position
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
    InsertionSort(array,arraySize);
    PrintArray(array,arraySize);
    free(array); // Gotta free that sweet memory
}
