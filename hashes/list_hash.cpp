#include <iostream>
#include <cstring>
using namespace std;

struct Person
{

    char password[10];
    char username[10];
};

struct Node
{
    Person person;
    Node *next;
};

Node *table[10] = {nullptr};

int hashFunction(const char *key)
{
    int hash = 0;
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        hash = (hash + key[i]) % 10;
    }
    return hash;
}

void insert(const char username[], const char password[])
{
    int index = hashFunction(username);
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        cout << "Memory allocation failed" << endl;
        return;
    }
    strcpy(newNode->person.username, username);
    strcpy(newNode->person.password, password);
    if (table[index] != NULL)
    {
        // chaining
        Node *current = table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    else
    {
        table[index] = newNode;
    }
    newNode->next = nullptr;
}

void display()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "Index " << i << ": ";
        Node *current = table[i];
        while (current != NULL)
        {
            cout << "(" << current->person.username << ", " << current->person.password << ") -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
    cout << endl;
}

void search(const char *key)
{
    int index = hashFunction(key);
    Node *current = table[index];
    while (current != nullptr)
    {
        if (strcmp(current->person.password, key) == 0)
        {
            cout << current->person.username;
        }
        current = current->next;
    }
    return ; // Return nullptr if the key is not found
} 

    void deletee(const char *username, const char *password){

        int index_to_delete = hashFunction(username);
        Node *temp = table[index_to_delete];
        Node *prev = nullptr;

        while (temp != nullptr)
        {
            cout << "test\n";
            cout << temp->person.username << " " << temp->person.password << endl;
            if (strcmp(temp->person.username, username) == 0 && strcmp(temp->person.password, password) == 0)
            {
                if (prev == nullptr)
                {
                    table[index_to_delete] = temp->next;
                }else{
                    prev->next = temp->next;
                }
                free(temp);
            }
            prev = temp;
            temp = temp->next;

        }
        cout << "Data not found\n";

    }

    int main()
    {

        insert("Alice", "10");
        insert("Bob", "20");
        insert("Alice", "test");
        display();
        search("test");
        deletee("Alice", "test");
        display();
        return 0;
    }