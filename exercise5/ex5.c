/********************************
* Student Name: Dmitri Zinkevich
* Student ID: 317301596
* Course Exercise Group: 01
* Exercise Name: Exercise 5
********************************/

#include <stdio.h>
#include <string.h>
#include "ex5.h"


int CheckNameLength(char *charArr, int nameType);
int CheckNameChar(char *charArr, int nameType);
int ExtractGrade(char *inputArr, int outputArr[][MAX_COURSES], int courseCounter, int studentCounter);
int UpdateGrade(char *inputArr, int *outputArr);
int CalculateAvg(int grades[][MAX_COURSES], int studentNumber);
int CalculateMax(int grades[][MAX_COURSES], int studentNumber);
int CalculateMin(int grades[][MAX_COURSES], int studentNumber);
int CalculateSum(int grades[][MAX_COURSES], int studentNumber);
int CountCourses(int grades[][MAX_COURSES], int studentNumber);
int CountStudents(char fName[][MAX_NAME]);
void DelTrailingSpace(char *charArr);
void UpdateCourse(char *inputArr, char *outputArr);
void Aggregate(char fName[MAX_STUDENTS][MAX_NAME], char sName[MAX_STUDENTS][MAX_NAME], char courses[MAX_STUDENTS]
	[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES], int type);
void PrintError();
void SubSpace(char *inputArr, int nameLen);
void ClearRegistry(char fName[][MAX_NAME], char sName[][MAX_NAME], char courses[][MAX_COURSES][MAX_NAME],
	int grades[][MAX_COURSES], int studentCounter);
void ExtractName(char *inputArr, char outputArr[], int extractType);
void ExtractCourse(char *inputArr, char outputArr[][MAX_COURSES][MAX_NAME], int courseCount, int studentCounter);
void SortStudents(char fName[][MAX_NAME], char sName[MAX_STUDENTS][MAX_NAME], char courses[MAX_STUDENTS]
	[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES]);
void SwapStr(char *firstStudent, char *secondStudent);
void SwapInt(int *firstStudent, int *secondStudent);

// Main Functions

/*******************************************************************************************************
* Function Name: PrintMenu
* Input: The function doesn't receive any parameters
* Output: No output, returns void
* Function Operation: The function simply prints the menu of the operation types we provide to the user
*******************************************************************************************************/

void PrintMenu() {
	printf("Please select the operation:\n");
	printf("	0. Exit.\n");
	printf("	1. Insert or update student grades.\n");
	printf("	2. Delete student information.\n");
	printf("	3. Print the student with maximal computed grade.\n");
	printf("	4. Print all the students with their computed grades.\n");
	printf("	5. Print the menu.\n");
}

/*******************************************************************************************************
* Function Name: PrintNxtOp
* Input: The function doesn't receive any parameters
* Output: No output, returns void
* Function Operation: The function simply prints the select next operation message when called
*******************************************************************************************************/

