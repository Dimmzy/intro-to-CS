#include "person.h"
#include "utils.h"
#include "sorting.h"
#include "game.h"
#include <stdio.h>

int main() {
    Person* head = InitTheHungerGame();
	PrintCircle(head);
    InsertLaters(head);
    PrintCircle(head);
    head = RemoveCowards(head);
    PrintCircle(head);
    head = SortCircleByName(head);
	printf("BREAK POINT BY NAME\n");
    PrintCircle(head);
    head = SortCircleByID(head);
	printf("BREAK POINT BY ID\n");
    PrintCircle(head);
	FreeCircle(&head);
	PrintCircle(head);
    return 0;
}


