// Write a function that checks if an array is a palindrome

#include <stdio.h>
#include <string.h>

typedef enum {FALSE,TRUE} bool;


bool isPalindrome(char* arr,int start,int end){
    if (start == end || start > end){
        return TRUE;
    }
    printf("Comparing %c with %c\n",arr[start],arr[end]);
    if (arr[start] == arr[end]){
        return isPalindrome(arr,start+1,end-1);
    }
    else{
        return FALSE;
    }
}

void main () {
    char* arrOne = "aa";
    int sizeArrOne = strlen(arrOne)-1;
    char* arrTwo = "blob";
    int sizeArrTwo = strlen(arrTwo)-1;
    printf("First Array: %d\n",isPalindrome(arrOne,0,sizeArrOne));
    printf("Second Array: %d",isPalindrome(arrTwo,0,sizeArrTwo));
}