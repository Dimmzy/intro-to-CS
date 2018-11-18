

#include <stdio.h>
#include "ex5.h"


int main() {
	// Initializes our arrays for each part of the name, courses and grades which we will use to store the student info
	char firstName[MAX_STUDENTS][MAX_NAME] = { 0, };
	char surName[MAX_STUDENTS][MAX_NAME] = { 0, };
	char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME] = { 0, };
	int grades[MAX_STUDENTS][MAX_COURSES];
	int operationNumber;
	// Sets an exit flag that we will use to exit the program if 0 is given as input
	int exitFlag = 0;
	// We'll set every element in the grades array to -1 for easier accesss and iterations through our functions
	for (int i = 0; i < MAX_STUDENTS; i++) {
		for (int j = 0; j < MAX_COURSES; j++) {
			grades[i][j] = -1;
		}
	}
	PrintMenu();
	// Endless loop that exits only when exitFlag = 1 (which gets set if we receive 0 as input in the menu)
	while (1) {
		scanf(" %d", &operationNumber);
		// Switch statement that directs which function gets called according to our given input in the scanf function
		switch(operationNumber){
		case(0):
			exitFlag = 1;
			break;
		case(1):
			ModStudent(firstName, surName, courses, grades);
			PrintNxtOp();
			break;
		case(2):
			DelStudent(firstName, surName, courses, grades);
			PrintNxtOp();
			break;
		case(3):
			Aggregate(firstName, surName, courses, grades, 1);
			PrintNxtOp();
			break;
		case(4):
			Aggregate(firstName, surName, courses, grades, 2);
			PrintNxtOp();
			break;
		case(5):
			PrintMenu();
			break;
		default:
			printf("Error: unrecognized operation.\n");
		}
		if (exitFlag == 1) {
			break;
		}
	}
	return 0;
}
