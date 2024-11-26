#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to represent a student
struct Student {
    string name;
    int credits;
};

// Function to merge two halves of the array in sorted order
void merge(vector<Student>& students, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary vectors to store left and right subarrays
    vector<Student> leftArray(n1), rightArray(n2);

    // Copy data to temporary subarrays
    for (int i = 0; i < n1; ++i)
        leftArray[i] = students[left + i];
    for (int i = 0; i < n2; ++i)
        rightArray[i] = students[mid + 1 + i];

    // Merge the temporary subarrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].credits >= rightArray[j].credits) {
            students[k] = leftArray[i];
            ++i;
        } else {
            students[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    // Copy remaining elements of leftArray if any
    while (i < n1) {
        students[k] = leftArray[i];
        ++i;
        ++k;
    }

    // Copy remaining elements of rightArray if any
    while (j < n2) {
        students[k] = rightArray[j];
        ++j;
        ++k;
    }
}

// Merge Sort function to sort students by credits
void mergeSort(vector<Student>& students, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort(students, left, mid);
        mergeSort(students, mid + 1, right);

        // Merge the sorted halves
        merge(students, left, mid, right);
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<Student> students(n);  // Vector to store student details

    // Input student names and credits
    cout << "Enter the details of students (Name, Credits):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Student " << i + 1 << " (Name Credits): ";
        cin >> students[i].name >> students[i].credits;
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display All Students\n";
        cout << "2. Sort Students by Credits and Display\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nAll Students:\n";
                for (const auto& student : students) {
                    cout << "Name: " << student.name << ", Credits: " << student.credits << endl;
                }
                break;
            case 2:
                mergeSort(students, 0, n - 1);  // Sorting students by credits using merge sort
                cout << "\nSorted Students by Credits:\n";
                for (const auto& student : students) {
                    cout << "Name: " << student.name << ", Credits: " << student.credits << endl;
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
