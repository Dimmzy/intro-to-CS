
#include <stdio.h>
#include <math.h>
// Definition of the upper limit of unsigned long int (for mission 2)
#define UL_LIMIT 4294967295

// Declarations of helper functions that will assist us in some missions
int RecurHelper (long int num);
int FindCommonDigitHelper (long int n1,long int n2);
int CountDigitHelper(long int n1, int n2,int counter);
int Div3IterHelper(long int n);
int Div3RecursiveHelper(long int n,long int sum, int flag);
int AddIt(int n1,int n2);


/*********************************************************************************************************************
* Function Name: Collatz
* Input: long int n (any number)
* Output: No output - void type
* Function Operation: The function performs the Collattz conjecture on the provided number. It prints the sequence
*                     it took and the amount of steps the sequence had to take in order to reach 1
*                     Both on the current call and as a sum of all steps of all the times the function has been called
*********************************************************************************************************************/

void Collatz (long int n){

  /*
  We need to use a static variable 'totalsteps' so we can have a variable that saves the amount of steps taken
  overall between all calls of the function as requested.
  */
  static long int totalSteps;
  long int currentSteps = 0;
  printf("%ld",n);
  // Runs the loop until we reach our designated number - 1
  while (n != 1){
    // Checks if the iterated number is even.
    switch(n % 2){

      case (0):
      // if it is even, divide it by two, increase the counters and go back to the start of the while loop
        n = n / 2;
        printf ("->%ld",n);
        currentSteps++;
        totalSteps++;
        break;

      default:
      // else (if it's odd), multiply it by 3, add 1. increase the counters and go back to the while loop
        n = n * 3 + 1;
        printf ("->%ld",n);
        currentSteps++;
        totalSteps++;

      }
    }
    printf("\nnum of steps: %ld\n",currentSteps);
    printf("total num of steps: %ld\n",totalSteps);
}

/*************************************************************************************************************
* Function Name: CollatzNoPrint
* Input: long int n (any value)
* Output: unsigned long int (0 < UL_LIMIT)
* Function Operation: The function checks whether the received number is larger than the upper limit
*                     of unsigned long int, if it is it'll return 0,
*                     otherwise it'll perform the Collatz conjecture without printing anything,
*                     but it saves the amount of steps it took to perform the sequence, and then returns it.
*************************************************************************************************************/

unsigned long int CollatzNoPrint(long int n){
  unsigned long int currentSteps = 0;
  // Same idea as the previous task, while loop that performs the conjecture through the numbers until we reach 1.
  while (n != 1){
    switch(n % 2){

      case (0):
        n = n /2;
        currentSteps++;
        break;

      default:
        n = n * 3 +1;
        currentSteps++;
    }
  }
  // check if the amount of steps is lower than our limit, if it is, return the value. else, return 0.
  if (currentSteps < UL_LIMIT){
    return currentSteps;
  }
  else{
    return 0;
  }
}


/**********************************************************************************************************
* Function Name: ProofCollatzUntill
* Input: long int n (any value)
* Ouput: No output - void type
* Function Operation: The function checks the numbers from 1 to the input number
*                     and prints if they pass the threshold set by the CollatzNoPrint function.
*                     (if the numbers of steps needed is larger than the limit of unsigned long int)
*                     if it isn't larger we'll print the test is passed and the number of steps, otherwise
*                     we print the problematic number that doesn't follow Collatzs' conjecture.
**********************************************************************************************************/

void ProofCollatzUntill(long int n){
  long int i;
  unsigned long int currentSteps;
  // for loop that calls the function CollatzNoPrint each number until the given n
  for(i = 1; i < n; i++){
    currentSteps = CollatzNoPrint(i);
    if (currentSteps != 0 || i == 1){
      printf("passed: %ld (num of steps: %lu)\n",i,currentSteps);
    }
    else{
      printf("you might wanna check %ld and win 500$ :)\n",i);
    }
  }
}

/********************************************************************************************************
* Function Name: Fermat
* Input: int n, int stop (any value)
* Output: No output - void type
* Function Operation: The function checks the pythagorean trios that exist between 1 and the input stop,
*                     that follow the rule of a^n + b^n = c^n,
*                      by running nested for loops checking the integers by order of a then b.
********************************************************************************************************/

