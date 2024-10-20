#pragma once
#include "library.h"
// Node structure for a complete binary tree
struct node 
{
    int32_t key;
    node* leftChild;
    node* rightChild;

    node(int value) : key(value), leftChild(nullptr), rightChild(nullptr) {}
};

template <typename T>
struct Queue 
{
private:

    struct Node 
    {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:

    Queue() : head(nullptr), tail(nullptr) {}

    Queue(const Queue& other) : head(nullptr), tail(nullptr) 
    {
        Node* current = other.head;
        while (current != nullptr) 
        {
            enqueue(current->data);  // We copy the elements one by one
            current = current->next;
        }
    }

    ~Queue() 
    {
        while (head != nullptr) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool is_empty() const
    {
        return head == nullptr; 
    }

    void enqueue(T data) 
    {
        Node* new_node = new Node(data);
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

    void dequeue() 
    {
        if (is_empty()) 
        {
            throw runtime_error("Queue is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) 
        {
            tail = nullptr;
        }
    }

    T front() const 
    {
        if (is_empty()) 
        {
            throw runtime_error("Queue is empty");
        }
        return head->data;
    }
};

struct FBT 
{
private:
    node* root;
    Queue<node*> waitlist;  // Queue for adding new nodes
    Queue<node*> allNodes;  // Queue for storing all nodes

public:
    FBT(int value) 
    {
        root = new node(value);
        allNodes.enqueue(root);
        waitlist.enqueue(root);
    }

    ~FBT() 
    {
        // Freeing all nodes
        Queue<node*> tempQueue = allNodes;
        while (!tempQueue.is_empty()) 
        {
            node* currentNode = tempQueue.front();
            tempQueue.dequeue();
            delete currentNode;  // Deleting the node
        }
    }

    void Add(int value) 
    {
        if (waitlist.is_empty()) 
        {
            throw runtime_error("The parent node was not found to which a new child node can be added!!!");
        }

        node* parent = waitlist.front();  // We take the node that is in the queue
        node* newNode = new node(value);
        allNodes.enqueue(newNode);

        if (parent->leftChild == nullptr) 
        {
            parent->leftChild = newNode;
        }
        else if (parent->rightChild == nullptr) 
        {
            parent->rightChild = newNode;
            waitlist.dequeue(); // If the node has both children, we remove it from the queue
        }
        else 
        {
            throw runtime_error("Parent node already has two children.");
        }

        waitlist.enqueue(newNode);  // Adding a new node to the queue for consideration
    }

    void PrintNodes() 
    {
        Queue<node*> tempQueue = allNodes;
        while (!tempQueue.is_empty()) 
        {
            node* currentNode = tempQueue.front();
            cout << currentNode->key << " ";
            tempQueue.dequeue();
        }
        cout << "\n";
    }

    void PrintTree() 
    {
        int totalNodes = 0;  // The total number of nodes in the tree
        Queue<node*> tempQueue = allNodes;

        while (!tempQueue.is_empty()) 
        {
            tempQueue.dequeue();
            totalNodes++;
        }

        int level = 0;  // Current tree level
        int printedNodes = 0;  // The number of nodes already printed
        int maxNodesAtLevel = pow(2, floor(log2(totalNodes)) + 1);

        tempQueue = allNodes;  // Returning the queue to its original state for printing the tree

        while (printedNodes < totalNodes) 
        {
            int nodesInLevel = pow(2, level);
            level++;

            int leadingSpaces = maxNodesAtLevel / nodesInLevel - 1;
            int spacingBetweenNodes = maxNodesAtLevel / nodesInLevel - 1;
            string leadSep(leadingSpaces + 3, ' ');
            string endSep(spacingBetweenNodes, ' ');

            for (int i = 0; i < nodesInLevel && printedNodes < totalNodes; i++) 
            {
                cout << leadSep << tempQueue.front()->key << endSep;
                tempQueue.dequeue();
                printedNodes++;
            }

            cout << "\n";
        }
    }

    node* findPlace(int value) 
    {
        Queue<node*> tempQueue = allNodes;

        while (!tempQueue.is_empty()) 
        {
            node* currentNode = tempQueue.front();
            if (currentNode->key == value) 
            {
                return currentNode;
            }
            tempQueue.dequeue();
        }

        throw runtime_error("Value was not found!!!");
        return nullptr;
    }

    bool isFull() 
    {
        Queue<node*> tempQueue = allNodes;

        while (!tempQueue.is_empty()) 
        {
            node* currentNode = tempQueue.front();
            if ((currentNode->leftChild == nullptr && currentNode->rightChild != nullptr) ||
                (currentNode->leftChild != nullptr && currentNode->rightChild == nullptr)) 
            {
                return false;
            }
            tempQueue.dequeue();
        }
        return true;
    }

    string remove_spaces(const string& str) 
    {
        string result = "";
        for (size_t i = 0; i < str.length(); i++) 
        {
            if (str[i] != ' ' && str[i] != '|') 
            {
                result += str[i];
            }
        }
        return result;
    }

    void save_new_element_to_file(const string& filename, int key) const 
    {
        ofstream file(filename, ios::app);
        if (file.is_open()) 
        {
            file << "mytree:| " << key << " |\n"; 
            file.close();
        } 
        else 
        {
            cerr << "Error opening the file for writing.\n";
        }
    }

    void load_from_file(const string& filename) 
    {
        ifstream file(filename);
        if (file.is_open()) 
        {
            string line;
            while (getline(file, line)) 
            {
                if (line.empty()) continue;

                size_t pos = line.find("mytree:|"); 
                if (pos != string::npos) 
                {
                    string key_str = line.substr(pos + 8);
                    key_str = key_str.substr(0, key_str.find('|')); 
                    int key = stoi(key_str);
                    Add(key); 
                }
            }
            file.close();
        } 
        else 
        {
            cerr << "Error opening the file for writing.\n";
        }
    }
};





