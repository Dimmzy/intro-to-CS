
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "utils.h"
#include "person.h"

// Defines the maximum length of a name, and defines the printf function arguments 

#define MAX_NAME 80
#define NAME_INPUT "Name:\n"
#define ID_INPUT "ID:\n"
#define NUM_KIDS_INPUT "Num of kids:\n"
#define KID_NAME_INPUT "Kid #%d name:\n"
#define ID_ERROR "No Such ID: %d\n"
#define KILL_PRINT "%s kills %s "
#define KILL_KIDS_PRINT "and %s "
#define DASH_PRINT "----------\n"
#define NAME_PRINT "Name: %s\n"
#define ID_PRINT "ID: %d\n"
#define KID_NAME_PRINT "Kid #%d: %s\n"

// Some function definitions we'll use

void Print(struct Person* this);
void KillNext(struct Person* this);
struct Person* SelfDestruct(struct Person* this);

/***************************************************************************************************************
* Function Name: CreatePerson
* Input: None 
* Output: Pointer to the created person's struct
* Function Operation: The function allocates memory and creates a new structure for the person
*					  It receives input from the user and sets the values in the struct from the give input.
*					  It also allocates memory for an array that holds the name of the person, and a 2D array
*					  that holds the person's kids and their names.
***************************************************************************************************************/

Person* CreatePerson() {
	Person *newPerson;
	newPerson = (Person *)malloc(sizeof(Person));
	// Checks if the allocation was successful, if it wasn't, it returns NULL to the calling function
	if (newPerson == NULL) {
		return NULL;
	}
	// Initializes the new array
	InitPersonValues(newPerson);
	int id, numOfKids;
	// Allocates memory for the name and checks if the allocation was successful
	char *namep = (char *)malloc(MAX_NAME);
	if (namep == NULL) {
		free(newPerson);
		return NULL;
	}
	// We receive input from the user and set the matching values in the struct to our given input
	printf(NAME_INPUT);
	scanf("%s", namep);
	newPerson->name = namep;
	printf(ID_INPUT);
	scanf("%d", &id);
	newPerson->id = id;
	printf(NUM_KIDS_INPUT);
	scanf("%d", &numOfKids);
	newPerson->numOfKids = numOfKids;
	newPerson->next = NULL;
	// Creates a 2D array that lets us record and access the person's kid's names (if he has any kids)
	if (numOfKids > 0) {
		char** kids = (char** )malloc(numOfKids * sizeof(char *));
		if (kids == NULL) {
			free(newPerson->name);
			free(newPerson);
			return NULL;
		}
		for (int i = 0; i < numOfKids; i++) {
			kids[i] = (char* )malloc(MAX_NAME * sizeof(char));
			if (kids[i] == NULL) {
				for (int j = i; j > 0; j--) {
					free(newPerson->kids[i]);
				}
				free(newPerson->name);
				free(newPerson->kids);
				free(newPerson);
				return NULL;
			}
			printf(KID_NAME_INPUT, i+1);
			scanf("%s", kids[i]);
		}
		newPerson->kids = kids;
	}
	// Finally, we return a pointer to the struct we just created
	return newPerson;
}

/******************************************************************************************************************
* Function Name: CreateNext
* Input:(1) Pointer to the struct the function is called from (2) int (0 or 1) that defines if the person is "late"
*		 to the circle (3) int argument which dictates after which ID we'll add the person (any natural number)
* Output: No Output, Void
* Function Operation: The main use of the function is to call CreatePerson, and then find and appoint a spot for
*					  the new person in our linked list. If we receive 0 as isNextNext argument, we'll simply
*					  iterate through our linked list and insert the new person at the end.
*					  If we receive 1 as the argument, we'll extract the ID argument from the variadic function
*					  and then call FindByID which helps us find the pointer to the person with the said ID, which
*					  we'll use to insert our new person after him.
******************************************************************************************************************/

