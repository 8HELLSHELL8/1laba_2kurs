#include "Array.h"
#include "ForwardList.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "Hash.h"
#include "Tree.h"

struct user_command
{
    string command;
    string name_structure;
    string value_fir = "null";
    string value_sec = "null";
};

struct data_structure 
{
    string values[100];
    int count;
};

void read_file(const string& filename, data_structure* ds)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Could not open the file\n";
        return;
    }
    
    string line;
    ds -> count = 0;
    while(getline(file, line) && ds -> count < 100)
    {
        ds -> values[ds -> count] = line;
        ds -> count++;
    }
    file.close();
}

void parse_command(const string& query, user_command* cmd)
{
    string current = query;
    size_t pos = current.find(" ");
    if(pos != string::npos)
    {
        cmd->command = current.substr(0, pos);
        current = current.substr(pos + 1);
        pos = current.find(" ");
        if(pos != string::npos)
        {
            cmd->name_structure = current.substr(0, pos);
            current = current.substr(pos + 1);
            pos = current.find(" ");
            if(pos != string::npos)
            {
                cmd->value_fir = current.substr(0, pos);
                current = current.substr(pos + 1);
                cmd->value_sec = current.substr(0, pos);
            }
            else
            {
                cmd -> value_fir = current;
            }
        }
        else
        {
            cmd->name_structure = current;
        }
    }
    else 
    {
        cmd->command = current;
    }
}


