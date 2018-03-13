// Write a recursive program that checks if two sorted arrays have a shared element

#include <stdio.h>
#include <stdlib.h>
typedef enum {FALSE,TRUE} bool;

bool SharedElement(char** arrays,int end,int start,int size){
    if(end != start){
    if(arrays[0][end] == arrays[0][start]){
        return TRUE;
    }
    else{
        return SharedElement(arrays, end, ++start,size);
    }
    }
    else{
        if(end == -1){
            return FALSE;
        }
        return (arrays, --end, size, size);
    }


}

char** create2DArray(int size) {
    char** arrOfArr = (char**)malloc(2*sizeof(char*));
    arrOfArr[0] = (char*)malloc(size * sizeof(char));
    arrOfArr[1] = (char*)malloc(size * sizeof(char));
    arrOfArr[0] = "hel";
    arrOfArr[1] = "hga";
    return arrOfArr;
}

void main () {
    char** arrOfArr = create2DArray(4);
    int size = 4;
    printf("Has shared element (0/1): %d",SharedElement(arrOfArr, 4, 0, 4));

}