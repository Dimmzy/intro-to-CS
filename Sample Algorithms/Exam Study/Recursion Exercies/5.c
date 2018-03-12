// Write a recursive function that replaces the small characters with large characters


#include <stdio.h>
#include <string.h>
#define CONVERT 32

void replaceLowercase(char* arr,int n){
    if(n < 0){
        return;
    }
    if(arr[n] >= 97 && arr[n] <=122){
        arr[n] -= CONVERT;
    } 
    replaceLowercase(arr,n-1);
}

void main() {
    char array[] = "HeLlo worLd";
    int end = strlen(array)-1;
    replaceLowercase(array,end);
    printf("new string is: %s",array);
}