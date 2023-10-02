#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Contact {

public:

    string name;
    string homePhone;
    string workPhone;
    string cellPhone;
    string info;

    Contact() {

    }
  
    Contact(const string& name, const string& homePhone, const string& workPhone, const string& cellPhone, const string& info) : name(name), homePhone(homePhone), workPhone(workPhone), cellPhone(cellPhone), info(info) {

    }

    inline void print() {
        cout << name << "\n";
        cout << "Home phone: " << name << "\n";
        cout << "Work phone: " << name << "\n";
        cout << "Mobile phone: " << name << "\n";
        cout << "Info: " << name << "\n";
    }

    ~Contact() {

    }
};

class PhoneBook {

private:

    vector<Contact> contacts;

public:

    void add(const Contact& contact) {
        contacts.push_back(contact);
    }

    void remove(int i) {
        contacts.erase(contacts.begin() + i);
    }

    void searchByName(string name) {
        for (int i = 0; i < contacts.size(); i++)
        {
            if (contacts[i].name.compare(name) == 0) {
                contacts[i].print();
            }
        }
    }

    void printAll() {
        for (size_t i = 0; i < contacts.size(); i++) {
            cout << "\n" << i << ") ";
            contacts[i].print();
        }
    } 
    
    void save(const string &filename) {
        ofstream file(filename);
        for (const auto& contact : contacts) {
            file << contact.name << '\n'
                << contact.homePhone << '\n'
                << contact.workPhone << '\n'
                << contact.cellPhone << '\n'
                << contact.info << '\n';
        }
        file.close();
    }
      
    void load(const string &filename) {
        ifstream file(filename);
        string name, homePhone, workPhone, cellPhone, info;

        while (getline(file, name)) {
            getline(file, homePhone);
            getline(file, workPhone);
            getline(file, cellPhone);
            getline(file, info);
            add(Contact(name, homePhone, workPhone, cellPhone, info));
        }
        file.close();
    }
};

int main()
{
    PhoneBook book;
    string name, homePhone, workPhone, cellPhone, info, query;
    string filename = "phonebook.txt";
    char loadChoice;
    int choice = 0; 
    bool stop = 0;

    cout << "Load previous phonebook? (Y / N) ";
    cin >> loadChoice;
    switch (loadChoice)
    {
    case 'y':
    case 'Y':
        book.load(filename);
        break;
    case 'n':
    case 'N':
        cout << "Phonebook not loaded";
        break;
    default:
        cout << "Wrong input";
        break;
    }

    while (!stop)
    {
        cout << "\n1) Print phonebook\n2) Add\n3) Remove\n4) Find\n5) Save\n0) Exit\n";
        cin >> choice;
        std::cin.ignore();
        switch (choice)
        {
        case 1:
            book.printAll();
            break;
        case 2:
            cout << "Name: ";
            getline(cin, name);
            cout << "Home phone: ";
            getline(cin, homePhone);
            cout << "Work phone: ";
            getline(cin, workPhone);
            cout << "Cell phone: ";
            getline(cin, cellPhone);
            cout << "Info: ";
            getline(cin, info);
            book.add(Contact(name, homePhone, workPhone, cellPhone, info));
            break;
        case 3:
            int removal;
            book.printAll();
            cout << "Which contact to remove? (0-X)\n";
            cin >> removal;
            book.remove(removal);
            break;
        case 4:
            cout << "Enter a name: ";
            getline(cin, query);
            book.searchByName(query);
            break;
        case 5:
            book.save(filename);
            cout << "Saved successfully\n";
            break;
        case 0:
            stop = 1;
            break;
        default:
            cout << "Wrong input";
            break;
        }
    }
}
