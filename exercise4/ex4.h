
/********************************
* Student Name: Dmitri Zinkevich
* Student ID: 317301596
* Course Exercise Group: 01
* Exercise Name: Exercise 4
********************************/


/*********************************************************************************************************************
* Function Name: Collatz
* Input: long int n (any number)
* Output: No output - void type
* Function Operation: The function performs the Collattz conjecture on the provided number. It prints the sequence
*                     it took and the amount of steps the sequence had to take in order to reach 1
*                     Both on the current call and as a sum of all steps of all the times the function has been called
*********************************************************************************************************************/

void Collatz(long int n);

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

void ProofCollatzUntill(long int n);

/********************************************************************************************************
* Function Name: Fermat
* Input: int n, int stop (any value)
* Output: No output - void type
* Function Operation: The function checks the pythagorean trios that exist between 1 and the input stop,
*                     that follow the rule of a^n + b^n = c^n,
*                      by running nested for loops checking the integers by order of a then b.
********************************************************************************************************/

void Fermat(int n, int stop);

/**************************************************************************************************************
* Function Name: IsDividedBy3Iter
* Input: long int n (any value)
* Output: int (1 or 2)
* Function Operation: The function adds the digits of the received number to a sum variable
*                     if the sum is bigger than 10, it calls a helper function that performs the same operation
*                     until the sum is lower than 10 afterwards it returns 0 case by case (1-10)
*                     if the number isn't divisible 3, and 1 if it is divisible by 3.
**************************************************************************************************************/

int IsDividedBy3Iter(long int n);

/*****************************************************************************************************************
* Function Name: IsDividedBy3Rec
* Input: a long int (consists of the digits 1 2 or 3)
* Output: int (1 or 0)
* Function Operation: If the given number to the function is larger or equal to 10, it calls its' helper functions
*                      that adds the digits until given a single digit number.
*****************************************************************************************************************/

int IsDividedBy3Rec(long int n);

/******************************************************************************************************
* Function Name: FindCommonDigit
* Input: long int n1,n2 (any values)
* Output: int (0 - 9, else -1)
* Function Operation: After receiving the input, the function starts by checking similarities between
*                      n1's rightmost digit and each digit in n2 through our helper function.
*                      if no common digit is found, we divide n1 by ten to the reach the next digit
*                      and then call the function recursively to check again.
******************************************************************************************************/

int FindCommonDigit(long int n1, long int n2);

/******************************************************************************************************
* Function Name: CountDigit
* Input: long int n, int d (n - any value, d - 0 to 9)
* Ouput: int (any value)
* Function Operation: Checks if the given digit is equal to the given number, if it is returns 1. Else,
*                     calls the function CountDigitHelper with the given number and digit as arguments,
*                     and also 0 as the starting counter.
******************************************************************************************************/

int CountDigit(long int n, int d);


/*****************************************************************************************************************
* Function Name: PrintReverse
* Input: long int n (any value)
* Output: No output - void type
* Function Operation: The function prints the call to it's subordinate recursive function that reverses the given
*                     number in the received parameter.
*****************************************************************************************************************/

void PrintReverse(long int n);
