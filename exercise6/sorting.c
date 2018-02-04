/********************************
* Student Name: Dmitri Zinkevich
* Student ID: 317301596
* Course Exercise Group: 01
* Exercise Name: Exercise 6
********************************/

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "sorting.h"

/***************************************************************************************************************
* Function Name: SortCircleByID
* Input: Pointer to the head of the linked list
* Output: Pointer to the new head of the linked list
* Function Operation: The function performs a bubble sort technique. It checks the values of the ID of two 
*					  adjacent nodes, if the first node's ID is larger than the second, it calls the SwapNodes 
*					  function which swaps the struct's values. It performs these checks until everything 
*					  is in place.
***************************************************************************************************************/

Person* SortCircleByID(Person* head) {
	if (head == NULL) {
		return head;
	}
	// Initializes swapped which tells us if the while iteration swapped anything (if it didn't, sorting is done)
	int swapped = 1;
	Person* current;
	Person* last = NULL;
	do {
		// Sets swapped to 0
		swapped = 0;
		current = head;
		while (current->next != last) {
			if (current->id > current->next->id) {
				SwapNodes(current, current->next);
				// Swapped is 1 because we changed values between two nodes
				swapped = 1;
			}
			// Proceeds to the next nodes
			current = current->next;
		}
		last = current;
	} while (swapped == 1);
	return head;
}

/*********************************************************************************************************************
* Function Name: SortCircleByName
* Input: Pointer to the head of the linked list
* Output: Pointer to the new head of the linked list
* Function Operation: The function performs a bubble sort technique. It uses strcmp to check the ASCII values of the
*					  names inside the two struct nodes, if the first one is larger than the second one, we'll swap
*					  the struct's values. It iterates through the list on and on until all of the nodes are in their
*					  proper spots according to the names.
*********************************************************************************************************************/

Person* SortCircleByName(Person* head) {
	if (head == NULL) {
		return head;
	}
	int swapped = 1;
	Person* current;
	Person* last = NULL;
	do {
		swapped = 0;
		current = head;
		while (current->next != last) {
			if (strcmp(current->name,current->next->name) > 0) {
				SwapNodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	} while (swapped == 1);
	return head;
}