#include "Graph.h"
#include <set>

vector<vector<int>> Graph::createEmptyAdjacencyList(int size) {
    return vector<vector<int>>(size, vector<int>());
}

vector<vector<int>> Graph::createEmptyMatrix(int size) {
    return vector<vector<int>>(size, vector<int>(size, 0));
}

void Graph::addBothSidesEdge(vector<vector<int>>& adjacencyList, int u, int v) {
    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);
}

void Graph::addBothSidesEdgeToMatrix(vector<vector<int>>& graph, int x, int y) {
    graph[x][y] = 1;
    graph[y][x] = 1;
}

void Graph::updateEdgeWeight(vector<vector<int>>& matrix, int a, int b, int value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

int Graph::calculateTotalDistance(const vector<vector<int>>& graph) {
    int totalDistance = 0;
    int n = graph.size();

    for (int start = 0; start < n; start++) {
        vector<int> distances(n, INT_MAX);
        distances[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : graph[node]) {
                if (distances[neighbor] == INT_MAX) {
                    distances[neighbor] = distances[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        for (int i = start + 1; i < n; ++i) {
            if (distances[i] != INT_MAX) {
                totalDistance += distances[i];
            }
        }
    }

    return totalDistance;
}

int Graph::calculateTotalDistanceMatrix(const vector<vector<int>>& graph) {
    int totalDistance = 0;
    int n = graph.size();

    for (int start = 0; start < n; start++) {
        vector<int> distances(n, INT_MAX);
        distances[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor = 0; neighbor < n; ++neighbor) {
                if (graph[node][neighbor] == 1 && distances[neighbor] == INT_MAX) {
                    distances[neighbor] = distances[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (i != start && distances[i] != INT_MAX) {
                totalDistance += distances[i];
            }
        }
    }

    return totalDistance / 2;
}

void Graph::printAdjacencyMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

void Graph::printAdjacencyList(const vector<vector<int>>& adjacencyList) {
    for (size_t i = 0; i < adjacencyList.size(); ++i) {
        cout << i << ": ";

        set<int> uniqueNeighbors(adjacencyList[i].begin(), adjacencyList[i].end()); // Usunięcie duplikatów

        for (int neighbor : uniqueNeighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}
