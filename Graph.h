#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

using namespace std;

class Graph {
private:
    int numVertices;
    int maxVertices;
    string* locations;
    int** adjMatrix;
    
    int getLocationIndex(string location) const;

public:
    Graph(int maxV = 50);
    ~Graph();

    void addLocation(string location);
    void addConnection(string loc1, string loc2, int weight = 1);
    void displayConnections() const;

    void BFS(string startLoc) const;
    void DFS(string startLoc) const;
    void DFSRecursive(int vertexIdx, bool visited[]) const;
    void dijkstra(string startLoc) const;

    int getNumVertices() const;
    string getLocationName(int idx) const;
};

#endif // GRAPH_H
