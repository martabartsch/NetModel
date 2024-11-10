#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> lastConnectedToRootPoints;

vector<vector<int>> createEmptyAdjacencyList(int size) {
    return vector<vector<int>>(size, vector<int>());
}

vector<vector<int>> createEmptyMatrix(int size) {
    return vector<vector<int>>(size, vector<int>(size, 0));
}

void addBothSidesEdgeToMatrix(vector<vector<int>>& graph, int x, int y) {
    graph[x][y] = 1;
    graph[y][x] = 1;
}

void addBothSidesEdge(vector<vector<int>>& adjacencyList, int u, int v) {
    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);
}

vector<vector<int>> generateBRVAdjacencyList(int iterations) {

    if (iterations == 0) {
        return createEmptyAdjacencyList(1);
    } else if (iterations == 1) {
        vector<vector<int>> baseGraph = createEmptyAdjacencyList(3);
        addBothSidesEdge(baseGraph, 0, 1);
        addBothSidesEdge(baseGraph, 0, 2);
        lastConnectedToRootPoints = {1, 2};
        return baseGraph;
    } else {
        int prevSize = 1;
        for (int i = 1; i < iterations; ++i) prevSize *= 3;
        int newSize = prevSize * 3;

        vector<vector<int>> prevGraph = generateBRVAdjacencyList(iterations - 1);
        vector<vector<int>> newGraph = createEmptyAdjacencyList(newSize);

        // Copy previous graph into three regions of new graph
        for (int i = 0; i < prevSize; i++) {
            for (int neighbor : prevGraph[i]) {
                newGraph[i].push_back(neighbor);
                newGraph[i + prevSize].push_back(neighbor + prevSize);
                newGraph[i + 2 * prevSize].push_back(neighbor + 2 * prevSize);
            }
        }

        // Connect root points
        vector<int> newConnectedToRootPoints;
        for (int point : lastConnectedToRootPoints) {
            int newPointIndex = point + prevSize;
            addBothSidesEdge(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        for (int point : lastConnectedToRootPoints) {
            int newPointIndex = point + 2 * prevSize;
            addBothSidesEdge(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        lastConnectedToRootPoints = newConnectedToRootPoints;
        return newGraph;
    }
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

int calculateTotalDistance(const vector<vector<int>>& graph) {
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

int calculateTotalDistanceMatrix(const vector<vector<int>>& graph) {
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

void displayMatrix(const vector<vector<int>>& matrix) {
    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Print neighbor list
void printAdjacencyList(const vector<vector<int>>& adjacencyList) {
    for (size_t i = 0; i < adjacencyList.size(); ++i) {
        cout << i << ": ";
        for (int neighbor : adjacencyList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}


int main() {
    int num_model, value;
    while(cin>>num_model>>value)
    {
        switch(num_model){
            case 0: {
                vector<vector<int>> graph = generateBRVAdjacencyList(value);
                value = calculateTotalDistance(graph);
                cout << value << endl;
                break;
            }
            case 1:
                cout<<"0"<<endl;
                break;
            case 3:
                cout<<"0"<<endl;
                break;
            case 4:
                cout<<"0"<<endl;
                break;
            case 6:
                cout<<"0"<<endl;
                break;
        }
    }
    return 0;
}