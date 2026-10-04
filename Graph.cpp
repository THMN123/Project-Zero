#include "Graph.h"

using namespace std;

// Using a custom queue class for BFS locally to avoid external dependencies
class BFSQueueNode {
public:
    int data;
    BFSQueueNode* next;
    BFSQueueNode(int val) { data = val; next = nullptr; }
};

class BFSQueue {
private:
    BFSQueueNode* frontNode;
    BFSQueueNode* rearNode;
public:
    BFSQueue() { frontNode = rearNode = nullptr; }
    ~BFSQueue() { while(!isEmpty()) dequeue(); }
    void enqueue(int val) {
        BFSQueueNode* n = new BFSQueueNode(val);
        if (rearNode == nullptr) frontNode = rearNode = n;
        else { rearNode->next = n; rearNode = n; }
    }
    int dequeue() {
        if (isEmpty()) return -1;
        BFSQueueNode* temp = frontNode;
        int val = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
        return val;
    }
    bool isEmpty() const { return frontNode == nullptr; }
};


Graph::Graph(int maxV) {
    maxVertices = maxV;
    numVertices = 0;
    locations = new string[maxVertices];
    
    adjMatrix = new int*[maxVertices];
    for (int i = 0; i < maxVertices; i++) {
        adjMatrix[i] = new int[maxVertices];
        for (int j = 0; j < maxVertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    delete[] locations;
    for (int i = 0; i < maxVertices; i++) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

int Graph::getLocationIndex(string location) const {
    for (int i = 0; i < numVertices; i++) {
        if (locations[i] == location) {
            return i;
        }
    }
    return -1;
}

void Graph::addLocation(string location) {
    if (numVertices >= maxVertices) {
        cout << "Graph is full. Cannot add more locations." << endl;
        return;
    }
    if (getLocationIndex(location) == -1) {
        locations[numVertices] = location;
        numVertices++;
        cout << "Added location: " << location << endl;
    } else {
        cout << "Location already exists." << endl;
    }
}

void Graph::addConnection(string loc1, string loc2, int weight) {
    int idx1 = getLocationIndex(loc1);
    int idx2 = getLocationIndex(loc2);

    if (idx1 != -1 && idx2 != -1) {
        adjMatrix[idx1][idx2] = weight;
        adjMatrix[idx2][idx1] = weight; // Assuming undirected graph
        cout << "Connection added between " << loc1 << " and " << loc2 << endl;
    } else {
        cout << "One or both locations not found." << endl;
    }
}

void Graph::displayConnections() const {
    for (int i = 0; i < numVertices; i++) {
        cout << locations[i] << " is connected to: ";
        bool hasConnections = false;
        for (int j = 0; j < numVertices; j++) {
            if (adjMatrix[i][j] != 0) {
                cout << locations[j] << " ";
                hasConnections = true;
            }
        }
        if (!hasConnections) cout << "None";
        cout << endl;
    }
}

void Graph::BFS(string startLoc) const {
    int startIdx = getLocationIndex(startLoc);
    if (startIdx == -1) {
        cout << "Start location not found." << endl;
        return;
    }

    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) visited[i] = false;

    BFSQueue q;
    q.enqueue(startIdx);
    visited[startIdx] = true;

    cout << "BFS Traversal from " << startLoc << ": ";

    while (!q.isEmpty()) {
        int curr = q.dequeue();
        cout << locations[curr] << " ";

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[curr][i] != 0 && !visited[i]) {
                q.enqueue(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
    delete[] visited;
}

void Graph::DFS(string startLoc) const {
    int startIdx = getLocationIndex(startLoc);
    if (startIdx == -1) {
        cout << "Start location not found." << endl;
        return;
    }

    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) visited[i] = false;

    cout << "DFS Traversal from " << startLoc << ": ";
    DFSRecursive(startIdx, visited);
    cout << endl;

    delete[] visited;
}

void Graph::DFSRecursive(int vertexIdx, bool visited[]) const {
    visited[vertexIdx] = true;
    cout << locations[vertexIdx] << " ";

    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[vertexIdx][i] != 0 && !visited[i]) {
            DFSRecursive(i, visited);
        }
    }
}

// Dijkstra's Shortest Path Algorithm (O(V^2) - no STL needed)
void Graph::dijkstra(string startLoc) const {
    int startIdx = getLocationIndex(startLoc);
    if (startIdx == -1) {
        cout << "Start location not found." << endl;
        return;
    }

    int* dist = new int[numVertices];
    bool* visited = new bool[numVertices];
    int* prev = new int[numVertices];

    // A very large number to represent infinity
    int INF = 999999;

    // Initialise all distances as infinity, not visited, no previous node
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        visited[i] = false;
        prev[i] = -1;
    }
    dist[startIdx] = 0;

    // Relax edges V-1 times
    for (int count = 0; count < numVertices - 1; count++) {
        // Find the unvisited vertex with the smallest distance
        int u = -1;
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;

        // Update distances to neighbours of u
        for (int v = 0; v < numVertices; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                int newDist = dist[u] + adjMatrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }

    // Print the results
    cout << "\n--- Shortest Paths from: " << startLoc << " ---" << endl;
    for (int i = 0; i < numVertices; i++) {
        if (i == startIdx) continue;
        cout << "  To " << locations[i] << ": ";
        if (dist[i] == INF) {
            cout << "No path found.";
        } else {
            cout << "Distance = " << dist[i] << "  |  Path: ";
            // Trace back the path
            int* path = new int[numVertices];
            int pathLen = 0;
            int curr = i;
            while (curr != -1) {
                path[pathLen++] = curr;
                curr = prev[curr];
            }
            // Print path in reverse (from source to destination)
            for (int j = pathLen - 1; j >= 0; j--) {
                cout << locations[path[j]];
                if (j != 0) cout << " -> ";
            }
            delete[] path;
        }
        cout << endl;
    }

    delete[] dist;
    delete[] visited;
    delete[] prev;
}

int Graph::getNumVertices() const {
    return numVertices;
}

string Graph::getLocationName(int idx) const {
    if (idx >= 0 && idx < numVertices) return locations[idx];
    return "";
}
