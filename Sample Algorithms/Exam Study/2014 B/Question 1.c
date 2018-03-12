/*
Define a binary tree of students
a Student contains:
1. ID
2. Name
3. Last Name
4. Dynamic Array of courses (Course is represented by Name and Grade)
5. Faculty (Math,CS,Informatics,Neuroscience)
*/

typedef enum faculty {MATH=99,CS=98,INFORMATICS=97,NEUROSCIENCE=96} faculty;

typedef struct Courses{
    char* name;
    int grade;
} Course;

typedef struct StudenData{
    int ID;
    char* firstName;
    char* lastName;
    Course* courses;
    faculty subject;

} StudentData;

typedef struct StudentNode{
    StudentData* data;
    struct StudentNode* left;
    struct StudentNode* right;
} StudentNode;

typedef struct StudentBinaryTree{
    StudentNode* root;
} StudentBinaryTree;