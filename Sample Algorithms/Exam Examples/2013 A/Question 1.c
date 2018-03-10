#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Create a Linked List consisting of a professor's data:
1. Name
2. Faculty
3. List of Articles
4. Satisfaction Rating
5. Number of Students in the Course
*/

// A. Write the DataType (professor) and the DataType that corresponds to a list of professors

typedef enum faculty {CS=99,Math=98,Physics=97} faculty;

typedef struct Papers{
    char* paperName;
    struct Papers* next;
} Papers;

typedef struct Professor{
    char* name;
    faculty facult;
    Papers* papersHead;
    float statisfactionRating;
    int numberOfStudents;
} Professor;

typedef struct ProfessorsList{
    Professor* headProfessor;
    struct professorsList* next;
}  ProfessorsList;

// B. Write a fucntion that receives an article and a professor and adds the article to the professor's list

void addPaper(Professor* professor, char* paperName){
    Papers* current = professor->papersHead;
    // Get to the end of the list
    while(current->next != NULL){
        current = current->next;
    }
    Papers* newPaper = (Papers*) malloc (sizeof(Papers));
    if(newPaper == NULL){
        return;
    }
    newPaper->paperName = paperName;
    newPaper->next = NULL;
    current->next = newPaper;
}

// C. Write a function that receives a list of professors and a professor, and adds him to the list

void addProf(Professor* professor, ProfessorsList* profList){
    ProfessorsList* current = profList;
    while(current->next != NULL){
        current = current->next;
    }
    ProfessorsList* addProf = (ProfessorsList*)malloc(sizeof(ProfessorsList));
    addProf->headProfessor = professor;
    addProf->next = NULL;
    current->next = addProf;
}

// D. Write a function that receives a list of professors, a subject and deletes all the professors that teach that subject

void fireProfessors(ProfessorsList* profList, faculty subject){
    ProfessorsList* current = profList;
    while(current != NULL){
        if(current->headProfessor->facult == subject){
            if(!(current->headProfessor->papersHead)){
            Papers* paperIter = current->headProfessor->papersHead;
            do{
                free(paperIter->paperName);
                Papers* temp = paperIter->next;
                free(paperIter->next);
                paperIter = temp;
            } while(paperIter->next != NULL);
            }
            free(current->headProfessor);
            ProfessorsList* temp = current->next;
            free(current);
            current = temp;
        }
    }
}

// E. Write a function that calculates the number of papers a professor has

int countArticles(Professor* professor){
    int numOfArticles = 0;
    Papers* current = professor->papersHead;
    while (current != NULL) {
        numOfArticles++;
        current = current->next;
    }
    return numOfArticles;
}

// F. Write a function that receives a list of Professors and arranges them by their number of articles.

void sortByNumOfArticles(ProfessorsList* profList){
    int numOfProfs = 0;
    int swapped;
    ProfessorsList* current = profList;
    while(current != NULL){
        numOfProfs++;
        current = current->next;
    }
    current = profList;
    do{
        swapped = 0;
    for(int i = 0 ; i < numOfProfs - 1; i++) {
        ProfessorsList* next = current->next;
        if(countArticles(current->headProfessor) > countArticles(next->headProfessor)){
            Professor* temp = current->headProfessor;
            current->headProfessor = next->headProfessor;
            next->headProfessor = temp;
            swapped = 1;
        }
        current = current->next;
    }
    }while(swapped = 1);

}