void CreateNext (struct Person* this, int isNextNext, ...) {
	if (isNextNext == 0) {
		Person *newPerson = CreatePerson();
		// If the allocation failed (we received NULL from CreatePerson), we'll free the memory of the whole circle
		if (newPerson == NULL) {
			FreeCircle(&this);
		}
		// Otherwise, we iterate through our list, looking for the last node that we'll append our new person to 
		else {
			Person *current = this;
			while (1) {
				if (current->next == NULL) {
					current->next = newPerson;
					break;
				}
				current = current->next;
			}
		}
	}
	// Adding a person late to the circle
	else {
		// Extracts the third argument from the variadic function
		va_list ap;
		va_start(ap, isNextNext);
		int friendID = va_arg(ap, int);
		va_end(ap);
		// Call FindByID and get the pointer to his friends' node
		Person* friend = FindByID(this, friendID);
		// If we received NULL from FindByID it means the ID doesn't exist, so we return from the function.
		if (friend == NULL) {
			printf(ID_ERROR, friendID);
			return;
		}
		// If we found the ID we'll create the person and append him after his friend. Also checks allocation success
		Person* newPerson = CreatePerson();
		if (newPerson == NULL) {
			newPerson->SelfDestruct(newPerson);
		}
		// Performs a pointer swap so we can insert the person between two nodes if needed
		Person* temp = friend->next;
		newPerson->next = temp;
		temp = NULL;
		friend->next = newPerson;
	}
}

/******************************************************************************
* Function Name: InitPersonValues
* Input: Pointer to the person's struct we want to initialize
* Output: No Output, Void
* Function Operation: The function simply initializes the values of the struct
******************************************************************************/

void InitPersonValues(Person* person) {
	person->name = NULL;
	person->id = 0;
	person->numOfKids = 0;
	person->kids = NULL;
	person->next = NULL;
	person->Print = Print;	
	person->KillNext = KillNext;
	person->SelfDestruct = SelfDestruct;
	person->CreateNext = CreateNext;
}

/***********************************************************************************************
* Function Name: KillNext
* Input: Pointer to the person's struct we're calling the function from
* Output: No Output, Void
* Function Operation: The function "kills" the next person in the list from the calling person.
*					  It starts by printing the killing strings and then backing up the linking
*					  pointer of the person that's going to die. It calls SelfDestruct on the
*					  person being killed and then moves the pointer to the ->next of the person
*					  that killed him.
***********************************************************************************************/

void KillNext(struct Person* this) {
	printf(KILL_PRINT, this->name, this->next->name);
	if (this->next->numOfKids > 0) {
		for (int i = 0; i < this->next->numOfKids; i++) {
			printf(KILL_KIDS_PRINT, this->next->kids[i]);
		}
	}
	printf("\n");
	// Backs up the ->next pointer of the person that's about to die
	Person* temp = (this->next)->next;
	this->next->SelfDestruct(this->next);
	this->next = temp;
	// Sets the pointer to NULL to avoid loose ends
	temp = NULL;
}

/***********************************************************************************************
* Function Name: Print
* Input: Pointer to the person's struct we're calling the function from
* Output: No Output, Void
* Function Operation: The function simply prints the name,id and kids of the person it's called
*					  from in the required format.
***********************************************************************************************/

void Print(struct Person* this) {
	printf(DASH_PRINT);
	printf(NAME_PRINT, this->name);
	printf(ID_PRINT, this->id);
	if (this->numOfKids > 0) {
		for (int i = 0; i < this->numOfKids; i++) {
			printf(KID_NAME_PRINT, i + 1, *(this->kids + i));
		}
	}
}


/****************************************************************************************************
* Function Name: SelfDestruct
* Input: Pointer to the person's struct we're calling the function from
* Output: Pointer to the next person in the linked list (the one this person is pointing to)
* Function Operation: The function backs up the pointer to the next person, and then begins freeing
*					  the allocated memory from inside the struct (name array,2D kids array).
*					  finally freeing the struct and returning the pointer to the next person.
****************************************************************************************************/

struct Person* SelfDestruct(struct Person* this) {
	struct Person* temp = this->next;
	free(this->name);
	if (this->numOfKids > 0) {
		for (int i = 0; i < this->numOfKids; i++) {
			free(this->kids[i]);
		}
	}
	free(this->kids);
	free(this);
	return temp;
}
