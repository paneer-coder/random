#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    char id;    // Job identifier (e.g., 'A', 'B', 'C', ...)
    int deadline;
    int profit;
};

bool compareJobs(Job j1, Job j2) {
    // Sort jobs by profit in descending order
    return j1.profit > j2.profit;
}

void jobScheduling(vector<Job>& jobs, int n) {
    // Sort jobs by profit in descending order
    sort(jobs.begin(), jobs.end(), compareJobs);

    vector<bool> slots(n, false);  // Tracks which slots are occupied
    vector<char> result(n, ' ');   // Stores the result jobs
    
    int totalProfit = 0;

    // Iterate through the jobs and find a slot for each job
    for (int i = 0; i < n; ++i) {
        // Find a slot for job[i] starting from its deadline (or before)
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; --j) {
            if (!slots[j]) {
                // Slot is available, assign this job
                slots[j] = true;
                result[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Output the selected jobs and their total profit
    cout << "Selected jobs: ";
    for (int i = 0; i < n; ++i) {
        if (result[i] != ' ') {
            cout << result[i] << " ";
        }
    }
    cout << endl;
    cout << "Total profit: " << totalProfit << endl;
}

int main() {
    int n;  // Number of jobs
    cout << "Enter the number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);  // Array to store jobs

    // Input the job details
    cout << "Enter the job details (ID, Deadline, Profit):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Job " << i + 1 << " (ID Deadline Profit): ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display Job Details\n";
        cout << "2. Calculate and Display Selected Jobs\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nJob Details:\n";
                cout << "ID Deadline Profit\n";
                for (int i = 0; i < n; ++i) {
                    cout << jobs[i].id << " " << jobs[i].deadline << " " << jobs[i].profit << endl;
                }
                break;
            case 2:
                jobScheduling(jobs, n);
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
