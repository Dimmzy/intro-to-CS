
// Create a two way linked list

typedef struct Line {
    int start[2];
    int end[2];
} Line;

typedef struct LinesList {
    Line* line;
    struct LinesList* next;
    struct LinesList* previous;
} LinesList;

