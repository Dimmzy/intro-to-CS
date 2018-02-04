/**
* Student Name: Dmitri Zinkevich
* Student ID: 317301596
* Course Exercise Group: 01
* Exercise Name: ex3_c.c
**/

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <math.h>

int main () {
  for(;;){
    // User Mission Input
    int missionSelect;
    printf("please enter a mission number: \n");
    scanf("%d",&missionSelect);

    // Mission 1
    if (missionSelect == 1){
      // Select the Mission Type
      char missionType;
      int primeTestNumber, i;
      int flag = FALSE;
      printf("please enter the mission type: \n");
      scanf(" %c",&missionType);
      // Initiate Type 'a'
      if (missionType == 'a'){
        printf("please enter a number: \n");
        scanf("%d",&primeTestNumber);

        /*
        * We'll run a loop that performs a primality test. First checking the instances where our given number
        * is either 2,3,smaller or equal to 1, or is even (divisble by 2). if neither of those instances apply
        * we begin the loop which runs from 3 to primeTestNumber - 1, checking if the number is divisible by any
        * number passed. If it is, it isn't a prime number per the definition.
        */

        if (primeTestNumber == 2 || primeTestNumber == 3){
          printf("YES \n");
        }
        else if (primeTestNumber <= 1 || primeTestNumber % 2 == 0){
          printf("NO \n");
        }
        else{
          for (i = 3;i <= (primeTestNumber-1);i++){
            if (primeTestNumber % i == 0){
              printf("NO \n");
              // use the flag as an indicator to print "YES" if flag is false at the end of the loop
              flag = TRUE;
              break;
            }
          }
          if (flag != TRUE){
            printf("YES \n");
          }
        }

      }
      // Initate type 'b'
      else if (missionType == 'b'){
        printf("please enter a number: \n");
        scanf("%d",&primeTestNumber);

        /* Same test as before, except on this mission type we will be testing until the square root of the number
        * we've been given. If the number is divisible by any number from 2 to sqrt(number)+1, the number isnt a prime
        */

        if (primeTestNumber == 2 || primeTestNumber == 3){
          printf("YES \n");
        }
        else if (primeTestNumber <= 1 || primeTestNumber % 2 == 0){
          printf("NO \n");
        }
        else{
          for (i = 3; i <= floor(sqrt(primeTestNumber)) + 1;i++){
            if (primeTestNumber % i == 0){
              printf("NO \n");
              flag = TRUE;
              break;
            }
          }
          if (flag != TRUE){
            printf("YES \n");
          }
        }
      }
      // Initate type 'c'
      else if (missionType == 'c'){
        printf("please enter a number: \n");
        scanf("%d",&primeTestNumber);

        /*
        * To speed up the process, in this type, we'll check the division until the root
        * but only check the odd numbers, since if the number's divisible by 2, then it's already
        * divisible by all the even numbers.
        */

        if (primeTestNumber == 2 || primeTestNumber == 3){
          printf("YES \n");
        }
        else if (primeTestNumber <= 1 || primeTestNumber % 2 == 0){
          printf("NO \n");
        }
        else{
          for (i = 3; i <= floor(sqrt(primeTestNumber)) + 1;i+=2){
            if (primeTestNumber % i == 0){
              printf("NO \n");
              flag = TRUE;
              break;
            }
          }
          if (flag != TRUE){
            printf("YES \n");
          }
        }
      }

    }
    else if (missionSelect == 2){
      int divNum1,divNum2,i;
      // We will use a flag to print the first occurence of divisibility, to properly handle the printing of commas.
      int flag = FALSE;
      // Receive two integer numbers as inputs. We will check which numbers from 1-100 divide them with no remainder.
      printf("please enter two numbers: \n");
      scanf("%d %d",&divNum1,&divNum2);
      // Prints the opening bracket for our "list" of integers
      printf("[");
      for (i = 1; i <= 100; i++){
        // If 'i' is divisible by one of the numbers with no remainder, print 'i'
        if (i % divNum1 == 0 || i % divNum2 == 0){
          // "special" print, prints the first occurence and sets the flag to true
          if (flag == FALSE){
            printf("%d", i);
            flag = TRUE;
          }
          // the prints afterwards will be will have a comma and a space char before the number as requested
          else{
            printf(", %d", i);
          }
        }
      }
      // Prints closing bracket for the list
      printf("] \n");
    }
    // If 0 is entered as a mission, exit the program
    else if (missionSelect == 0){
      break;
    }
    // If any integer but 0,1,2 is entered, ask for input a second time
    else{
      continue;
    }
  }
  return 0;
}

/* Run time for case a: python 1.83031487 c 0.06260896
  Run time for case b: python 0.01615286 c 0.00409508
  Run time for case c: python 0.01574612 c 0.00389910
*/
