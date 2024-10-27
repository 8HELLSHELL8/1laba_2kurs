#pragma once
#include "DynamicArray.h"

struct QUEUE 
{
private:
    struct Node 
    {
        string person;
        Node* next;

        Node(string person)
        {
            this->person = person;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;

public:

    QUEUE()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~QUEUE() 
    {
        while (head != nullptr) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }                            

    bool is_empty() 
    {
        return head == nullptr;
    }    

    void push(string name) 
    {
        Node* new_node = new Node(name);

        if (is_empty()) 
        {
            head = tail = new_node;
        }
        else 
        {
            tail->next = new_node;
            tail = new_node;
        }
    }
                 
    void pop() 
    {
        if (is_empty()) 
        {
            throw runtime_error("QUEUE is empty");
        }

        Node* temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr) 
        {
            tail = nullptr;
        }
    }  

    void print() 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            cout << current->person << " ";
            current = current->next;
        }
        cout << "\n";
    }

    void save_to_file(const string& filename, const string& name_structure) const 
    {
        ifstream read_file(filename);
        DynamicArray<string> lines;  
        string line;
        bool structure_found = false;

        if (read_file.is_open()) 
        {
            while (getline(read_file, line)) 
            {
                lines.MPUSH(line);  
            }
            read_file.close();
        } 
        else 
        {
            cerr << "Error opening the file for reading.\n";
            return;
        }

        ofstream write_file(filename);
        if (!write_file.is_open())
        {
            cerr << "Error opening the file for writing.\n";
            return;
        }

        for (auto& existing_line : lines) 
        {

            if (existing_line.find(name_structure + " : ") == 0) 
            {
                structure_found = true;

                // Заменяем строку структуры новыми значениями
                write_file << name_structure << " : ";
                Node* current = head;  
                bool first = true;
                while (current != nullptr) 
                {
                    if (!first) write_file << ", ";
                    write_file << current->person;
                    first = false;
                    current = current->next;
                }
                write_file << endl;
            } 
            else 
            {
                write_file << existing_line << endl;  // Записываем остальные строки
            }
        }

        // Если структура не найдена, добавляем её в конец файла
        if (!structure_found) 
        {
            write_file << name_structure << " : ";
            Node* current = head;  // Начинаем с головы текущей очереди
            bool first = true;

            // Проверяем, если очередь пустая
            if (current == nullptr) 
            {
                cerr << "Error: the queue is empty, I can't add " << name_structure << " : \n";
            } 
            else 
            {
                while (current != nullptr) 
                {
                    if (!first) write_file << ", ";
                    write_file << current->person;
                    first = false;
                    current = current->next;
                }
                write_file << endl;
            }
        }

        write_file.close();  // Закрываем файл
    }

    void load_from_file(const string& filename, const string& name_structure) 
    {
        ifstream file(filename);
        
        if (file.is_open()) 
        {
            string line;
            bool structure_found = false;

            while (getline(file, line)) 
            {
                // Проверяем, является ли строка началом нового массива
                if (line.find(name_structure + " : ") != string::npos) 
                {
                    structure_found = true;  // Найден массив с указанным именем
                    size_t pos = line.find(':');
                    string values = line.substr(pos + 1); 
                    stringstream ss(values);
                    string value;

                    // Парсим значения, разделенные запятыми
                    while (getline(ss, value, ',')) 
                    {
                        push(value);  // Добавляем значение в очередь
                    }
                    break; 
                }
            }

            file.close();
        } 
        else 
        {
            cerr << "Error opening the file for reading.\n";
        }
    }
};