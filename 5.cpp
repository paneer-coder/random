#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

#define MAX_CITIES 10
#define INF INT_MAX

// Dijkstra's algorithm to find the shortest path
void dijkstra(int graph[MAX_CITIES][MAX_CITIES], int n, int source, int destination) {
    vector<int> dist(n, INF);  // Initialize distances as infinite
    vector<bool> visited(n, false);  // Keep track of visited nodes
    vector<int> prev(n, -1);  // Store previous node for path reconstruction
    dist[source] = 0;  // Distance to source is 0
    
    // Priority queue to select the node with the minimum distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});  // Push the source node with distance 0
    
    while (!pq.empty()) {
        int u = pq.top().second;  // Node with the smallest distance
        pq.pop();
        
        if (visited[u]) continue;  // Skip if already visited
        visited[u] = true;
        
        // Update distances for neighbors
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF) {
                int alt = dist[u] + graph[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    
    // Print the shortest path from source to destination
    if (dist[destination] == INF) {
        cout << "No path exists from source to destination.\n";
    } else {
        cout << "Shortest time to reach destination: " << dist[destination] << " units\n";
        
        // Reconstruct and print the path
        cout << "Path: ";
        vector<int> path;
        for (int at = destination; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}

// Menu-driven interface for the user
int main() {
    int n, source, destination;
    int graph[MAX_CITIES][MAX_CITIES];
    
    // Initialize the graph with no paths (infinite distances)
    cout << "Enter number of cities (max 10): ";
    cin >> n;

    // Initialize the graph with infinity (no path between cities)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;  // Distance from a city to itself is 0
            } else {
                graph[i][j] = INF;  // No direct path initially
            }
        }
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add a road between two cities\n";
        cout << "2. Calculate shortest path from Source to Destination\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int city1, city2, time;
                cout << "Enter the two cities (0 to " << n-1 << "): ";
                cin >> city1 >> city2;
                cout << "Enter the travel time from city " << city1 << " to city " << city2 << ": ";
                cin >> time;
                // Add the road to the graph (assuming bidirectional travel)
                graph[city1][city2] = time;
                graph[city2][city1] = time;
                break;
            }
            case 2: {
                cout << "Enter the source city (0 to " << n-1 << "): ";
                cin >> source;
                cout << "Enter the destination city (0 to " << n-1 << "): ";
                cin >> destination;
                
                // Call Dijkstra to calculate the shortest path
                dijkstra(graph, n, source, destination);
                break;
            }            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }} while (choice != 3);

    return 0;
}
