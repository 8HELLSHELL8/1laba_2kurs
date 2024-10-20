#pragma once
#include "library.h"

struct Stack 
{
private:
    struct Node 
    {
        string person;
        Node* next;

        Node(string person) : person(person), next(nullptr) {}
    };

    Node* head;

public:
    Stack() : head(nullptr) {}    

    ~Stack() 
    {
        while (head != nullptr) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }                           

    bool is_empty()
    {
        return head == nullptr;
    }                  

    void push(string name) 
    {
        Node* new_node = new Node(name);
        new_node->next = head;
        head = new_node;
    }  

    void pop() 
    {
        if (is_empty()) 
        {
            throw runtime_error("Stack is empty");
        }
        else 
        {
            Node* new_head = head->next;
            delete head;
            head = new_head;
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

    void load_from_file(const string& filename)
    {
        ifstream file(filename);
        if (file.is_open()) 
        {
            string line;
            while (getline(file, line)) 
            {
                if (!line.empty()) 
                {
                    push(line);
                }
            }
            file.close();
        } 
        else 
        {
            cerr << "Error opening the file for reading. \n";
        }
    }

    void save_to_file(const string& filename, bool overwrite) const 
    {
        ios_base::openmode mode = overwrite ? ios::trunc : ios::app;
        ofstream file(filename, mode);  
        if (!file) 
        {
            cerr << "Error opening a file for writing: " << filename << endl; 
            return; 
        }

        Node* current = head;
        while (current != nullptr) 
        {
            file << current->person << "\n"; 
            current = current->next;
        }
        file.close();
    }
};