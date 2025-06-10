#include <iostream>
#include <fstream>
#include <cstring>   
#include <string>    
#include <clocale>   
#include <algorithm> 
#include <limits>    
struct Student {
    char surname[50];
    int32_t group;
    double grade;
};

// Функция для загрузки студентов из файла
Student* loadStudents(const std::string& filename, int32_t& count) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return nullptr;
    }

    file >> count;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    Student* students = new Student[count];
    for (int32_t i = 0; i < count; i++) {
        file.getline(students[i].surname, 50);
        if (file.fail()) { // Проверка на случай, если строка слишком длинная или EOF
            std::cerr << "Ошибка чтения фамилии для студента " << i << std::endl;
            delete[] students;
            return nullptr;
        }
        file >> students[i].group >> students[i].grade;
        if (file.fail()) { // Проверка на ошибку чтения группы/оценки
            std::cerr << "Ошибка чтения группы или оценки для студента " << students[i].surname << std::endl;
            delete[] students;
            return nullptr;
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
    }

    file.close();
    return students;
}

// Функция для поиска студента по фамилии (students теперь const)
Student* searchBySurname(const Student* students, int32_t count, const char* surname) {
    for (int32_t i = 0; i < count; i++) {
        if (strcmp(students[i].surname, surname) == 0) {
            return const_cast<Student*>(&students[i]); // Убираем const для возврата Student*
        }
    }
    return nullptr;
}

// Функция для сортировки студентов по фамилии
void sortBySurname(Student* students, int32_t count) {
    for (int32_t i = 0; i < count - 1; i++) {
        for (int32_t j = 0; j < count - 1 - i; j++) {
            if (strcmp(students[j].surname, students[j + 1].surname) > 0) {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
}

// Вспомогательная функция для вывода списка студентов
void printStudents(const Student* students, int32_t count) {
    if (!students || count <= 0) {
        std::cout << "Список студентов пуст.\n";
        return;
    }
    std::cout << "Список студентов:\n";
    for (int32_t i = 0; i < count; ++i) {
        std::cout << "Фамилия: " << students[i].surname
            << ", Группа: " << students[i].group
            << ", Оценка: " << students[i].grade << std::endl;
    }
}

void menu(Student* students, int32_t count) {
    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Сортировать по фамилии\n";
        std::cout << "2. Найти студента по фамилии\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите операцию: ";
        std::cin >> choice;

        // Очистка буфера ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            sortBySurname(students, count);
            std::cout << "Сортировка завершена!\n";
            printStudents(students, count); // Показываем результат сортировки
            break;
        case 2: {
            char surname[50];
            std::cout << "Введите фамилию: ";
            std::cin.getline(surname, 50);
            Student* found = searchBySurname(students, count, surname);
            if (found) {
                std::cout << "Найден студент: " << found->surname << ", Группа: "
                    << found->group << ", Оценка: " << found->grade << std::endl;
            }
            else {
                std::cout << "Студент не найден.\n";
            }
            break;
        }
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::ofstream test_file("s.txt");
    if (!test_file) {
        std::cerr << "Не удалось создать тестовый файл 's.txt'.\n";
        return 1;
    }

    test_file << 6 << std::endl;
    test_file << "Иванов А.И." << std::endl;
    test_file << "1 7.5" << std::endl;
    test_file << "Белуга В.В." << std::endl;
    test_file << "2 8.0" << std::endl;
    test_file << "Мирин С.С." << std::endl;
    test_file << "1 6.8" << std::endl;
    test_file << "Савельев Д.А." << std::endl;
    test_file << "3 9.2" << std::endl;
    test_file << "Попов Е.Л." << std::endl;
    test_file << "2 7.9" << std::endl;
    test_file << "Алексеев Р.М." << std::endl;
    test_file << "3 8.5" << std::endl;
    test_file.close();

    int32_t count = 0;
    Student* students = loadStudents("s.txt", count);

    if (!students) {
        return 1;
    }

    menu(students, count); // Запускаем меню

    delete[] students;
    return 0;
}