void process_command(const user_command& cmd, const string& name_file) 
{
    if (cmd.name_structure == "STACK") 
    {
        Stack stack;
        if (cmd.command == "SPUSH") 
        {
            stack.load_from_file(name_file);
            stack.push(cmd.value_fir);
            stack.save_to_file(name_file, true); 
        } 
        else if (cmd.command == "SPOP") 
        {
            stack.load_from_file(name_file);
            stack.pop();
            stack.save_to_file(name_file, true); 
        } 
        else if (cmd.command == "SPRINT") 
        {
            stack.load_from_file(name_file);
            stack.print();
        } 
    } 
    else if (cmd.name_structure == "QUEUE") 
    {
        QUEUE queue; 
        if (cmd.command == "QPUSH") 
        {
            queue.load_from_file(name_file);
            queue.push(cmd.value_fir);
            queue.save_to_file(name_file, true); 
        } 
        else if (cmd.command == "QPOP") 
        {
            queue.load_from_file(name_file);
            queue.pop();
            queue.save_to_file(name_file, true); 
        } 
        else if (cmd.command == "QPRINT") 
        {
            queue.load_from_file(name_file);
            queue.print();
        } 
    } 
    else if (cmd.name_structure == "MASSIVE") 
    {
        ARRAY<string> vector; 
        if (cmd.command == "MPUSH") 
        {
            vector.load_from_file(name_file);  
            if (cmd.value_sec != "null") 
            {
                int index = stoi(cmd.value_sec);  
                vector.MPUSH(cmd.value_fir, index);  
            } 
            else 
            {
                vector.MPUSH(cmd.value_fir);  
            }
            vector.save_to_file(name_file, true);  
        }
        else if (cmd.command == "MDEL") 
        {
            vector.load_from_file(name_file);    
            vector.MDEL(stoi(cmd.value_fir));    
            vector.save_to_file(name_file, true); 
        } 
        else if (cmd.command == "MGET") 
        {
            vector.load_from_file(name_file);    
            cout << vector.MGET(stoi(cmd.value_fir)) << endl; 
        } 
        else if (cmd.command == "MSET") 
        {
            vector.load_from_file(name_file);  
            int index = stoi(cmd.value_sec);  
            vector.MSET(cmd.value_fir, index); 
            vector.save_to_file(name_file, true);  
        }
        else if (cmd.command == "SIZE") 
        {
            vector.load_from_file(name_file);    
            cout << vector.size() << endl;       
        } 
        else if (cmd.command == "MPRINT") 
        {
            vector.load_from_file(name_file);    
            vector.print();                      
        }  
    }
    else if (cmd.name_structure == "FLIST") 
    {

        ForwardList flist; 
        flist.load_from_file(name_file); 
        if (cmd.command == "ADDHEAD") 
        {
            flist.addhead(cmd.value_fir); 
        } 
        else if (cmd.command == "ADDTAIL") 
        {
            flist.addtail(cmd.value_fir);  
        } 
        else if (cmd.command == "DELHEAD") 
        {
            flist.delhead();  
        } 
        else if (cmd.command == "DELTAIL") 
        {
            flist.deltail();  
        } 
        else if (cmd.command == "FREMOVE") 
        {
            flist.remove(cmd.value_fir);  
        } 
        else if (cmd.command == "FSEARCH") 
        {
            flist.search(cmd.value_fir); 
        } 
        else if (cmd.command == "FPRINT") 
        {
            flist.print();  
        }

        flist.save_to_file(name_file, true);  
    }
    else if (cmd.name_structure == "LLIST") 
    {

        LinkedList llist; 
        llist.load_from_file(name_file); 
        if (cmd.command == "LADDHEAD") 
        {
            llist.addhead(cmd.value_fir); 
        } 
        else if (cmd.command == "LADDTAIL") 
        {
            llist.addtail(cmd.value_fir);  
        } 
        else if (cmd.command == "LDELHEAD") 
        {
            llist.delhead();  
        } 
        else if (cmd.command == "LDELTAIL") 
        {
            llist.deltail();  
        } 
        else if (cmd.command == "LREMOVE") 
        {
            llist.remove(cmd.value_fir);  
        } 
        else if (cmd.command == "LSEARCH") 
        {
            llist.search(cmd.value_fir); 
        } 
        else if (cmd.command == "LPRINT") 
        {
            llist.print();  
        }

        llist.save_to_file(name_file, true); 
    }
    else if (cmd.name_structure == "HASH") 
    {
        Hashtable hashtableInstance(25);  
        if (cmd.command == "HADD") 
        {
            hashtableInstance.load_from_file(name_file);
            hashtableInstance.add(cmd.value_fir, cmd.value_sec);
            hashtableInstance.save_to_file(name_file, true); 
        } 
        else if (cmd.command == "HGET") 
        {
            hashtableInstance.load_from_file(name_file);
            try 
            {
                string value = hashtableInstance.get(cmd.value_fir);
                cout << "Value: " << value << endl;
            } 
            catch (const runtime_error& e) 
            {
                cout << "Error: " << e.what() << endl;
            }
        } 
        else if (cmd.command == "HREMOVE") 
        {
            hashtableInstance.load_from_file(name_file);
            try 
            {
                hashtableInstance.remove(cmd.value_fir);
                hashtableInstance.save_to_file(name_file, true); 
            } 
            catch (const runtime_error& e) 
            {
                cout << "Error: " << e.what() << endl;
            }
        } 
        else if (cmd.command == "HPRINT") 
        {
            hashtableInstance.load_from_file(name_file);
            hashtableInstance.print();
        } 
    }
    else if (cmd.name_structure == "TREE") 
    {
        int startingValue = 100;
        FBT treeInstance(startingValue); 

        if (cmd.command == "TADD") 
        {
            treeInstance.save_new_element_to_file(name_file, startingValue);
            treeInstance.load_from_file(name_file);
            treeInstance.Add(stoi(cmd.value_fir));
            treeInstance.save_new_element_to_file(name_file, stoi(cmd.value_fir));
        } 
        else if (cmd.command == "TPRINT") 
        {
            treeInstance.load_from_file(name_file);
            treeInstance.PrintNodes();
        } 
        else if (cmd.command == "TREEPRINT") 
        {
            treeInstance.load_from_file(name_file);
            treeInstance.PrintTree();
        } 
        else if (cmd.command == "TFIND") 
        {
            treeInstance.load_from_file(name_file);
            try 
            {
                node* foundNode = treeInstance.findPlace(stoi(cmd.value_fir));
                cout << "Node found: " << foundNode->key << endl;
            } 
            catch (const runtime_error& e) 
            {
                cout << "Error: " << e.what() << endl;
            }
        } 
        else if (cmd.command == "TFULL") 
        {
            treeInstance.load_from_file(name_file);
            bool isFull = treeInstance.isFull();
            cout << "Tree is " << (isFull ? "full" : "not full") << endl;
        }
    }   
}

int main(int argc, char *argv[])
{
    try 
    {
        string name_file = argv[2];
        string query = argv[4];

        user_command cmd;
        parse_command(query, &cmd);
        process_command(cmd, name_file);
    }
    catch (const runtime_error& e) 
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}