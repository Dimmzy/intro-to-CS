/********************************
* Student Name: Dmitri Zinkevich
* Student ID: 317301596
* Course Exercise Group: 01
* Exercise Name: Exercise 5
********************************/

#ifndef EX5_H
#define EX5_H

#define MAX_STUDENTS 50
#define MAX_NAME 20
#define MAX_COURSES 5
#define MAX_STRING 200


/*******************************************************************************************************
* Function Name: ModStudent
* Input: char fName(Max size,length: 50,20), char sName(Max size,length: 50,20),
*		char courses(Max size,num,length: 50,5,20),int grades (Max size,num: 50,5,(0<=Value<=100)
* Output: No output, returns void
* Function Operation: The function's purpose is to add or modify (update) a student in our registry.
*						It does so by receving a string from the user that we store in a temporary
*						array. Afterwards we iterate through the string using our helper functions
*						and append the correct elements to their corresponding arrays the main
*						function provides us. While performing checks for the legality of the
*						inputs and making sure we don't exceed our student number limit.
*******************************************************************************************************/

void ModStudent(char fName[MAX_STUDENTS][MAX_NAME], char sName[MAX_STUDENTS][MAX_NAME], char courses[MAX_STUDENTS]
				[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES]);

/*******************************************************************************************************
* Function Name: DelStudent
* Input: char fName(Max size,length: 50,20), char sName(Max size,length: 50,20),
*		char courses(Max size,num,length: 50,5,20),int grades (Max size,num: 50,5,(0<=Value<=100)
* Output: No output, returns void
* Function Operation: The function receives a string as input, performs the functions to extract the
*						first and last name of the student and then compares it to our first and last
*						name main array. if there's a match we'll perform our CleanRegistry function to
*						clear the values in the main array - basically 'deletes' the student.
*******************************************************************************************************/

void DelStudent(char fName[MAX_STUDENTS][MAX_NAME], char sName[MAX_STUDENTS][MAX_NAME], char courses[MAX_STUDENTS]
	[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES]);

/*******************************************************************************************************
* Function Name: Aggregate
* Input: char fName(Max size,length: 50,20), char sName(Max size,length: 50,20),
*		char courses(Max size,num,length: 50,5,20),int grades (Max size,num: 50,5,(0<=Value<=100)
* Output: No output, returns void
* Function Operation: The function prints a menu that lets the user select an aggregation method which
*						will be applied and printed.
*						Inside the function we will also call the sort function so that when we print
*						the requested student, it will print it in a lexographically correct order.
*						Our if statements decides which function will be called to calculate the
*						aggregation as requested by the user.
*						In given type 1 (operation 3) it will print the student with the highest value
*						for the selected aggregation, out of all the students
*						and in given type 2 (operation 4) it will print all the students with their
*						corresponding aggregation value, ordered lexicographically.
*******************************************************************************************************/

void Aggregate(char fName[MAX_STUDENTS][MAX_NAME], char sName[MAX_STUDENTS][MAX_NAME], char courses[MAX_STUDENTS]
[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES], int type);

/*******************************************************************************************************
* Function Name: PrintMenu
* Input: The function doesn't receive any parameters
* Output: No output, returns void
* Function Operation: The function simply prints the menu of the operation types we provide to the user
*******************************************************************************************************/

void PrintMenu();

/*******************************************************************************************************
* Function Name: PrintNxtOp
* Input: The function doesn't receive any parameters
* Output: No output, returns void
* Function Operation: The function simply prints the select next operation message when called
*******************************************************************************************************/

void PrintNxtOp();

#endif