#include "functions.h"          
#include <iostream>             

int main() {
    const char* filename = "students.txt";
    Student* students = nullptr;
    int32_t size{};

    try {
        size = CountLines(filename);        // Считаем количество строк в файле (т.е. студентов)
        students = new Student[size];       // Выделяем динамическую память под массив студентов
        LoadStudentsFromFile(filename, students, size);  // Загружаем данные из файла в массив
    }
    catch (const std::exception& exc) {
        std::cerr << "Error: " << exc.what() << "\n"; // Выводим сообщение об ошибке
        return 1;                                     // Завершаем программу с кодом ошибки
    }

    int32_t choice;
    do {

        std::cout << "\nMenu:\n";
        std::cout << "1) Sort by surname\n";
        std::cout << "2) Find by surname\n";
        std::cout << "3) Sort by surname and group\n";
        std::cout << "4) Average grade by group\n"; // Нет функции которая считает средний балл в группе
        std::cout << "0) Cancel\n";
        std::cout << "Choice: " << '\n';
        std::cin >> choice;

        try {
            switch (choice) {
            case 1:
                SortByName(students, size);      // Сортировка студентов по фамилии
                PrintStudents(students, size);   // Вывод отсортированного списка
                break;
            case 2: {
                char surname[30];
                std::cout << "Input surname: ";
                std::cin >> surname;
                int32_t index = FindBySurname(students, size, surname); // Поиск сиудента
                if (index >= 0) {
                    std::cout << "Found: " << students[index].name
                        << ", group " << students[index].group
                        << ", grade " << students[index].grade << "\n";
                }
                else {
                    std::cout << "Student not found.\n"; 
                }
                break;
            }
            case 3:
                SortByGroupAndName(students, size);    // Сортировка по группе и фамилии
                PrintStudents(students, size);         // Вывод результата
                break;
            case 4:
                PrintAverageByGroup(students, size); // Вывод ср.оц. по груам
                break;
                break;
            case 0:
                std::cout << "Cancel.\n";
                break;
            default:
                std::cout << "Incorrect choice.\n";
            }
        }
        catch (const std::exception& exc) {
            std::cerr << "Error: " << exc.what() << "\n";
        }
    } while (choice != 0); {
        delete[] students;
    }
    return 0;
}