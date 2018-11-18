

#ifndef UTILS_H
#define UTILS_H

#include "person.h"

/***************************************************************************************************************
* Function Name: PrintCircle
* Input: Pointer to the head of the linked list (or the next person, recursively)
* Output: No Output, Void
* Function Operation: The function prints the people in the list in order by calling itself recursively
*					  each time pointing to the next person in the list, until we get to ->next == NULL
*					  which marks the end of the linked list.
***************************************************************************************************************/

void PrintCircle(Person* head);

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

Person* FindByID(Person* head, int id);

/***************************************************************************************************************
* Function Name: SwapNodes
* Input: (1) Pointer to a node in the linked list (2) Pointer to the following node in the linked list
* Output: No Output, Void
* Function Operation: The function receives two pointers which point to a node and the subsequent node.
*					  It then backs up the values in the first node, and then replacing it's values with the
*					  second node's ones, then it simply restores the backups into the second node's values.
*					  Basically performing a complete swap between the values of two nodes.
***************************************************************************************************************/

void SwapNodes(Person* nodeOne, Person* nodeTwo);

/***************************************************************************************************************
* Function Name: FreeCircle
* Input: Pointer to the head of the linked list
* Output: No Output, Void
* Function Operation: The function iterates through the linked list, performing SelfDestruct on each node
*					  Which frees the memory allocated to the specific node, until there are no more nodes
*					  remaining. This function gets called only if we failed to allocate memory during the
*					  first circle formation. (Not when trying to insert people late to the circle)
***************************************************************************************************************/

void FreeCircle(Person** head);

#endif
