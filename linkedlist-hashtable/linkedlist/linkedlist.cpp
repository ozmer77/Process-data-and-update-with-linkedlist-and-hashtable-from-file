#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>

class Student {
public:
    std::string name;
    int studentID;

    Student(const std::string& name, int studentID) : name(name), studentID(studentID) {}
    Student(){}
};


struct Node {
    Student data;
    Node* next;
    Node(Student student) : data(student), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(const Student& student) {
        Node* newNode = new Node(student);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

};

class HashTable {
private:
    std::unordered_map<int, Student> table;

public:
    void insert(int key, const Student& student) {
        table[key] = student;
    }
    void remove(int key) {
        table.erase(key);
    }
   
};

void readFromFile(const std::string& filename, LinkedList& list, HashTable& table) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    std::string name;
    int id;

    while (file >> name >> id) {
        Student student(name, id);
            list.append(student);
            table.remove(id);
            
        
    }

    file.close();
}

bool findRecordById(const std:: string& filename, int searchId) {
    std::ifstream file(filename);
    if (!file.is_open()) {
       std:: cerr << "Dosya açılamadı!" << std::endl;
        return false;
    }

    std::string line;
    std::string name;
    int id;
    bool found = false;

    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> name >> id) {
            if (id == searchId) {
                std::cout << "Bulunan isim" << std::endl;
                std::cout << "İsim: " << name << " ID: " << id << std::endl;
                found = true;
                break;
            }
        }
    }

    file.close();
    return found;
}


void updateOrRemoveStudents(const std::string& filename, int searchId, const std::string& newName = "", bool remove = false) {
    std::ifstream File(filename);
    std::vector<Student> students;
    Student student;
    std::string name;
    int id;

    if (!File.is_open()) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    while (File >> name >> id) {
        if (id == searchId) {
            if (remove) {
               
                continue;
            }
            if (!newName.empty()) {
                
                name = newName;
            }
        }
        students.push_back(Student(name, id));
    }

    File.close();

    
    std::ofstream outFile("students.txt");
    if (!outFile.is_open()) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    for (const auto& s : students) {
        outFile << s.name << " " << s.studentID << std::endl;
    }

    outFile.close();
}






void writeToFile(const std::string& filename, const LinkedList& list, const HashTable& table) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    Node* temp = list.head;
    while (temp) {
        file << temp->data.name << " " << temp->data.studentID << std::endl;
        temp = temp->next;
    }

    file.close();
}

void addStudent(LinkedList& list, HashTable& table, const std::string& name, int id) {
    Student newStudent(name, id);
    list.append(newStudent);
    table.insert(id, newStudent);
}


void printStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Dosya açılamadı!" << std::endl;
        return;
    }

    std::string name;
    int id;

    while (file >> name >> id) {
        std::cout << "isim: " << name << ", ID: " << id << std::endl;
    }

    file.close();
}

int main() {
    LinkedList list;
    HashTable table;
    
    addStudent(list, table, "omer", 7);
  
    updateOrRemoveStudents("students.txt", 10, "mertens", false);
    updateOrRemoveStudents("students.txt", 7, "kerem", false);
    
    
    readFromFile("students.txt", list, table);
    printStudentsFromFile("students.txt");

    writeToFile("students.txt", list, table);

    return 0;
}
