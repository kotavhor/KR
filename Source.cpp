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

// ������� ��� �������� ��������� �� �����
Student* loadStudents(const std::string& filename, int32_t& count) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "������ �������� �����: " << filename << std::endl;
        return nullptr;
    }

    file >> count;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    Student* students = new Student[count];
    for (int32_t i = 0; i < count; i++) {
        file.getline(students[i].surname, 50);
        if (file.fail()) { // �������� �� ������, ���� ������ ������� ������� ��� EOF
            std::cerr << "������ ������ ������� ��� �������� " << i << std::endl;
            delete[] students;
            return nullptr;
        }
        file >> students[i].group >> students[i].grade;
        if (file.fail()) { // �������� �� ������ ������ ������/������
            std::cerr << "������ ������ ������ ��� ������ ��� �������� " << students[i].surname << std::endl;
            delete[] students;
            return nullptr;
        }
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� �����
    }

    file.close();
    return students;
}

// ������� ��� ������ �������� �� ������� (students ������ const)
Student* searchBySurname(const Student* students, int32_t count, const char* surname) {
    for (int32_t i = 0; i < count; i++) {
        if (strcmp(students[i].surname, surname) == 0) {
            return const_cast<Student*>(&students[i]); // ������� const ��� �������� Student*
        }
    }
    return nullptr;
}

// ������� ��� ���������� ��������� �� �������
void sortBySurname(Student* students, int32_t count) {
    for (int32_t i = 0; i < count - 1; i++) {
        for (int32_t j = 0; j < count - 1 - i; j++) {
            if (strcmp(students[j].surname, students[j + 1].surname) > 0) {
                std::swap(students[j], students[j + 1]);
            }
        }
    }
}

// ��������������� ������� ��� ������ ������ ���������
void printStudents(const Student* students, int32_t count) {
    if (!students || count <= 0) {
        std::cout << "������ ��������� ����.\n";
        return;
    }
    std::cout << "������ ���������:\n";
    for (int32_t i = 0; i < count; ++i) {
        std::cout << "�������: " << students[i].surname
            << ", ������: " << students[i].group
            << ", ������: " << students[i].grade << std::endl;
    }
}

void menu(Student* students, int32_t count) {
    int choice;
    do {
        std::cout << "\n����:\n";
        std::cout << "1. ����������� �� �������\n";
        std::cout << "2. ����� �������� �� �������\n";
        std::cout << "0. �����\n";
        std::cout << "�������� ��������: ";
        std::cin >> choice;

        // ������� ������ �����
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            sortBySurname(students, count);
            std::cout << "���������� ���������!\n";
            printStudents(students, count); // ���������� ��������� ����������
            break;
        case 2: {
            char surname[50];
            std::cout << "������� �������: ";
            std::cin.getline(surname, 50);
            Student* found = searchBySurname(students, count, surname);
            if (found) {
                std::cout << "������ �������: " << found->surname << ", ������: "
                    << found->group << ", ������: " << found->grade << std::endl;
            }
            else {
                std::cout << "������� �� ������.\n";
            }
            break;
        }
        case 0:
            std::cout << "����� �� ���������.\n";
            break;
        default:
            std::cout << "������������ �����. ����������, ���������� �����.\n";
            break;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::ofstream test_file("s.txt");
    if (!test_file) {
        std::cerr << "�� ������� ������� �������� ���� 's.txt'.\n";
        return 1;
    }

    test_file << 6 << std::endl;
    test_file << "������ �.�." << std::endl;
    test_file << "1 7.5" << std::endl;
    test_file << "������ �.�." << std::endl;
    test_file << "2 8.0" << std::endl;
    test_file << "����� �.�." << std::endl;
    test_file << "1 6.8" << std::endl;
    test_file << "�������� �.�." << std::endl;
    test_file << "3 9.2" << std::endl;
    test_file << "����� �.�." << std::endl;
    test_file << "2 7.9" << std::endl;
    test_file << "�������� �.�." << std::endl;
    test_file << "3 8.5" << std::endl;
    test_file.close();

    int32_t count = 0;
    Student* students = loadStudents("s.txt", count);

    if (!students) {
        return 1;
    }

    menu(students, count); // ��������� ����

    delete[] students;
    return 0;
}