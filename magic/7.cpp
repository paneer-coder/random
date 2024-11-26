#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <limits.h>
using namespace std;

// Define the maximum size of the hash table
#define TABLE_SIZE 10

// Structure to represent a client entry
struct Client {
    string name;
    string phoneNumber;
};

// Hash Table class with two collision resolution techniques
class TelephoneBook {
private:
    vector<Client*> table;  // Hash table (for Linear Probing)
    vector<list<Client>> chainTable;  // Hash table (for Chaining)
    
public:
    TelephoneBook() {
        table.resize(TABLE_SIZE, nullptr);
        chainTable.resize(TABLE_SIZE);
    }

    // Hash function to map a name to a hash value
    int hashFunction(const string& name) {
        int hashValue = 0;
        for (char ch : name) {
            hashValue += ch;
        }
        return hashValue % TABLE_SIZE;
    }

    // Insertion using Linear Probing
    void insertLinearProbing(const string& name, const string& phoneNumber) {
        int index = hashFunction(name);
        int comparisons = 0;
        
        // Linear probing to handle collisions
        while (table[index] != nullptr) {
            comparisons++;
            if (table[index]->name == name) {
                table[index]->phoneNumber = phoneNumber;  // Update existing entry
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        }
        
        table[index] = new Client{name, phoneNumber};
        comparisons++;
        cout << "Comparisons (Linear Probing): " << comparisons << endl;
    }

    // Insertion using Chaining
    void insertChaining(const string& name, const string& phoneNumber) {
        int index = hashFunction(name);
        int comparisons = 0;
        
        // Check if the client already exists in the list at the given index
        for (auto& client : chainTable[index]) {
            comparisons++;
            if (client.name == name) {
                client.phoneNumber = phoneNumber;  // Update existing entry
                cout << "Comparisons (Chaining): " << comparisons << endl;
                return;
            }
        }
        
        // If not found, insert at the head of the list
        chainTable[index].push_back(Client{name, phoneNumber});
        comparisons++;
        cout << "Comparisons (Chaining): " << comparisons << endl;
    }

    // Search using Linear Probing
    string searchLinearProbing(const string& name) {
        int index = hashFunction(name);
        int comparisons = 0;

        while (table[index] != nullptr) {
            comparisons++;
            if (table[index]->name == name) {
                cout << "Comparisons (Linear Probing): " << comparisons << endl;
                return table[index]->phoneNumber;
            }
            index = (index + 1) % TABLE_SIZE;
        }

        cout << "Comparisons (Linear Probing): " << comparisons << endl;
        return "Not Found";
    }

    // Search using Chaining
    string searchChaining(const string& name) {
        int index = hashFunction(name);
        int comparisons = 0;

        for (auto& client : chainTable[index]) {
            comparisons++;
            if (client.name == name) {
                cout << "Comparisons (Chaining): " << comparisons << endl;
                return client.phoneNumber;
            }
        }

        cout << "Comparisons (Chaining): " << comparisons << endl;
        return "Not Found";
    }

    // Display the telephone book (for both methods)
    void display() {
        cout << "\nDisplaying Telephone Book (Chaining method):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Index " << i << ": ";
            for (auto& client : chainTable[i]) {
                cout << "(" << client.name << ", " << client.phoneNumber << ") ";
            }
            cout << endl;
        }
    }
};

// Menu-driven interface to interact with the user
int main() {
    TelephoneBook book;
    int choice;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Client (Linear Probing)\n";
        cout << "2. Insert Client (Chaining)\n";
        cout << "3. Search Client (Linear Probing)\n";
        cout << "4. Search Client (Chaining)\n";
        cout << "5. Display Telephone Book (Chaining)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name, phoneNumber;

        switch (choice) {
            case 1:
                cout << "Enter client name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phoneNumber;
                book.insertLinearProbing(name, phoneNumber);
                break;
            case 2:
                cout << "Enter client name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phoneNumber;
                book.insertChaining(name, phoneNumber);
                break;
            case 3:
                cout << "Enter client name to search: ";
                cin >> name;
                cout << "Phone Number: " << book.searchLinearProbing(name) << endl;
                break;
            case 4:
                cout << "Enter client name to search: ";
                cin >> name;
                cout << "Phone Number: " << book.searchChaining(name) << endl;
                break;
            case 5:
                book.display();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}

