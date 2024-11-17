#include <iostream>
#include <string>
using namespace std;

struct Person
{
    string password, username;
    int step;
} person;
Person *table[26];

int hashFunction(Person person)
{
    return tolower(person.username[0]) - 97;
}

void make_table()
{
    for (int i = 0; i < 26; i++)
    {
        table[i] = NULL;
    }
}

void print_table()
{
    for (int i = 0; i < 26; i++)
    {
        if (table[i] == NULL)
        {
            cout << i << ".\t---\n";
        }
        else if (table[i] != NULL)
        {
            cout << i << ".\t" << table[i]->username << endl;
        }
    }
    cout << endl;

}

void insert(Person *person)
{
    if (person == NULL)
        return;
    int index = hashFunction(*person);
    person->step = 1;
    while (table[index] != NULL)//linear probing
    {
        person->step++;
        index++;
    }

    if (index > 26)
    {
        cout << "Index full!\n";
        return;
    }
    else
    {
        table[index] = person;
        cout << "insert success\n\n";
        return;
    }
}

int search(string search)
{

    int index = tolower(search[0]) - 97;
    if (table[index] != NULL)
    {
        cari:
        if (table[index]->username == search)
        {
            cout << "Data founded in index " << index << " and the password is " << table[index]->password 
                 << " with " << table[index]->step << " step." << endl;
            return index;
        }else{
            if (index<26)
            {
                index++; // linear probing
                goto cari;
            }
            return -1;
        }
    }
    cout << "Data not Found\n";
    return -1;
}

void deletee(string username)
{
    int index_to_delete = search(username);
    if (table[index_to_delete] == NULL)
    {
        cout << "data not found\n";
        return;
    }
    table[index_to_delete] = NULL;
    cout << "succes to delete\n";
}

main()
{
    Person gatot, gatot2;
    gatot.password = "gatot123";
    gatot.username = "gatot";

    gatot2.password = "gatot231";
    gatot2.username = "gatot2";

    make_table();
    print_table();
    insert(&gatot);
    print_table();
    insert(&gatot2);
    print_table();
    search("gatot");

}