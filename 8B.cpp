#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to represent a student
struct Student
{
    string name;
    int credits;
};

// Function to perform quick sort on the array of students based on credits
int partition(vector<Student> &students, int low, int high)
{
    int pivot = students[high].credits; // Taking the last element as pivot
    int i = low - 1;                    // Index of smaller element

    // Rearranging the students based on their credits
    for (int j = low; j < high; j++)
    {
        if (students[j].credits >= pivot)
        { // For descending order
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]); // Move pivot to the correct position
    return (i + 1);
}

void quickSort(vector<Student> &students, int low, int high)
{
    if (low < high)
    {
        int pi = partition(students, low, high); // Partition index
        quickSort(students, low, pi - 1);        // Sorting left part
        quickSort(students, pi + 1, high);       // Sorting right part
    }
}

int main()
{
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<Student> students(n); // Vector to store students

    // Input student names and credits
    cout << "Enter the details of students (Name, Credits):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Student " << i + 1 << " (Name Credits): ";
        cin >> students[i].name >> students[i].credits;
    }

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Display All Students\n";
        cout << "2. Display Top 3 Students\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nAll Students:\n";
            for (const auto &student : students)
            {
                cout << "Name: " << student.name << ", Credits: " << student.credits << endl;
            }
            break;
        case 2:
            quickSort(students, 0, n - 1); // Sorting students by credits
            cout << "\nTop 3 Students by Credits:\n";
            for (int i = 0; i < 3 && i < n; ++i)
            {
                cout << "Name: " << students[i].name << ", Credits: " << students[i].credits << endl;
            }
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}