void Fermat(int n, int stop){
  // Declare our loop indicies and a flag we'll use to print no trio found if it's false
  int i,j,k;
  int coefficientA,coefficientB,coefficientC;
  int trioFound = 0;
  for(i=1;i<stop;i++){
    coefficientA = i;
    for (j=i;j<stop;j++){
      coefficientB = j;
      for (k=j;k<stop;k++){
        coefficientC = k;
        // Checks if the pytagorean theorm applies to the selected three numbers,prints and repeats the loop until n.
        if(pow(coefficientA,n)+pow(coefficientB,n) == pow(coefficientC,n)){
          trioFound = 1;
          printf("Eureka! %d^%d + %d^%d = %d^%d\n", coefficientA,n,coefficientB,n,coefficientC,n);
        }
      }
    }
  } //end of nested for loops
  if (trioFound == 0){
    printf("meh :(\n");
  }
}

/*****************************************************************************************************************
* Function Name: IsDividedBy3Rec
* Input: a long int (consists of the digits 1 2 or 3)
* Output: int (1 or 0)
* Function Operation: If the given number to the function is larger or equal to 10, it calls its' helper functions
*                      that adds the digits until given a single digit number.
*****************************************************************************************************************/

int IsDividedBy3Rec(long int n){
  int finalNum;
  if (n >= 10){
    n = Div3RecursiveHelper(n,0,0);
  switch(n){
    case 1:
    return 0;

    case 2:
    return 0;

    case 0:
    return 1;

    default:
    return 0;
    }
  }
  else{
    if (n == 3){
      return 1;
    }
    else{
      return 0;
    }
  }
}


/**************************************************************************************************************
* Function Name: IsDividedBy3Iter
* Input: long int n (any value)
* Output: int (1 or 2)
* Function Operation: The function adds the digits of the received number to a sum variable
*                     if the sum is bigger than 10, it calls a helper function that performs the same operation
*                     until the sum is lower than 10 afterwards it returns 0 case by case (1-10)
*                     if the number isn't divisible 3, and 1 if it is divisible by 3.
**************************************************************************************************************/

int IsDividedBy3Iter(long int n){
  long int sum = 0;
  // while loop that turns sums the digits of our received number n
  while (n > 0){
    sum += n % 10;
    n /= 10;
  }
  while (sum >= 10){
    sum = Div3IterHelper(sum);
  }
  // If the remainder after the operations is one of the elements in the group {1,2,4,5,7,8} returns 0, otherwise returns 1.
  switch (sum){
    case 1:
    return 0;

    case 2:
    return 0;

    case 4:
    return 0;

    case 5:
    return 0;

    case 7:
    return 0;

    case 8:
    return 0;

    default:
    return 1;
  }
}

/******************************************************************************************************
* Function Name: FindCommonDigit
* Input: long int n1,n2 (any values)
* Output: int (0 - 9, else -1)
* Function Operation: After receiving the input, the function starts by checking similarities between
*                      n1's rightmost digit and each digit in n2 through our helper function.
*                      if no common digit is found, we divide n1 by ten to the reach the next digit
*                      and then call the function recursively to check again.
******************************************************************************************************/

int FindCommonDigit(long int n1, long int n2){
  // Checks n1 rightmost digit and each digit in n2
  if (FindCommonDigitHelper(n1,n2) != 0){
    return (n1 % 10);
  }
  // Brings us to the next digit in n1 (if it exists), and calls the function recursively
  else if (n1 > 0){
    n1 /= 10;
    FindCommonDigit(n1,n2);
  }
  else{
    return -1;
  }
}

/******************************************************************************************************
* Function Name: CountDigit
* Input: long int n, int d (n - any value, d - 0 to 9)
* Ouput: int (any value)
* Function Operation: Checks if the given digit is equal to the given number, if it is returns 1. Else,
*                     calls the function CountDigitHelper with the given number and digit as arguments,
*                     and also 0 as the starting counter.
******************************************************************************************************/

int CountDigit(long int n, int d){
  if (n == d){
    return 1;
  }
  else{
  return CountDigitHelper(n,d,0);
  }
}

/*****************************************************************************************************************
* Function Name: PrintReverse
* Input: long int n (any value)
* Output: No output - void type
* Function Operation: The function prints the call to it's subordinate recursive function that reverses the given
*                     number in the received parameter.
*****************************************************************************************************************/

void PrintReverse(long int n){
  if (n < 1){
    printf("\n");
    return;
  }
  printf("%ld",(n % 10));
  PrintReverse(n / 10);
}

