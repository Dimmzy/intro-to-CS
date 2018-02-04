/********************************
* Student Name: Dmitri Zinkevich
* Student ID: 317301596
* Course Exercise Group: 01
* Exercise Name: Exercise 6
********************************/

#include <stdio.h>
#include "utils.h"
#define PRINT_DASH "----------\n"

/***************************************************************************************************************
* Function Name: PrintCircle
* Input: Pointer to the head of the linked list (or the next person, recursively)
* Output: No Output, Void
* Function Operation: The function prints the people in the list in order by calling itself recursively
*					  each time pointing to the next person in the list, until we get to ->next == NULL
*					  which marks the end of the linked list.
***************************************************************************************************************/

void PrintCircle(Person* head) {
	if (head != NULL) {
		head->Print(head);
		// If there are still people to print (next person's pointer isn't NULL) the function calls itself to continue
		if (head->next != NULL) {
			PrintCircle(head->next);
		}
		// If the next person's pointer is NULL we finished printing the circle, prints dashes and returns
		else {
			printf(PRINT_DASH);
		}
	}
}

/***************************************************************************************************************
* Function Name: FindByID
* Input: (1) Pointer to a node in the linked list (2) the ID of the person we look for
* Output: Pointer to the person matching the ID
* Function Operation: At it's first iteration the function receives the head of the linked list and an ID.
*					  It then beings to check if the person's ID in the specified node matches the given ID,
*					  if it doesn't, and we still have nodes to search, the function calls itself recursively
*					  and keeps searching for a match. If we iterated through all of the list (->next is NULL)
*					  it returns NULL to the calling function, which means the ID is not found in our list.
***************************************************************************************************************/

Person* FindByID(Person* node, int id) {
	if (node->id == id) {
		return node;
	}
	else if (node->next != NULL) {
		return FindByID(node->next, id);
	}
	else {
		return NULL;
	}
}

/***************************************************************************************************************
* Function Name: SwapNodes
* Input: (1) Pointer to a node in the linked list (2) Pointer to the following node in the linked list
* Output: No Output, Void
* Function Operation: The function receives two pointers which point to a node and the subsequent node. 
*					  It then backs up the values in the first node, and then replacing it's values with the 
*					  second node's ones, then it simply restores the backups into the second node's values.
*					  Basically performing a complete swap between the values of two nodes.
***************************************************************************************************************/

void SwapNodes(Person* nodeOne, Person* nodeTwo) {
	// Back up the values in the nodeOne struct to prepare for swapping
	char* nameTemp = nodeOne->name;
	int idTemp = nodeOne->id;
	int numOfKidsTemp = nodeOne->numOfKids;
	char** kidsTemp = nodeOne->kids;
	// Swapping first node values with the second values
	nodeOne->name = nodeTwo->name;
	nodeOne->id = nodeTwo->id;
	nodeOne->numOfKids = nodeTwo->numOfKids;
	nodeOne->kids = nodeTwo->kids;
	// Replacing the second node's values with the nodeOne backup
	nodeTwo->name = nameTemp;
	nodeTwo->id = idTemp;
	nodeTwo->numOfKids = numOfKidsTemp;
	nodeTwo->kids = kidsTemp;
}

/***************************************************************************************************************
* Function Name: FreeCircle
* Input: Pointer to the head of the linked list
* Output: No Output, Void
* Function Operation: The function iterates through the linked list, performing SelfDestruct on each node
*					  Which frees the memory allocated to the specific node, until there are no more nodes
*					  remaining. This function gets called only if we failed to allocate memory during the
*					  first circle formation. (Not when trying to insert people late to the circle)
***************************************************************************************************************/

void FreeCircle(Person** head) {
	Person* current = *head;
	while (current != NULL) {
		current = current->SelfDestruct(current);
	}
	*head = NULL;
}