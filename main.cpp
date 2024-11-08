#include <iostream>
#include <vector>

using namespace std;

vector<int> lastConnectedToRootPoints;


vector<vector<int>> createEmptyMatrix(int size) {
    return vector<vector<int>>(size, vector<int>(size, 0));
}

void addBothSidesEdgeToMatrix(vector<vector<int>>& graph, int x, int y) {
    graph[x][y] = 1;
    graph[y][x] = 1;
}

vector<vector<int>> generateBRVGraph(int iterations) {
    if (iterations == 0) {
        return createEmptyMatrix(1);
    }
    else if(iterations == 1){
        vector<vector<int>> baseGraph = createEmptyMatrix(3);
        addBothSidesEdgeToMatrix(baseGraph, 0, 1);
        addBothSidesEdgeToMatrix(baseGraph, 0, 2);
        lastConnectedToRootPoints = {1, 2};
        return baseGraph;
    }
    else{ // n = 2
        vector <int> newConnectedToRootPoints;
        int prevSize = pow(3, iterations - 1);
        int newSize = prevSize * 3;

        vector<vector<int>> prevGraph = generateBRVGraph(iterations - 1); // 9x9 {4, 5, 7, 8 }
        vector<vector<int>> newGraph = createEmptyMatrix(newSize); // 27x27

        for (int i = 0; i < prevSize; i++) { // kopiowanie grafu
            for (int j = 0; j < prevSize; j++) {
                // Pierwsza kopia w lewym górnym rogu
                newGraph[i][j] = prevGraph[i][j];

                // Druga kopia w środku
                newGraph[i + prevSize][j + prevSize] = prevGraph[i][j];

                // Trzecia kopia w prawym dolnym rogu
                newGraph[i + 2 * prevSize][j + 2 * prevSize] = prevGraph[i][j];
            }
        }

        int leftSideDistanceFromRoot = prevSize;
        for (int i = 0; i < lastConnectedToRootPoints.size(); i++)
        {
            int newPointIndex = lastConnectedToRootPoints[i] + leftSideDistanceFromRoot;
            addBothSidesEdgeToMatrix(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        int rightSideDistanceFromRoot = prevSize * 2;
        for (int i = 0; i < lastConnectedToRootPoints.size(); i++)
        {
            int newPointIndex = lastConnectedToRootPoints[i] + rightSideDistanceFromRoot;
            addBothSidesEdgeToMatrix(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        lastConnectedToRootPoints = newConnectedToRootPoints;
        return newGraph;
    }
}

void displayMatrix(const vector<vector<int>>& matrix) {
    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int calculateTotalDistance(const vector<vector<int>>& graph) {
    int totalDistance = 0;
    int n = graph.size();

    for (int start = 0; start < n; start++) {
        vector<int> distances(n, INT_MAX); // Maksymalne odległości
        distances[start] = 0; // Odległość od startowego węzła do siebie samego to 0
        queue<int> q;
        q.push(start);

        // BFS
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

        // Dodaje odległości do całkowitej sumy
        for (int i = 0; i < n; ++i) {
            if (i != start && distances[i] != INT_MAX) {
                totalDistance += distances[i];
            }
        }
    }

    return totalDistance/2;
}

int main() {
    int num_model, value;
    while(cin>>num_model>>value)
    {
        switch(num_model){
            case 0:
                vector<vector<int>> graph = generateBRVGraph(value);
//                cout << "Macierz sąsiedztwa:" << endl;
                //displayMatrix(graph);
                value = calculateTotalDistance(graph);
                cout << value<< endl;
                break;
        }
    }
    return 0;
}