#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // для форматованого виводу
using namespace std;

// Структура для збереження даних студента
struct Student {
    string group;
    string surname;
    int course;
    double averageMark;
};

// Структура для факультету, який має студентів
struct Faculty {
    string name;
    vector<Student> students;
};

// Функція для запису даних до файлу
void WriteToFile(const string& filename, const vector<Faculty>& faculties) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    size_t facultyCount = faculties.size();
    fout.write(reinterpret_cast<const char*>(&facultyCount), sizeof(facultyCount));

    for (const Faculty& faculty : faculties) {
        size_t nameLength = faculty.name.size();
        fout.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        fout.write(faculty.name.c_str(), nameLength);

        size_t studentCount = faculty.students.size();
        fout.write(reinterpret_cast<const char*>(&studentCount), sizeof(studentCount));

        for (const Student& student : faculty.students) {
            size_t groupLength = student.group.size();
            fout.write(reinterpret_cast<const char*>(&groupLength), sizeof(groupLength));
            fout.write(student.group.c_str(), groupLength);

            size_t surnameLength = student.surname.size();
            fout.write(reinterpret_cast<const char*>(&surnameLength), sizeof(surnameLength));
            fout.write(student.surname.c_str(), surnameLength);

            fout.write(reinterpret_cast<const char*>(&student.course), sizeof(student.course));
            fout.write(reinterpret_cast<const char*>(&student.averageMark), sizeof(student.averageMark));
        }
    }

    fout.close();
    cout << "Data successfully written to the file." << endl;
}

// Функція для читання даних з файлу
vector<Faculty> ReadFromFile(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error: Could not open file for reading." << endl;
        return {};
    }

    vector<Faculty> faculties;
    size_t facultyCount;
    fin.read(reinterpret_cast<char*>(&facultyCount), sizeof(facultyCount));

    for (size_t i = 0; i < facultyCount; ++i) {
        Faculty faculty;

        size_t nameLength;
        fin.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        faculty.name.resize(nameLength);
        fin.read(&faculty.name[0], nameLength);

        size_t studentCount;
        fin.read(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));

        for (size_t j = 0; j < studentCount; ++j) {
            Student student;

            size_t groupLength;
            fin.read(reinterpret_cast<char*>(&groupLength), sizeof(groupLength));
            student.group.resize(groupLength);
            fin.read(&student.group[0], groupLength);

            size_t surnameLength;
            fin.read(reinterpret_cast<char*>(&surnameLength), sizeof(surnameLength));
            student.surname.resize(surnameLength);
            fin.read(&student.surname[0], surnameLength);

            fin.read(reinterpret_cast<char*>(&student.course), sizeof(student.course));
            fin.read(reinterpret_cast<char*>(&student.averageMark), sizeof(student.averageMark));

            faculty.students.push_back(student);
        }

        faculties.push_back(faculty);
    }

    fin.close();
    return faculties;
}

// Функція для виведення даних
void PrintData(const vector<Faculty>& faculties) {
    if (faculties.empty()) {
        cout << "No data to display." << endl;
        return;
    }

    for (const Faculty& faculty : faculties) {
        cout << "Faculty: " << faculty.name << endl;
        for (const Student& student : faculty.students) {
            cout << "  Group: " << student.group
                << ", Surname: " << student.surname
                << ", Course: " << student.course
                << ", Average Mark: " << fixed << setprecision(2) << student.averageMark
                << endl;
        }
    }
}

// Функція для доповнення файлу
void AppendToFile(const string& filename) {
    vector<Faculty> faculties = ReadFromFile(filename);

    int newFacultyCount;
    cout << "Enter the number of faculties to add: ";
    cin >> newFacultyCount;

    for (int i = 0; i < newFacultyCount; ++i) {
        Faculty newFaculty;
        cout << "Enter faculty name: ";
        cin.ignore();
        getline(cin, newFaculty.name);

        int studentCount;
        cout << "Enter the number of students: ";
        cin >> studentCount;

        for (int j = 0; j < studentCount; ++j) {
            Student newStudent;
            cout << "Enter student " << j + 1 << ":" << endl;
            cout << "  Group: ";
            cin >> newStudent.group;
            cout << "  Surname: ";
            cin >> newStudent.surname;
            cout << "  Course: ";
            cin >> newStudent.course;
            cout << "  Average mark: ";
            cin >> newStudent.averageMark;

            newFaculty.students.push_back(newStudent);
        }

        faculties.push_back(newFaculty);
    }

    WriteToFile(filename, faculties);
}

// Меню програми
void Menu() {
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Write data to the file\n";
        cout << "2. Read data from the file\n";
        cout << "3. Append data to the file\n";
        cout << "4. Exit\n";
        cout << "Choose an action: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            vector<Faculty> faculties;
            int facultyCount;
            cout << "Enter the number of faculties: ";
            cin >> facultyCount;

            for (int i = 0; i < facultyCount; ++i) {
                Faculty faculty;
                cout << "Enter faculty name: ";
                cin.ignore();
                getline(cin, faculty.name);

                int studentCount;
                cout << "Enter the number of students: ";
                cin >> studentCount;

                for (int j = 0; j < studentCount; ++j) {
                    Student student;
                    cout << "Enter student " << j + 1 << ":" << endl;
                    cout << "  Group: ";
                    cin >> student.group;
                    cout << "  Surname: ";
                    cin >> student.surname;
                    cout << "  Course: ";
                    cin >> student.course;
                    cout << "  Average mark: ";
                    cin >> student.averageMark;

                    faculty.students.push_back(student);
                }

                faculties.push_back(faculty);
            }

            WriteToFile(filename, faculties);
        }
        else if (choice == 2) {
            vector<Faculty> faculties = ReadFromFile(filename);
            PrintData(faculties);
        }
        else if (choice == 3) {
            AppendToFile(filename);
        }
        else if (choice == 4) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    Menu();
    return 0;
}