void PrintNxtOp() {
	printf("Select the next operation (insert 5 for complete menu).\n");
}

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
	[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES]) {

	/*
	We'll create several arrays we'll append our names from the input string to so we can handle the strings
	more easily. Their size will be MAX_NAME + 1 to avoid copying garbage to our 'main' arrays when
	copying a name that is 20 (MAX_NAME) characters long. Also creates a courseCounter so we can know to which
	index of the courses array we should add/modify a course.
	*/

	char tempArray[MAX_STRING] = { 0 };
	char tempFName[MAX_NAME + 1] = { 0 };
	char tempSName[MAX_NAME + 1] = { 0 };
	int courseCounter = 0;

	// Creates a dummy that will eat up the backspace that we get after selecting an operation in main
	char dummy;
	scanf("%c", &dummy);

	// Receives the string from the user and saves it in our temporary array
	fgets(tempArray, MAX_STRING, stdin);

	// Perform a basic check to see if the first name has spaces trailing it, if so, remove them with our function
	if (tempArray[0] == ' ') {
		DelTrailingSpace(tempArray);
	}

	/* 
	In the following lines we perform legality checks and then extract the first name and last name from the temp
	array that contains the whole input as a string and move it to the tempFName and tempSName arrays
	*/

	if ((CheckNameLength(tempArray, 1)) == 0 || ((CheckNameChar(tempArray, 1)) == 0)) {
		PrintError();
		return;
	}

	ExtractName(tempArray, tempFName, 1);

	if (((CheckNameLength(tempArray, 2)) == 0) || ((CheckNameChar(tempArray, 2)) == 0)) {
		PrintError();
		return;
	}

	ExtractName(tempArray, tempSName, 2);

	/* 
	Using our tempF and tempS name strings, we'll compare them to our main first and last name arrays to see if
	a student with the same name exists and if it does we'll perform the update student portion of this function
	*/

	for (int i = 0; i <= MAX_STUDENTS; i++) {
		if ((strcmp(tempFName, fName[i]) == 0 && (strcmp(tempSName, sName[i]) == 0))) {
			// if the 'if' statement returns true, we begin updating the student in the i index
			int updateNumber = i, updatedAtleastOnce = 0;
			// We'll perform a simple loop that checks the amount of empty course spots (if we'll need to add courses)
			int emptyCourseIndex = -1;
			for (int s = 0; s < MAX_COURSES; s++) {
				if (grades[updateNumber][s] == -1) {
					emptyCourseIndex = s;
					break;
				}
			}

			/*
			We'll create two backup arrays of the courses and grades that we can fall back to incase we'll get an 
			invalid input in the course or grade entries. Basically lets us return to the previous values of 
			the stuents' arrays.
			*/

			char bkpCourses[MAX_COURSES][MAX_NAME] = { 0, };
			int bkpGrades[MAX_COURSES] = { -1,-1,-1,-1,-1 };
			for (int i = 0; i < MAX_COURSES; i++) {
				strcpy(bkpCourses[i], courses[updateNumber][i]);
				bkpGrades[i] = grades[updateNumber][i];
			}

			// We start iterating through the input string using a while loop that checks the length of the string
			while (strlen(tempArray) > 1) {
				
				/*
				In the following code we will create a temporary array that stores the name of the course extracted
				from our input string. We perform the legality check on each course name, if it fails we completely
				restore the registry at that index from our backup arrays and then return to the main function.
				*/

				char tempCName[MAX_NAME] = { 0 };
				int updatedGrade = 0;
				if ((CheckNameLength(tempArray, 3) == 0) || (CheckNameChar(tempArray, 3) == 0)) {
					for (int i = 0; i < MAX_COURSES; i++) {
						strcpy(courses[updateNumber][i], bkpCourses[i]);
						grades[updateNumber][i] = bkpGrades[i];
					}
					PrintError();
					return;
				}
				UpdateCourse(tempArray, tempCName);
				// We'll perform a check that compares the course name with the main course array to see if it exists
				for (int k = 0; k <= MAX_COURSES; k++) {
					if ((strcmp(tempCName, courses[updateNumber][k]) == 0)) {
						// If the course exists, we'll use the UpdateGrade function to update the grade
						int tempGrade[1] = { 0 };
						// If the function returns 0, the grade is invalid so we restore and return
						if (UpdateGrade(tempArray, tempGrade) == 0) {
							for (int i = 0; i < MAX_COURSES; i++) {
								strcpy(courses[updateNumber][i], bkpCourses[i]);
								grades[updateNumber][i] = bkpGrades[i];
							}
							PrintError();
							return;
						}
						// Else, we update the grade and set a flag that we updated a students' info
						else {
							grades[updateNumber][k] = tempGrade[0];
							updatedGrade = 1;
							updatedAtleastOnce = 1;
							break;
						}
					}
				}
				// If the course doesn't exist in the students' registry, we'll try adding it to the student
				if (updatedGrade == 0) {
					// If it is valid, we check if we have enough space (through emptycourseindex) to add it 
					if (emptyCourseIndex != -1 && emptyCourseIndex <= 4) {
						// Once again, we make sure the grade is valid, if it isn't restore and return
						if (ExtractGrade(tempArray, grades, updateNumber, emptyCourseIndex) == 0) {
							for (int i = 0; i < MAX_COURSES; i++) {
								strcpy(courses[updateNumber][i], bkpCourses[i]);
								grades[updateNumber][i] = bkpGrades[i];
							}
							PrintError();
							return;
						}
						// If all checks are OK then we add the course, add one to the index and flag the updated
						strcat(courses[updateNumber][emptyCourseIndex], tempCName);
						emptyCourseIndex++;
						updatedAtleastOnce = 1;
					}
					else {
						// If we have no more space for the course
						if (updatedAtleastOnce == 1) {
							// We print the student has been updated if the flag has been set previously
							printf("Student \"%s %s\" updated.\n", fName[updateNumber], sName[updateNumber]);
							return;
						}
					}
				}
			}
			// End of While loop (Ended iterating through the string)
			if (updatedAtleastOnce == 1) {
				// We print the student has been updated if the flag has been set previously
				printf("Student \"%s %s\" updated.\n", fName[updateNumber], sName[updateNumber]);
				return;
			}
			// otherwise we print the error as requested
			else {
				PrintError();
				return;
			}
		}
	}
	// End of for loop (Check if need to update a student loop)

	/*
	If we didn't update any student, we'll create a new student entry and append each part of the string to it's 
	corresponding main array in the index.
	*/

	for (int studentIndex = 0; studentIndex < MAX_STUDENTS; studentIndex++) {

		/* 
		To make sure we add the student into an empty index, including an index which previously held a student
		that has been since deleted, we'll iterate through all of our 50 student indices, and add the student
		to the first empty index by checking the first letter of the first name. If its' null, that index is empty
		*/

		if (fName[studentIndex][0] == '\0') {
			strcpy(fName[studentIndex], tempFName);
			strcpy(sName[studentIndex], tempSName);

			// Loops through all the given courses 

			for (int i = 0; i < MAX_COURSES; i++) {

				// We'll perform the same name legality tests to make sure we have valid input, else we clear & return

				if (strlen(tempArray) > 1) {
					if (((CheckNameLength(tempArray, 3)) == 0) || ((CheckNameChar(tempArray, 3)) == 0)) {
						ClearRegistry(fName, sName, courses, grades, studentIndex);
						PrintError();
						return;
					}
					
					// if the name is legal, we'll extract and copy the course and the grade into our entry

					else {
						ExtractCourse(tempArray, courses, studentIndex, courseCounter);
						if (ExtractGrade(tempArray, grades, studentIndex, courseCounter) == 0) {
							ClearRegistry(fName, sName, courses, grades, studentIndex);
							PrintError();
							return;
						}
						courseCounter++;
					}
				}
			}

			// If no courses entered, we'll print an error

			if (courseCounter == 0) {
				ClearRegistry(fName, sName, courses, grades, studentIndex);
				PrintError();
				return;
			}

			// Finally, we print that the student is added if we didn't return eariler due to invalid input

			printf("Student \"%s %s\" added.\n", fName[studentIndex], sName[studentIndex]);
			return;
		}
		// End of the adding student portion of the function
	}
	// If we looped through all the indices, and didnt find an empty spot to add the student, we print an error
	printf("Error: there is no more space.\n");
	return;
}

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
	[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES]) {
	/*
	We'll initialize three arrays: tempArray which will hold the entire string that we receive as input
	delFName and delSName which will hold the first and last names respectively extraceted from the main input string
	we will compare them to the main arrays to see if they exist in the main array.
	*/
	char tempArray[MAX_STRING] = { 0 };
	char delFName[MAX_NAME] = { 0 };
	char delSName[MAX_NAME] = { 0 };
	// Creates a dummy that eats up the recieved backspace.
	char dummy;
	scanf("%c", &dummy);
	fgets(tempArray, MAX_STRING, stdin);
	// Removes trailing spaces
	if (tempArray[0] == ' ') {
		DelTrailingSpace(tempArray);
	}
	// Check legality of the first and last naem and then exracts them
	if ((CheckNameLength(tempArray, 1) == 0) || ((CheckNameChar(tempArray, 1) == 0))) {
		printf("Error: invalid name\n");
		return;
	}
	ExtractName(tempArray, delFName, 1);
	if ((CheckNameLength(tempArray, 4) == 0) || ((CheckNameChar(tempArray, 4) == 0))) {
		printf("Error: invalid name\n");
		return;
	}
	ExtractName(tempArray, delSName, 3);
	// Check our first and last names against the student list if they exist, clear the complete registry at the index
	for (int i = 0; i < MAX_STUDENTS; i++) {
		if ((strcmp(delFName,fName[i]) == 0) && (strcmp(delSName,sName[i]) == 0)) {
			ClearRegistry(fName, sName, courses, grades, i);
			printf("Student \"%s %s\" deleted.\n", delFName, delSName);
			return;
		}
	}
	// If the for loop ended naturally (didn't find a match) the student doesn't exist in our memory
	printf("Error: student name does not exist.\n");
	return;
}

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
	[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES], int type) {
	// Two variables: aggSelection which holds the users selected aggregation method,and a dummy which eats backspace
	char aggSelection, dummy;
	int numOfStudents = CountStudents(fName);
	if (numOfStudents == 0) {
		printf("Error: there are no students.\n");
		return;
	}
	printf("Please select the aggregation method:\n");
	printf("	a. Average grade.\n");
	printf("	b. Maximal grade.\n");
	printf("	c. Minimal grade.\n");
	printf("	d. Sum.\n");
	printf("	e. Count.\n");
	printf("	0. Return the main menu.\n");
	scanf("%c%c", &dummy, &aggSelection);
	// We'll call the SortStudents function to sort our students lexicographically for corrent printing order
	SortStudents(fName, sName, courses, grades);

	/*
	We'll use several if statements with the aggSelection and type conditions which will call the proper function
	that user requested. We use if statements instead of a Switch because the Switch would require another 
	nested Switch statement which would make the code less readable. Even though we have to use a large amount of
	else if's, it still seems more readable in my opinion than nested Switch statements.
	for each if stataement:
	If type = 1: We will run a loop that checks and compares that values of the corresponding function for each student
	and it prints the user with the largest value. If we have a situation where two (or more) students are tied
	at the score, it'll print the first one according to the sum of the ascii first name (and if they have the same
	name then by the last name)
	If type = 2: We will simply run a loop that prints the name and last name of the student and the value of the 
	aggregation
	*/

	if (aggSelection == 'a' && type == 1) {
		int topStudent = 0;
		int tieStudent = 0;
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				if (CalculateAvg(grades, i) > (CalculateAvg(grades, i + 1)) &&
					CalculateAvg(grades, i) > CalculateAvg(grades, topStudent)) {
					topStudent = i;
				}
				else if (CalculateAvg(grades, i) == (CalculateAvg(grades, i + 1)) &&
					CalculateAvg(grades, i) == CalculateAvg(grades, topStudent)) {
					tieStudent = i;
				}
			}
		}
		printf("%s %s, %d\n", fName[topStudent], sName[topStudent], CalculateAvg(grades, topStudent));
		return;
	}
	else if (aggSelection == 'a' && type == 2) {
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				printf("%s %s, %d\n", fName[i], sName[i], CalculateAvg(grades, i));
			}
		}
		return;
	}
	else if (aggSelection == 'b' && type == 1) {
		int topStudent = 0;
		int tieStudent = 0;
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				if ((CalculateMax(grades, i) > CalculateMax(grades, i + 1)) &&
					(CalculateMax(grades, i) > CalculateMax(grades, topStudent))) {
					topStudent = i;
				}
				else if ((CalculateMax(grades, i) == CalculateMax(grades, i + 1)) &&
					(CalculateMax(grades, i) == CalculateMax(grades, topStudent))) {
					tieStudent = i;
				}
			}
		}
		printf("%s %s, %d\n", fName[topStudent], sName[topStudent], CalculateMax(grades, topStudent));
		return;
	}
	else if (aggSelection == 'b' && type == 2) {
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				printf("%s %s, %d\n", fName[i], sName[i], CalculateMax(grades, i));
			}
		}
		return;
	}
	else if (aggSelection == 'c' && type == 1) {
		int topStudent = 0;
		int tieStudent = 0;
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				if ((CalculateMin(grades, i) > CalculateMin(grades, i + 1)) &&
					(CalculateMin(grades, i) > CalculateMin(grades, topStudent))) {
					topStudent = i;
				}
				else if ((CalculateMin(grades, i) == CalculateMin(grades, i + 1)) &&
					(CalculateMin(grades, i) == CalculateMin(grades, topStudent))) {
					tieStudent = i;
				}
			}
		}
		printf("%s %s, %d\n", fName[topStudent], sName[topStudent], CalculateMin(grades, topStudent));
		return;
	}
	else if (aggSelection == 'c' && type == 2) {
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				printf("%s %s, %d\n", fName[i], sName[i], CalculateMin(grades, i));
			}
		}
		return;
	}
	else if (aggSelection == 'd' && type == 1) {
		int topStudent = 0;
		int tieStudent = 0;
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				if (CalculateSum(grades, i) > CalculateSum(grades, i + 1) &&
					CalculateSum(grades, i) > CalculateSum(grades, topStudent)) {
					topStudent = i;
				}
				else if ((CalculateSum(grades, i) == CalculateSum(grades, i + 1)) &&
					(CalculateSum(grades, i) == CalculateSum(grades, topStudent))) {
					tieStudent = i;
				}
			}
		}
		printf("%s %s, %d\n", fName[topStudent], sName[topStudent], CalculateSum(grades, topStudent));
		return;
	}
	else if (aggSelection == 'd' && type == 2) {
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				printf("%s %s, %d\n", fName[i], sName[i], CalculateSum(grades, i));
			}
		}
		return;
	}
	else if (aggSelection == 'e' && type == 1) {
		int topStudent = 0;
		int tieStudent = 0;
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				if ((CountCourses(grades, i) > CountCourses(grades, i + 1)) &&
					(CountCourses(grades, i) > CountCourses(grades, topStudent))) {
					topStudent = i;
				}
				else if ((CountCourses(grades, i) == CountCourses(grades, i + 1)) &&
					(CountCourses(grades, i) == CountCourses(grades, topStudent))) {
					tieStudent = i;
				}
			}
		}
		printf("%s %s, %d\n", fName[topStudent], sName[topStudent], CountCourses(grades, topStudent));
		return;
	}
	else if (aggSelection == 'e' && type == 2) {
		for (int i = 0; i < MAX_STUDENTS; i++) {
			if (fName[i][0] != '\0') {
				printf("%s %s, %d\n", fName[i], sName[i], CountCourses(grades, i));
			}
		}
		return;
	}
	else if (aggSelection == '0') {
		return;
	}
}

