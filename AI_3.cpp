#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Define a pair for the Priority Queue: {distance, vertex}
typedef pair<int, int> pii;

class Graph {
private:
    int V; // Number of vertices
    // Adjacency list: vector of pairs {neighbor, weight}
    vector<vector<pii>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Function to add a directed edge with a weight
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        // Note: For an undirected graph, uncomment the line below:
        // adj[v].push_back(make_pair(u, weight));
    }

    // Dijkstra's Single-Source Shortest Path Algorithm
    void dijkstra(int src) {
        // Priority queue to store {distance, vertex}. 
        // greater<pii> turns it into a Min-Heap.
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        // Vector for distances, initialized to INFINITY
        vector<int> dist(V, INT_MAX);

        // Insert source itself into priority queue and initialize its distance to 0
        pq.push(make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty()) {
            // The first element in pair is distance, the second is vertex
            int u = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            // Optimization: If we found a shorter path to 'u' before extracting it, skip
            if (currentDist > dist[u]) continue;

            // Get all adjacent vertices of the dequeued vertex u
            for (auto edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                // If there is a shorter path to v through u
                if (dist[u] + weight < dist[v]) {
                    // Update distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        // Print shortest distances stored in dist[]
        cout << "\n--- [ DIJKSTRA'S ALGORITHM RESULTS ] ---\n";
        cout << "Source Node: " << src << "\n";
        cout << "----------------------------------------\n";
        cout << "Vertex\t\tShortest Distance from Source\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INT_MAX) {
                cout << i << "\t\t" << "Unreachable" << "\n";
            } else {
                cout << i << "\t\t" << dist[i] << "\n";
            }
        }
        cout << "----------------------------------------\n";
    }
};

int main() {
    int vertices, edges;
    
    cout << "===========================================\n";
    cout << "   SINGLE-SOURCE SHORTEST PATH (DIJKSTRA)  \n";
    cout << "===========================================\n";

    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (format: Source Destination Weight):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int sourceNode;
    cout << "\nEnter the source vertex: ";
    cin >> sourceNode;

    // Execute Dijkstra's Algorithm
    g.dijkstra(sourceNode);

    return 0;

}