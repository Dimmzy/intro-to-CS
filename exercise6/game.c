/********************************
* Student Name: Dmitri Zinkevich
* Student ID: 317301596
* Course Exercise Group: 01
* Exercise Name: Exercise 6
********************************/

#include "game.h"
#include "utils.h"
#include <stdio.h>
#define ADD_PERSON "Add a person to the game? (0|1)\n"
#define ASK_LATE "Are you late? (0|1)\n"
#define INSERT_BF_ID "Insert your best friend's ID:\n"
#define ASK_COWARD "Is there a coward in here? (0|1)\n"
#define INSERT_COWARD_ID "Insert your ID, you, lame pudding-heart coward:\n"
#define PRINT_COWARD "Let the world know that you are a coward, %s!\n"
#define ID_ERROR "No Such ID: %d\n"
#define WIN_MSG "Ah, ha, ha, ha, stayin' alive, stayin' alive! Ah, ha, ha, ha, \"%s\" stayin' alive!\n" 

/***************************************************************************************************************
* Function Name: InitTheHungerGames
* Input: No Input
* Output: Pointer to the head of the linked list
* Function Operation: The function forms the first circle of people. If we want to add a person we'll first
*					  begin by calling CreatePerson directly to receive the pointer to the head of the newly
*					  created linked list, subsequent additions will be through the CreateNext function.
*					  finally it returns the head of the linked list to main.
***************************************************************************************************************/

Person* InitTheHungerGame() {
	int addPerson;
	Person* head = NULL;
	printf(ADD_PERSON);
	scanf("%d", &addPerson);
	// If it's the first time we add a person, we call CreatePerson directly to get the head of the list
	if (addPerson == 1) {
		head = CreatePerson();

		/*
		If we fail to allocate the memory for the person, we'll return NULL to main and our circle will be empty
		freeing the already allocated memory will be done inside the function CreatePerson itself.
		*/

		if (head == NULL) {
			return NULL;
		}
	}
	else {
		return NULL;
	}
	// Begins a loop that ends when the user doesn't want to add anymore people (not 1 as input)
	while (1) {
		printf(ADD_PERSON);
		scanf("%d", &addPerson);
		if (addPerson == 1) {
			// Calls the CreateNext function with 0 as a isNextNext argument (which means the person isn't late)
			head->CreateNext(head, 0);
		}
		else {
			break;
		}
	}
	return head;
}

/***************************************************************************************************************
* Function Name: InsertLaters
* Input: Pointer to the head of the linked list
* Output: No Output, Void
* Function Operation: The function adds people that are late to the list by receiving input from the user that
*					  states after which person we want to add the new person (in the form of ID number).
*					  It then sends the pointer to the head, the argument 1 and the ID to CreateNext which
*					  will find the person we need to add after and it'll place him there.
*					  Afterwards it'll call itself recursively until we finished adding the later people.
***************************************************************************************************************/

void InsertLaters(Person* head) {
	if (head == NULL) {
		return;
	}
	int addLater;
	printf(ASK_LATE);
	scanf("%d", &addLater);
	if (addLater == 1) {
		int friendId;
		printf(INSERT_BF_ID);
		scanf("%d", &friendId);
		head->CreateNext(head,1,friendId);
		InsertLaters(head);
	}
}

/***************************************************************************************************************
* Function Name: RemoveCowards
* Input: Pointer to the head of the linked list
* Output: Pointer to the new head of the linked list
* Function Operation: The function removes nodes from the linked list by receiving an ID of the person we want
*					  to remove, finding his location through FindByID and then performing SelfDestruct to
*					  remove him from the list.
***************************************************************************************************************/

Person* RemoveCowards(Person* head) {
	// Make sure we even have anything to remove, if we don't we return
	while (1) {
		if (head == NULL) {
			break;
		}
		int cowardExists;
		printf(ASK_COWARD);
		scanf("%d", &cowardExists);
		if (cowardExists == 1) {
			int cowardID;
			printf(INSERT_COWARD_ID);
			scanf("%d", &cowardID);
			Person* coward = FindByID(head, cowardID);
			if (coward != NULL) {
				// If the person we're removing is the current head of the list, we'll appoint the next person as head
				if (coward == head) {
					printf(PRINT_COWARD, coward->name);
					head = coward->SelfDestruct(coward);
				}
				// Otherwise we iterate through the list, when we remove the person we'll fix the "link" between nodes
				else {
					printf(PRINT_COWARD, coward->name);
					Person* current = head;
					Person* previous = NULL;
					int counter = 0;
					// Saves the pointer to the next person from the removed person
					Person* fixLink = coward->SelfDestruct(coward);
					while (current != coward) {
						previous = current;
						current = current->next;
					}
					// Sets the ->next of the previous person to be the ->next of the removed one (to fix the link)
					previous->next = fixLink;
					previous = NULL;
					current = NULL;
				}

			}
			// If the pointer coward we received from FindByID is NULL, it means the ID isn't in the list.
			else {
				printf(ID_ERROR, cowardID);
			}
		}
		else {
			break;
		}
	}
	return head;
}

/***************************************************************************************************************
* Function Name: LetTheHungerGamesBegin
* Input: Pointer to the head of the linked list
* Output: No Output, Void
* Function Operation: The function begins the Josephus' Problem circle of death. We start by linking the last
*					  node with the first one so we can iterate through much easier.
*					  Afterwards we start killing every second person by using the KillNext function from the
*					  the person before him, eventually reaching only one node in the list which is the
*					  survivor of the circle.
***************************************************************************************************************/

void LetTheHungerGameBegin(Person* head) {
	if (head == NULL) {
		return;
	}
	// We'll start by linking the last node to the first one for easier iteration
	Person* current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	if (current != head) {
		current->next = head;
	}
	current = head;
	// While we still have people in the list (and the next person isn't the person itself)
	while(current->next != current) {
		// We call the KillNext function which kills the person next in the list
		current->KillNext(current);
		current = current->next;
	}
	// Eventually reaching the final person which survives, and then tragically SelfDestructs to free the memory.
	printf(WIN_MSG, current->name);
	current->SelfDestruct(current);
}