// Helper Functions

/********************************************************************************************************************
* Function Name: DelTrailingSpace
* Input: char array (Max length,200)
* Output: No output, returns void
* Function Operation: The function  receives an array, and removes any spaces by replacing the value in each index
						to the next index, until we receive a string without any backspaces before the first letter
********************************************************************************************************************/

void DelTrailingSpace(char *charArr) {
	int index = 0, i;
	while (charArr[index] == ' ') {
		index++;
	}
	if (index != 0) {
		i = 0;
		while (charArr[i + index] != '\0')
		{
			charArr[i] = charArr[i + index];
			i++;
		}
		charArr[i] = '\0';
	}
}

/********************************************************************************************************************
* Function Name: CheckNameLength
* Input: char array (Max length,200), int type (value between 1 to 4)
* Output: int (1 or 0) that denotes whether the length is valid or isn't. 1 = valid, 0 = invalid
* Function Operation: The function checks if the name's length is valid (up to and including 20 characters)
*						We check the name according to the nameType var that we receive, each one for a different
*						type of name. we simply check if in the name string, up to 20 chars, we see a 'break'
*						character, which marks the end of the name. if none exist in the first 20 chars'
t						the name is invalid.
********************************************************************************************************************/

int CheckNameLength(char *charArr, int nameType) {
	for (int i = 0; i < MAX_NAME + 1; i++) {
		if ((charArr[i] == ' ') && (nameType == 1)) {
			return 1;
		}
		else if ((charArr[i] == ':') && (nameType == 2)) {
			return 1;
		}
		else if ((charArr[i] == ',') && (nameType == 3)) {
			return 1;
		}
		else if ((charArr[i] == '\n') && (nameType == 4)) {
			return 1;
		}
	}
	return 0;
}