/************************************************************************************************************
* Function Name: AddIt
* Input: int n1, int n2 (n1 = 0 to 9, n2 = 0 to 9)
* Output: int (0-2)
* Function Operation: The function compares the values of n1 and n2 and returns their sum over the Z3 field.
************************************************************************************************************/

int AddIt(int n1,int n2){
  if (n1 == 0 && n2 == 1){
    return 1;
  }
  if (n1 == 0 && n2 == 2){
    return 2;
  }
  if (n1 == 0 && n2 == 3){
    return 0;
  }
  if (n1 == 1 && n2 == 0){
    return 1;
  }
  if (n1 == 2 && n2 == 0){
    return 2;
  }
  if (n1 == 3 && n2 == 0){
    return 0;
  }
  if (n1 == 1 && n2 == 1){
    return 2;
  }
  if (n1 == 1 && n2 == 2){
    return 0;
  }
  if (n1 == 1 && n2 == 3){
    return 1;
  }
  if (n1 == 2 && n2 == 1){
    return 0;
  }
  if (n1 == 2 && n2 == 2){
    return 1;
  }
  if (n1 == 2 && n2 == 3){
    return 2;
  }
  if (n1 == 3 && n2 == 1){
    return 1;
  }
  if (n1 == 3 && n2 == 2){
    return 2;
  }
  if (n1 == 3 && n2 == 3){
    return 0;
  }
}


/**************************************************************************************************************
* Function Name: Div3RecursiveHelper
* Input: long int n, long int sum, int flag. (n = any value, sum = any value, flag = 1 or 0)
* Output: int n (value between 0 and 9)
* Function Operation: At the first recursion of the function it adds the two last digits of the number
*                     (using the AddIt Function)
*                     then divides the number n by 100 and sets the flag to 1 (so it wont divide by 100 again).
*                     The next recursive calls adds the sum to the last digit, and saves it as a new sum,
*                     dividing n by 10 each call, until n is smaller than 10.
*                     Then it adds the sum to n one final time.
**************************************************************************************************************/

int Div3RecursiveHelper(long int n,long int sum, int flag){
  if (flag == 0){
    sum = AddIt((n/10) % 10, n % 10);
    n = ((n / 10) / 10);
    Div3RecursiveHelper(n,sum,1);
  }
  if (n > 10){
    sum = AddIt(n % 10, sum);
    n /= 10;
    Div3RecursiveHelper(n,sum,1);
  }
  else{
    n = AddIt(n,sum);
    return n;
  }
}

/*************************************************************************************************************
* Function Name: Div3IterHelper
* Input: long int n (any value)
* Output: int newSum (value between 0 and 9)
* Function Operation: The function performs a loop that adds to a newSum variable the value of the last digit
*                     and divides the original received sum by 10, until sum is equal to 0,
*                     and then returns to the calling function the new sum of the numbers.
*************************************************************************************************************/

int Div3IterHelper(long int sum){
  long int newSum = 0;
  while(sum > 0){
    newSum += sum % 10;
    sum /= 10;
  }
  return newSum;
}

/******************************************************************************************************************
* Function Name: FindCommonDigitHelper
* Input: long int n1,n2 (any value)
* Ouput: int (value between 0 and 9)
* Function Operation: The function starts by checking if the rightmost digit in n1 and n2 are equal.
*                     if they aren't, and n2 isn't a single digit number, it divides it by 10 and calls itself.
*                     if the function iterates through all of the digits in n2, returns 0 to the calling function.
******************************************************************************************************************/

int FindCommonDigitHelper(long int n1, long int n2){
    if ((n1 % 10) == (n2 % 10)){
    return n1 % 10;
    }
    else if (n2 > 0){
    n2 /= 10;
    FindCommonDigitHelper(n1,n2);
    }
    else{
    return 0;
  }
}

/**********************************************************************************************************
* Function Name: CountDigitHelper
* Input: long int n1,int n2,counter (n1 = any value, n2 = between 0 and 9, counter = any value)
* Output: int (amy value)
* Function Operation: While the given number n1 is larger than one, the function checks if it's first digit
*                     is equal to n2, if it is, add one to the counter.
*                     When n1 is smaller than 1 (iterated through all digits),
*                     returns the value of counter to it's calling function.
**********************************************************************************************************/

int CountDigitHelper(long int n1, int n2,int counter){
  if(n1 > 1){
    if(n2 == (n1 % 10)){
      counter++;
    }
    n1 /= 10;
    CountDigitHelper(n1,n2,counter);
  }
  else{
    return counter;
  }
}
