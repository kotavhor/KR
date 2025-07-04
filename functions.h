#include <iostream>
struct Student {

    char name[30];
    int32_t group;
    double grade;
};

void SortByName(Student* students, int32_t size);

void PrintStudents(const Student* students, int32_t size);

int32_t CountLines(const char* filename);

int32_t FindBySurname(const Student* students, int32_t size, const char* surname);

void SortByGroupAndName(Student* students, int32_t size);

void LoadStudentsFromFile(const char* filename, Student* students, int32_t size);