/********************************************************************************************************************
* Function Name: CheckNameChar
* Input: char array (Max length,200), int type (value between 1 to 4)
* Output: int (1 or 0) that denotes whether the length is valid or isn't. 1 - valid, 0 = invalid
* Function Operation: The function checks if the name's length is valid (up to and including 20 characters)
*						We check the name according to the nameType var that we receive, each one for a different
*						type of name. The check we perform is simply comparing any non letter characters to our valid
*						chars by the given nameType (for example, ',' is correct in the grade name, since it 
*						marks the end of the course name.
********************************************************************************************************************/

int CheckNameChar(char *charArr, int nameType) {
	for (int i = 0; i <= MAX_NAME; i++) {
		if (!((charArr[i] >= 'a' && charArr[i] <= 'z') || (charArr[i] >= 'A' && charArr[i] <= 'Z')))
		{
			if (charArr[i] == ' ' && nameType == 1) {
				return 1;
			}
			else if ((charArr[i] == ':' || charArr[i] == ' ') && nameType == 2) {
				return 1;
			}
			else if ((charArr[i] == ' ' || charArr[i] == ',') && nameType == 3) {
				return 1;
			}
			else if ((charArr[i] == '\n' || charArr[i] == ' ') && nameType == 4) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	return 1;
}

/********************************************************************************************************************
* Function Name: ExtractName
* Input: char inputArr (Max length 200), char outputArr (Max length 20), int extractType 
* Output: No output, returns void
* Function Operation: The function extracts the name of the student from our given string (inputArr) and appends it
*						to our given string outputArr, according to the extractType (1-first name,2&3 - last name)
*						If we're trying to extract the first name, the function simply copies all the chars up until
*						the ' ' character (note we always remove trailing spaces before calling this function)
*						If we try to extract the last name, we check until ':' or '\n', according to the needed
*						circumstances.
*						After extract the name we wanted, we call the DelTrailingSpace function to ease our following
*						work on the temp string we iterate through.
********************************************************************************************************************/

void ExtractName(char *inputArr, char outputArr[], int extractType) {
	if (extractType == 1) {
		int nameLen = 0;
		for (int i = 0; i < MAX_NAME; i++) {
			if (inputArr[i] != ' ') {
				nameLen++;
			}
			else {
				break;
			}
		}
		strncpy(outputArr, inputArr, nameLen);
		SubSpace(inputArr, nameLen);
		DelTrailingSpace(inputArr);
		return;
	}
	else if (extractType == 2) {
		int nameLen = 0;
		for (int i = 0; i < MAX_NAME; i++) {
			if (inputArr[i] != ':') {
				nameLen++;
			}
			else {
				break;
			}
		}
		strncpy(outputArr, inputArr, nameLen);
		SubSpace(inputArr, nameLen);
		DelTrailingSpace(inputArr);
		return;
	}
	else if (extractType == 3) {
		int nameLen = 0;
		for (int i = 0; i < MAX_NAME; i++) {
			if (inputArr[i] != '\n') {
				nameLen++;
			}
			else {
				break;
			}
		}
		strncpy(outputArr, inputArr, nameLen);
		SubSpace(inputArr, nameLen);
		DelTrailingSpace(inputArr);
		return;
	}
}

/********************************************************************************************************************
* Function Name: ExtractCourse
* Input: char inputArr (Max length 200), char outputArr (Max length 20), int studentCounter (Max 50), 
*		int courseCounter (Max 5)
* Output: No output, returns void
* Function Operation: The function extracts the name of the course from our given input string inputArr. It checks
*						the string up until the ',' string, and then copies those characters to our main courses
*						array for given student index (by studentcounter) and given course index (courseCounter)
********************************************************************************************************************/

void ExtractCourse(char *inputArr, char outputArr[][MAX_COURSES][MAX_NAME], int studentCounter, int courseCounter) {
	int nameLen = 0;
	for (int i = 0; i < MAX_NAME; i++) {
		if (inputArr[i] != ',') {
			nameLen++;
		}
		else {
			break;
		}
	}
	strncpy(outputArr[studentCounter][courseCounter], inputArr, nameLen);
	for (int i = nameLen + 1; i <= MAX_NAME; i++) {
		outputArr[studentCounter][courseCounter][i] = '\0';
	}
	SubSpace(inputArr, nameLen);
	DelTrailingSpace(inputArr);
	return;
}

/********************************************************************************************************************
* Function Name: UpdateCourse
* Input: char inputArr (Max length 20), char outputArr (Max length 20)
* Output: No output, returns void
* Function Operation: The function updates the course name in outputArr from given string inputArr.
*						We perform a loop that checks the length of the string until the last character of the course
*						(up to ',' which denotes the end of the course name). afterwards, we copy the strings up to
*						our calculated nameLen value to our output array.
********************************************************************************************************************/

void UpdateCourse(char *inputArr, char *outputArr) {
	int nameLen = 0;
	for (int i = 0; i < MAX_NAME; i++) {
		if (inputArr[i] != ',') {
			nameLen++;
		}
		else {
			break;
		}
	}
	strncpy(outputArr, inputArr, nameLen);
	SubSpace(inputArr, nameLen);
	DelTrailingSpace(inputArr);
	return;
}

/********************************************************************************************************************
* Function Name: ExtractGrade
* Input: char inputArr (Max length 200), int outputArr (Between 0 to 100), int studentCounter (Max 50),
*		int courseCounter (Max 5)
* Output: int (0 or 1) that tells the calling function if the grade input is valid or not, 0 = invalid and 1 = valid
* Function Operation: The function checks the length (in chars) of the grade, by checking the amount of chars until
*						the ';' character which notes the end of the grade.
*						then, according to the length it calculates the grade as an integer by using multiplication
*						if after converting the char grade to int it's either smaller than 0 or larger than 100
*						the function returns 0, telling the calling function the grade is invalid.
********************************************************************************************************************/

int ExtractGrade(char *inputArr, int outputArr[][MAX_COURSES], int studentCounter, int courseCounter) {
	int gradeLen = 0, grade = 0, gradeNum = 0;
	for (int i = 0; i < MAX_STRING; i++) {
		if (inputArr[i] != ';') {
			gradeLen++;
		}
		else {
			break;
		}
	}
	if (gradeLen > 3) {
		return 0;
	}
	else {
		switch (gradeLen) {
		case(3):
			grade += ((inputArr[0] - '0') * 100);
			grade += ((inputArr[1] - '0') * 10);
			grade += (inputArr[2] - '0');
			break;
		case(2):
			grade += ((inputArr[0] - '0') * 10);
			grade += (inputArr[1] - '0');
			break;
		case(1):
			grade += (inputArr[0] - '0');
		default:
			break;
		}
		if (grade > 100 || grade < 0) {
			return 0;
		}
	}
	outputArr[studentCounter][courseCounter] = grade;
	SubSpace(inputArr, gradeLen);
	DelTrailingSpace(inputArr);
	return 1;
}

/********************************************************************************************************************
* Function Name: UpdateGrade
* Input: char inputArr (Max length 200), int outputArr (Between 1 to 100)
* Output: int (0 or 1) that tells the calling function if the grade input is valid or not, 0 = invalid and 1 = valid
* Function Operation: The function checks the length (in chars) of the grade, by checking the amount of chars until
*						the ';' character which notes the end of the grade.
*						then, according to the length it calculates the grade as an integer by using multiplication
*						if after converting the char grade to int it's either smaller than 0 or larger than 100
*						the function returns 0, telling the calling function the grade is invalid.
*						(Basically the same function as ExtractGrade, except it needs to receive less parameters
*						to update)
********************************************************************************************************************/

int UpdateGrade(char *inputArr, int *outputArr) {
	int gradeLen = 0, grade = 0, gradeNum = 0;
	for (int i = 0; i < MAX_STRING; i++) {
		if (inputArr[i] != ';') {
			gradeLen++;
		}
		else {
			break;
		}
	}
	if (gradeLen > 3) {
		return 0;
	}
	else {
		switch (gradeLen) {
		case(3):
			grade += ((inputArr[0] - '0') * 100);
			grade += ((inputArr[1] - '0') * 10);
			grade += (inputArr[2] - '0');
			break;
		case(2):
			grade += ((inputArr[0] - '0') * 10);
			grade += (inputArr[1] - '0');
			break;
		case(1):
			grade += (inputArr[0] - '0');
		default:
			break;
		}
		if (grade > 100) {
			return 0;
		}
	}
	outputArr[0] = grade;
	SubSpace(inputArr, gradeLen);
	DelTrailingSpace(inputArr);
	return 1;
}

/********************************************************************************************************************
* Function Name: PrintError
* Input: No input parameters
* Output: No output, returns void
* Function Operation: The function prints an error message in the calling function 
********************************************************************************************************************/

void PrintError() {
	printf("Error: invalid name or grade.\n");
	return;
}

/********************************************************************************************************************
* Function Name: SubSpace
* Input: char inputArr (Max size 20), int nameLen (Between 1 to 20)
* Output: No output, returns void
* Function Operation: The function replaces the given course name (through nameLen on inputArr) with spaces
*						So that we could delete the course from our temporary array by using DelTrailingSpaces
********************************************************************************************************************/

void SubSpace(char *inputArr, int nameLen) {
	for (int i = 0; i <= nameLen; i++) {
		inputArr[i] = ' ';
	}
}

/********************************************************************************************************************
* Function Name: ClearRegistry
* Input: char fName (Max length 20), char sName (Max Length 20), char courses(Max len 20),
		int grades (Between 0 and 100), int studentCounter (Between 0 and 50)
* Output: No output, returns void
* Function Operation: The function clears completely the given arrays on the received student index
*						(via studentCounter), so that we can add a different student to the same index, if we 
*						received improper data when trying to add a student.
*						It simply sets the name arrays to NULL, and iterates through each course index, setting
*						NULL char to the name and -1 to the grade. (Same values we initialized with)
********************************************************************************************************************/

void ClearRegistry(char fName[][MAX_NAME], char sName[][MAX_NAME], char courses[][MAX_COURSES][MAX_NAME],
	int grades[][MAX_COURSES], int studentCounter) {
	*fName[studentCounter] = '\0';
	*sName[studentCounter] = '\0';
	for (int i = 0; i < MAX_COURSES; i++) {
		*courses[studentCounter][i] = '\0';
		grades[studentCounter][i] = -1;
	}
}

/********************************************************************************************************************
* Function Name: CalculateAvg
* Input: int grades(Between 0 to 100), int studentNumber(Between 0 to 50)
* Output: int that represents the average grade of the students courses
* Function Operation: The function sums up all the grades in the students registry (and counts the number of grades/
*						courses) and finally returns the value (int already performs floor division) of the 
*						sum divided by number of courses
********************************************************************************************************************/

int CalculateAvg(int grades[][MAX_COURSES], int studentNumber) {
	int sum = 0, numOfCourses = 0;
	for (int i = 0; i < MAX_COURSES; i++) {
		if (grades[studentNumber][i] != -1) {
			sum += grades[studentNumber][i];
			numOfCourses++;
		}
	}
	if (numOfCourses == 0) {
		return 0;
	}
	return sum / numOfCourses;
}

/********************************************************************************************************************
* Function Name: CalculateMax
* Input: int grades(Between 0 to 100), int studentNumber(Between 0 to 50)
* Output: int that represents the highest grade of the students courses
* Function Operation: The function iterates through the students courses and sets the maxGrade if the current grade
*						at the i index is higher than the maxGrade.
********************************************************************************************************************/

int CalculateMax(int grades[][MAX_COURSES], int studentNumber) {
	int maxGrade = 0;
	for (int i = 0; i < MAX_COURSES; i++) {
		if (grades[studentNumber][i] > grades[studentNumber][i + 1] && (grades[studentNumber][i] > maxGrade)){
			maxGrade = grades[studentNumber][i];
		}
	}
	return maxGrade;
}

/********************************************************************************************************************
* Function Name: CalculateMin
* Input: int grades(Between 0 to 100), int studentNumber(Between 0 to 50)
* Output: int that represents the lowest grade of the students courses
* Function Operation: The function iterates through the students courses and sets the minGrade if the current grade
*						at the i index is lower than the minGrade.
********************************************************************************************************************/

int CalculateMin(int grades[][MAX_COURSES], int studentNumber) {
	int minGrade = grades[studentNumber][0];
	for (int i = 0; i < MAX_COURSES; i++) {
		if (grades[studentNumber][i] < minGrade && grades[studentNumber][i] != -1){
			minGrade = grades[studentNumber][i];
		}
	}
	return minGrade;
}

/********************************************************************************************************************
* Function Name: CalculateSum
* Input: int grades(Between 0 to 100), int studentNumber(Between 0 to 50)
* Output: int that represents the sum of the students courses' grades.
* Function Operation: The fucntion iterates through the students' grades, summing them up as it goes
********************************************************************************************************************/

int CalculateSum(int grades[][MAX_COURSES], int studentNumber) {
	int sum = 0;
	for (int i = 0; i < MAX_COURSES; i++) {
		if (grades[studentNumber][i] != -1) {
			sum += grades[studentNumber][i];
		}
	}
	return sum;
}

/********************************************************************************************************************
* Function Name: CountCourses
* Input: int grades(Between 0 to 100), int studentNumber(Between 0 to 50)
* Output: int that represents the number of courses the student has
* Function Operation: The fucntion iterates through the students' grades, for every valid grade (not -1, since it's
*					  our initalization value) it adds one to the counter
********************************************************************************************************************/

int CountCourses(int grades[][MAX_COURSES], int studentNumber) {
	int coursesCount = 0;
	for (int i = 0; i < MAX_COURSES; i++) {
		if (grades[studentNumber][i] != -1) {
			coursesCount++;
		}
	}
	return coursesCount;
}

/********************************************************************************************************************
* Function Name: CountStudents
* Input: int fName(Max length 20)
* Output: int that represents the number of students currently saved in the memory
* Function Operation: The function iterates through the indexes (up to the max students value) and checks if the 
*						first character of the first name is NULL, if it isn't, add one to the studentCounter.
********************************************************************************************************************/

int CountStudents(char fName[][MAX_NAME]) {
	int studentCount = 0;
	for (int i = 0; i < MAX_STUDENTS; i++) {
		if (fName[i][0] != '\0') {
			studentCount++;
		}
	}
	return studentCount;
}

/********************************************************************************************************************
* Function Name: SortStudents
* Input: char fName (Max length 20), char sName (Max Length 20), char courses(Max len 20),
*		int grades (Between 0 and 100)
* Output: No output, returns void
* Function Operation: The function performs a bubble sort technique by comparing two adjacent strings, in our given
*						first name and last name arrays.
*						The function checks the ascii value of the two strings and switches them if the second one
*						is smaller than the first one. Eventually reaching a lexicographical order.
*						This will be performed for the first name, and if the first name is equal, it'll sort the
*						last name as well.
********************************************************************************************************************/

void SortStudents(char fName[][MAX_NAME], char sName[MAX_STUDENTS][MAX_NAME], char courses[MAX_STUDENTS]
	[MAX_COURSES][MAX_NAME], int grades[MAX_STUDENTS][MAX_COURSES]) {
	int studentCount = CountStudents(fName);
	// First Name Sort
	for (int i = 0; i < studentCount - 1; i++) {
		for (int j = i + 1; j < studentCount; j++) {
			if (strcmp(fName[i], fName[j]) > 0 && fName[j] != '\0') {
				SwapStr(fName[i], fName[j]);
				SwapStr(sName[i], sName[j]);
				for (int k = 0; k < MAX_COURSES; k++) {
					if (courses[i][k][0] != '\0'){
					SwapStr(courses[i][k], courses[j][k]);
					SwapInt(&grades[i][k], &grades[j][k]);
				}
					else {
						if (courses[j][k][0] != '\0') {
							SwapStr(courses[j][k], courses[i][k]);
							SwapInt(&grades[j][k], &grades[i][k]);
						}
					}
				}
			}
		}
	}
	// Last Name Sort (If the first name is equal)
	for (int i = 0; i < studentCount - 1; i++) {
		for (int j = i + 1; j < studentCount; j++) {
			if (strcmp(fName[i], fName[j]) == 0) {
				if (strcmp(sName[i], sName[j]) > 0) {
					SwapStr(sName[i], sName[j]);
					for (int k = 0; k < MAX_COURSES; k++) {
						if (courses[i][k][0] != '\0') {
							SwapStr(courses[i][k], courses[j][k]);
							SwapInt(&grades[i][k], &grades[j][k]);
						}
						else {
							if (courses[j][k][0] != '\0') {
								SwapStr(courses[j][k], courses[i][k]);
								SwapInt(&grades[j][k], &grades[i][k]);
							}
						}
					}
				}
			}
		}
	}

	return;
}

/********************************************************************************************************************
* Function Name: SwapStr
* Input: char firstStudent (Max length 20), char secondStudent (Max length 20)
* Output: No output, returns void
* Function Operation: The function copies the string from one array into a temporary array (which is MAX_NAME + 1
*						to avoid problems with junk values passing to the other array)
*						then copies the str from the second array to the first and finally moving the string
*						of the first array to the second one through the temporary array
********************************************************************************************************************/

void SwapStr(char *firstStudent, char *secondStudent) {
	char tempCourse[MAX_NAME + 1];
	strcpy(tempCourse, firstStudent);
	strcpy(firstStudent, secondStudent);
	strcpy(secondStudent, tempCourse);
}

/********************************************************************************************************************
* Function Name: SwapInt
* Input: int firstStudent (Between 0 to 100), int secondStudent (Between 0 to 100)
* Output: No output, returns void
* Function Operation: The function copies the value from one array into a temporary array and then copies
*						the value from the second array to the first and finally moving the value
*						of the first array to the second one through the temporary array
********************************************************************************************************************/

void SwapInt(int *firstStudent, int *secondStudent) {
	int tempGrade;
	tempGrade = *firstStudent;
	*firstStudent = *secondStudent;
	*secondStudent = tempGrade;

}