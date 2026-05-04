#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int V; 
    vector<vector<int>> adj; 

    void DFSUtil(int v, vector<bool>& visited, vector<int>& path) {
        visited[v] = true;
        path.push_back(v);
        cout << " -> Visited Node: " << v << "\n"; 

        for (int i = 0; i < adj[v].size(); ++i) {
            int neighbor = adj[v][i];
            if (!visited[neighbor]) {
                cout << "    (Going deep from Node " << v << " to Node " << neighbor << ")\n";
                DFSUtil(neighbor, visited, path);
            }
        }
    }

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V + 1); 
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    void BFS(int startVertex) {
        vector<bool> visited(V + 1, false);
        queue<int> q;
        vector<int> path;

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "\n--- [ BFS Traversal Process (Iterative) ] ---\n";
        cout << "Starting BFS at Root Node: " << startVertex << "\n";

        while (!q.empty()) {
            int current = q.front();
            path.push_back(current);
            cout << " -> Visited Node: " << current << "\n";
            q.pop();

            for (int i = 0; i < adj[current].size(); ++i) {
                int neighbor = adj[current][i];
                if (!visited[neighbor]) {
                    cout << "    (Found unvisited neighbor: Node " << neighbor << ", adding to queue)\n";
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        cout << "\nFINAL BFS PATH: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << "\n--- [ BFS Complete ] ---\n";
    }

    void DFS(int startVertex) {
        vector<bool> visited(V + 1, false);
        vector<int> path;
        
        cout << "\n--- [ DFS Traversal Process (Recursive) ] ---\n";
        cout << "Starting DFS at Root Node: " << startVertex << "\n";
        
        DFSUtil(startVertex, visited, path);
        
        cout << "\nFINAL DFS PATH: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << "\n--- [ DFS Complete ] ---\n";
    }
};

int main() {
    int vertices, edges;
    cout << "       GRAPH TRAVERSAL (BFS & DFS)         \n";
    
    
    cout << "Enter the total number of vertices: ";
    cin >> vertices;
    
    Graph g(vertices);

    cout << "Enter the total number of edges: ";
    cin >> edges;

    cout << "Enter the edges (Format: Source Destination):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int choice, startNode;
    
    do {
        cout << "\n================== MENU ==================\n";
        cout << "1. Perform Breadth First Search (BFS)\n";
        cout << "2. Perform Depth First Search (DFS) (Recursive)\n";
        cout << "3. Exit\n";
        cout << "==========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter starting vertex for BFS: ";
                cin >> startNode;
                if(startNode >= 0 && startNode <= vertices) {
                    g.BFS(startNode);
                } else {
                    cout << "Invalid vertex! Please enter a node between 0 and " << vertices << ".\n";
                }
                break;
                
            case 2:
                cout << "\nEnter starting vertex for DFS: ";
                cin >> startNode;
                if(startNode >= 0 && startNode <= vertices) {
                    g.DFS(startNode);
                } else {
                    cout << "Invalid vertex! Please enter a node between 0 and " << vertices << ".\n";
                }
                break;
                
            case 3:
                cout << "Exiting program...\n";
                break;
                
            default:
                cout << "Invalid choice! Please select 1, 2, or 3.\n";
        }
    } while (choice != 3);

    return 0;
}