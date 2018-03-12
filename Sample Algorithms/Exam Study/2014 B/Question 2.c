#include <stdio.h>
#include <string.h>

#define MAX_LEN 30

typedef enum Result {FAILURE,SUCCESS} Result;

typedef struct course_s{
    char lecturer[MAX_LEN];
    char name[MAX_LEN];
    int id;
} course_s;

typedef struct courseList{
    course_s* course;
    struct courseList* next;
    struct courseList* prev;
} courseList;

// A. Create a function that creates a two way linked list with one element

courseList* CreateCourseList(char lecturer[MAX_LEN], char name[MAX_LEN], int id){
    courseList* newList = (courseList*) malloc (sizeof(courseList));
    if(newList == NULL){
        return NULL;
    }
    newList->next = NULL;
    newList->prev = NULL;
    newList->course = (course_s*)malloc(sizeof(course_s));
    if(newList->course == NULL){
        free(newList);
        return NULL;
    }
    newList->course->id = id;
    strcpy(newList->course->lecturer,lecturer);
    strcpy(newList->course->name,name);
    return newList;
}

// B. Create a function that deletes the course with the specified ID

courseList* DeleteCourse(courseList* courseHead,int id){
    while(courseHead != NULL){
        if(courseHead->course->id == id){
            free(courseHead->course);
            if(courseHead->prev == NULL){
                struct courseList* temp = courseHead->next;
                free(courseHead);
                return temp;
            }
            else{
                courseHead->prev->next = courseHead->next;
                free(courseHead);
                return courseHead;
            }
        }
        courseHead = courseHead->next;
    }
}

// C. Create a function that returns the first course the specified lecturer teaches

course_s* GetCourseByIndex(courseList* list, char lecturer[MAX_LEN]){
    while(list != NULL){
        if(strcmp(list->course->lecturer,lecturer) == 0){
            return list->course;
        }
        list = list->next;
    }
    return NULL;
}


// D. Create a function that completely delets a double linked list

void destroyList(courseList* list){
    while(list != NULL){
        courseList* temp = list->next;
        free(list->course);
        free(list);
        list = temp;
    }
}