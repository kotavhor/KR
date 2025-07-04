#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "functions.h"



int32_t CountLines(const char* filename) { // количество строк в текстовом файле
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    int32_t count{};
    std::string line;
    while (std::getline(file, line)) {
        ++count;
    }
    return count;
}


void LoadStudentsFromFile(const char* filename, Student* students, int32_t size) { // Список студентов из файла переносим в массив
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Opening file error");
    }

    char buffer[100];
    int32_t index{};

    while (file.getline(buffer, sizeof(buffer)) && index < size) {
        char* name = strtok(buffer, ";");
        char* groupStr = strtok(nullptr, ";");
        char* gradeStr = strtok(nullptr, ";");

        if (!name || !groupStr || !gradeStr) {
            throw std::runtime_error("Wrond string in file");
        }

        strncpy(students[index].name, name, sizeof(students[index].name));
        students[index].group = std::atoi(groupStr); // Меняем строки в int (группы)
        students[index].grade = std::atof(gradeStr); // Меняем строки в double (средний балл)
        ++index;
    }
}


void PrintStudents(const Student* students, int size) { // Вывод списка учеников
    for (int32_t i{}; i < size; ++i) {
        std::cout << students[i].name << " | Group: " << students[i].group
            << " | Average grade: " << students[i].grade << "\n";
    }
}

void SortByGroupAndName(Student* students, int32_t size) { // Сортировка по группам и именам
    for (int32_t i{}; i < size - 1; ++i)
        for (int j{ i + 1 }; j < size; ++j)
            if (students[i].group > students[j].group ||
                (students[i].group == students[j].group &&
                    strcmp(students[i].name, students[j].name) > 0)) {
                std::swap(students[i], students[j]);
            }
}


void SortByName(Student* students, int32_t size) {
    for (int32_t i{}; i < size - 1; ++i)
        for (int32_t j{ i + 1 }; j < size; ++j)
            if (strcmp(students[i].name, students[j].name) > 0) {
                std::swap(students[i], students[j]);
            }
}

int32_t FindBySurname(const Student* students, int32_t size, const char* surname) {
    for (int32_t i{}; i < size; ++i) {
        if (std::strstr(students[i].name, surname) == students[i].name) {
            return i;
        }
    }
    return -1;
}