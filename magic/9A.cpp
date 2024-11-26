#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
    float ratio;  // Value-to-weight ratio
};

// Function to calculate the value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;  // Sort in decreasing order of ratio
}

// Function to calculate the maximum value we can obtain
float fractionalKnapsack(int capacity, vector<Item>& items, int n) {
    // Sort items by their value-to-weight ratio in descending order
    for (int i = 0; i < n; ++i) {
        items[i].ratio = (float)items[i].value / items[i].weight;
    }
    
    sort(items.begin(), items.end(), compare);
    
    float totalValue = 0.0;  // Variable to store total value
    int currentWeight = 0;   // Variable to track the current weight of knapsack
    
    // Greedily pick items
    for (int i = 0; i < n; ++i) {
        if (currentWeight + items[i].weight <= capacity) {
            // If the entire item can be picked
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            // Pick the fraction of the item that fits
            int remainingWeight = capacity - currentWeight;
            totalValue += items[i].value * ((float)remainingWeight / items[i].weight);
            break;
        }
    }
    
    return totalValue;  // Return the total value
}

int main() {
    int n;  // Number of items
    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items(n);  // Vector to store the items

    // Input the items' details
    cout << "Enter the details of each item (weight and value):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << " (Weight Value): ";
        cin >> items[i].weight >> items[i].value;
    }

    int capacity;  // Knapsack capacity
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display Items\n";
        cout << "2. Calculate Maximum Value in Fractional Knapsack\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nItems List:\n";
                cout << "Item   Weight   Value   Value-to-Weight Ratio\n";
                for (int i = 0; i < n; ++i) {
                    cout << items[i].weight << "     " << items[i].value << "      " 
                         << (float)items[i].value / items[i].weight << endl;
                }
                break;
            case 2:
                {
                    float maxValue = fractionalKnapsack(capacity, items, n);
                    cout << "The maximum value in the knapsack is: " << maxValue << endl;
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

