#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <limits>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, double>>> adjList; // adjacency list

    void DFS(const string& city, unordered_map<string, bool>& visited) {
        visited[city] = true;
        for (const auto& neighbor : adjList[city]) {
            if (!visited[neighbor.first]) {
                DFS(neighbor.first, visited);
            }
        }
    }

public:
    // Add a flight (edge) between two cities (nodes)
    void addFlight(const string& cityA, const string& cityB, double cost) {
        adjList[cityA].push_back({cityB, cost});
        adjList[cityB].push_back({cityA, cost}); // Assuming undirected graph (bidirectional flight)
    }

    // Check if the graph is connected
    bool isConnected() {
        if (adjList.empty()) return true; // An empty graph is considered connected

        unordered_map<string, bool> visited;
        for (const auto& city : adjList) {
            visited[city.first] = false;
        }

        // Start DFS from the first city in the adjList
        auto startCity = adjList.begin()->first;
        DFS(startCity, visited);

        // Check if all cities are visited
        for (const auto& city : visited) {
            if (!city.second) return false;
        }
        return true;
    }

    // Display the graph (adjacency list)
    void displayGraph() {
        for (const auto& city : adjList) {
            cout << city.first << " -> ";
            for (const auto& neighbor : city.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    int choice;
    string cityA, cityB;
    double cost;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add a flight between two cities\n";
        cout << "2. Display the graph\n";
        cout << "3. Check if the graph is connected\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the source city: ";
                cin >> cityA;
                cout << "Enter the destination city: ";
                cin >> cityB;
                cout << "Enter the cost (time or fuel): ";
                cin >> cost;
                g.addFlight(cityA, cityB, cost);
                break;
            case 2:
                g.displayGraph();
                break;
            case 3:
                if (g.isConnected()) {
                    cout << "The graph is connected.\n";
                } else {
                    cout << "The graph is not connected.\n";
                }
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

