#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<int>> DCN(int numNodes) {
    vector<vector<int>> matrix(numNodes, vector<int>(numNodes, 0));

    if (numNodes == 0) return matrix;

    // Dodajemy korzeń
    int nodesRemaining = numNodes - 1;
    int currentNode = 1;

    // Listę przodków traktujemy jako wektor, na początku tylko korzeń (0)
    vector<int> ancestors = {0};

    while (nodesRemaining > 0) {
        // Przygotowanie nowej listy przodków dla nowych węzłów
        vector<int> newAncestors;

        // Iterujemy po obecnych przodkach (korzeń + wcześniej dodane węzły)
        for (int ancestor : ancestors) {
            if (nodesRemaining <= 0) break;

            // Dodajemy dwa nowe węzły
            for (int i = 0; i < 2 && nodesRemaining > 0; ++i) {
                int newNode = currentNode++;
                nodesRemaining--;

                // Łączymy nowy węzeł z jego przodkiem (ancestor)
                matrix[ancestor][newNode] = 1;
                matrix[newNode][ancestor] = 1;

                // Łączymy nowy węzeł z wszystkimi przodkami węzła ancestor
                for (int parent : ancestors) {
                    if (parent != ancestor) { // Unikamy połączenia z samym sobą
                        matrix[parent][newNode] = 1;
                        matrix[newNode][parent] = 1;
                    }
                }

                // Przechowujemy przodków dla nowego węzła
                newAncestors.push_back(newNode);
            }
        }

        // Zaktualizowana lista przodków na następny krok
        ancestors = newAncestors;
    }

    return matrix;
}

int calculateTotalDistance(const vector<vector<int>>& graph) {
    int totalDistance = 0;
    int n = graph.size();
    for (int start = 0; start < n; start++) {
        vector<int> distances(n, INT_MAX);
        distances[start] = 0;
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
    while(cin >> num_model >> value)
    {
        switch(num_model){
            case 4:{
                vector<vector<int>> matrix = DCN(value);
                value = calculateTotalDistance(matrix);
                cout << value << endl;
                break;
            }
        }
    }

    return 0;
}
