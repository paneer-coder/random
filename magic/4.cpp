#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include<algorithm>

using namespace std;

#define INF INT_MAX

// Structure to represent an edge
struct Edge {
    int u, v, weight;
    
    Edge(int _u, int _v, int _weight) : u(_u), v(_v), weight(_weight) {}
    
    // For sorting edges in ascending order of their weight
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

// Function to implement Prim's Algorithm to find MST and its weight
void primMST(int n, vector<vector<int>>& graph) {
    vector<int> parent(n, -1); // To store the MST
    vector<int> key(n, INF);   // Key values to pick minimum weight edge
    vector<bool> inMST(n, false); // To track which vertices are included in MST
    
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    
    key[0] = 0;  // Start from node 0 (can be any node)
    pq.push(Edge(-1, 0, 0));  // Push the starting node into the priority queue
    
    int totalWeight = 0;  // Total weight of the MST
    
    while (!pq.empty()) {
        // Get the vertex with the minimum key value
        int u = pq.top().v;
        pq.pop();
        
        if (inMST[u]) continue; // If the vertex is already in MST, skip it
        
        inMST[u] = true;  // Mark the vertex as included in MST
        totalWeight += key[u];
        
        // Traverse all neighbors of u
        for (int v = 0; v < n; ++v) {
            // If v is not in MST and the weight of the edge u-v is smaller than the current key of v
            if (!inMST[v] && graph[u][v] != INF && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                pq.push(Edge(u, v, key[v]));
            }
        }
    }
    
    // Output the total weight of the MST
    cout << "Total weight of MST: " << totalWeight << endl;
    
    // Output one specific MST (parent array contains the MST structure)
    cout << "Edges in the MST: " << endl;
    for (int i = 1; i < n; ++i) {
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
    }
}
// Function to implement Kruskal's Algorithm to find MST and its weight
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

void kruskalMST(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge e1, Edge e2) {
        return e1.weight < e2.weight;
    });
    
    vector<Edge> mst;
    int parent[n];
    fill(parent, parent + n, -1);
    
    int totalWeight = 0;
    
    for (auto& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        
        int set_u = find(parent, u);
        int set_v = find(parent, v);
        
        if (set_u != set_v) {
            mst.push_back(edge);
            totalWeight += edge.weight;
            unionSet(parent, set_u, set_v);
        }
    }
    
    // Output the total weight of the MST
    cout << "Total weight of MST: " << totalWeight << endl;
    
    // Output one specific MST (the edges included in the MST)
    cout << "Edges in the MST: " << endl;
    for (auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

// Menu-driven program
int main() {
    int n, m;
    int choice;
    
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;
    
    vector<vector<int>> graph(n, vector<int>(n, INF));
    vector<Edge> edges;
    
    // Initialize the graph
    cout << "Enter the edges (u v weight): " << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        
        graph[u][v] = w;
        graph[v][u] = w; // For undirected graph
        
        edges.push_back(Edge(u, v, w));
    }
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Find MST using Prim's Algorithm\n";
        cout << "2. Find MST using Kruskal's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                primMST(n, graph);
                break;
            case 2:
                kruskalMST(n, edges);
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);
    
    return 0;
}
