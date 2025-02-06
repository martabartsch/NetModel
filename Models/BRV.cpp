#include "BRV.h"

// Function to generate the Barabasi–Ravasz–Vicsek adjacency list for a given number of iterations
vector<vector<int>> BRV::generateBRVAdjacencyList(int iterations) {

    if (iterations == 0) {
        return Graph::createEmptyAdjacencyList(1);
    } else if (iterations == 1) {
        vector<vector<int>> baseGraph = Graph::createEmptyAdjacencyList(3);
        Graph::addBothSidesEdge(baseGraph, 0, 1);
        Graph::addBothSidesEdge(baseGraph, 0, 2);
        lastConnectedToRootPoints = {1, 2};  // nodes connected to the root
        return baseGraph;
    } else { // n=2
        int prevSize = 1;
        for (int i = 1; i < iterations; ++i) prevSize *= 3;
        int newSize = prevSize * 3;

        vector<vector<int>> prevGraph = generateBRVAdjacencyList(iterations - 1);
        vector<vector<int>> newGraph = Graph::createEmptyAdjacencyList(newSize);
        // copy the previous graph into three positions in the new graph
        for (int i = 0; i < prevSize; i++) { // kopiowanie grafu
            for (int neighbor : prevGraph[i]) {
                // first copy in the top-left corner
                newGraph[i].push_back(neighbor);
                // second copy in the middle
                newGraph[i + prevSize].push_back(neighbor + prevSize);
                // third copy in the bottom-right corner
                newGraph[i + 2 * prevSize].push_back(neighbor + 2 * prevSize);
            }
        }

        // connect the new graph to the root
        vector<int> newConnectedToRootPoints;
        for (int point : lastConnectedToRootPoints) {
            int newPointIndex = point + prevSize;
            Graph::addBothSidesEdge(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        for (int point : lastConnectedToRootPoints) {
            int newPointIndex = point + 2 * prevSize;
            Graph::addBothSidesEdge(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        lastConnectedToRootPoints = newConnectedToRootPoints;
        Graph::printAdjacencyList(newGraph);
        return newGraph;
    }
}

// Function to generate the Barabasi–Ravasz–Vicsek adjacency matrix for a given number of iterations
vector<vector<int>> BRV::generateBRVAdjacencyMatrix(int iterations){
    if (iterations == 0) {
        return Graph::createEmptyMatrix(1);
    }
    else if(iterations == 1){
        vector<vector<int>> baseGraph = Graph::createEmptyMatrix(3);
        Graph::addBothSidesEdgeToMatrix(baseGraph, 0, 1);
        Graph::addBothSidesEdgeToMatrix(baseGraph, 0, 2);
        lastConnectedToRootPoints = {1, 2}; // nodes connected to the root
        return baseGraph;
    }
    else{ // n = 2
        vector <int> newConnectedToRootPoints;
        int prevSize = pow(3, iterations - 1);
        int newSize = prevSize * 3;

        vector<vector<int>> prevGraph = BRV::generateBRVAdjacencyMatrix(iterations - 1);
        vector<vector<int>> newGraph = Graph::createEmptyMatrix(newSize);

        // copy the previous graph into three positions in the new graph
        for (int i = 0; i < prevSize; i++) {
            for (int j = 0; j < prevSize; j++) {
                // first copy in the top-left corner
                newGraph[i][j] = prevGraph[i][j];
                // second copy in the middle
                newGraph[i + prevSize][j + prevSize] = prevGraph[i][j];
                // third copy in the bottom-right corner
                newGraph[i + 2 * prevSize][j + 2 * prevSize] = prevGraph[i][j];
            }
        }

        // connect the new graph to the root (left side)
        int leftSideDistanceFromRoot = prevSize;
        for (int lastConnectedToRootPoint : lastConnectedToRootPoints)
        {
            int newPointIndex = lastConnectedToRootPoint + leftSideDistanceFromRoot;
            Graph::addBothSidesEdgeToMatrix(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        // connect the new graph to the root (right side)
        int rightSideDistanceFromRoot = prevSize * 2;
        for (int lastConnectedToRootPoint : lastConnectedToRootPoints)
        {
            int newPointIndex = lastConnectedToRootPoint + rightSideDistanceFromRoot;
            Graph::addBothSidesEdgeToMatrix(newGraph, 0, newPointIndex);
            newConnectedToRootPoints.push_back(newPointIndex);
        }

        lastConnectedToRootPoints = newConnectedToRootPoints;
        return newGraph;
    }
}
