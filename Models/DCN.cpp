#include "DCN.h"

// Function to generate an adjacency list for the DCN model
vector<vector<int>> DCN::adjacencyListDCN(int numNodes) {
    vector<vector<int>> adjacencyList(numNodes);

    if (numNodes == 0) return adjacencyList;

    int nodesRemaining = numNodes - 1;
    int currentNode = 1;

    vector<int> ancestors = {0};

    while (nodesRemaining > 0) {
        vector<int> newAncestors;

        //  iterate over all current ancestors (root + previously added nodes)
        for (int ancestor : ancestors) {
            if (nodesRemaining <= 0) break;

            for (int i = 0; i < 2 && nodesRemaining > 0; ++i) {
                int newNode = currentNode++;
                nodesRemaining--;

                Graph::addBothSidesEdge(adjacencyList, ancestor, newNode);
                // connect the new node to all ancestors except the current one
                for (int parent : ancestors) {
                    // Avoid self-connections
                    if (parent != ancestor) {
                        Graph::addBothSidesEdge(adjacencyList, parent, newNode);
                    }
                }

                newAncestors.push_back(newNode);
            }
        }
        ancestors = newAncestors;
    }
    Graph::printAdjacencyList(adjacencyList);
    return adjacencyList;
}

// Function to generate an adjacency matrix for the DCN model
vector<vector<int>> DCN::adjacencyMatrixDCN(int numNodes) {
    vector<vector<int>> matrix(numNodes, vector<int>(numNodes, 0));

    if (numNodes == 0) return matrix;

    int nodesRemaining = numNodes - 1;
    int currentNode = 1;
    vector<int> ancestors = {0};

    while (nodesRemaining > 0) {
        vector<int> newAncestors;

        //  iterate over all current ancestors (root + previously added nodes)
        for (int ancestor : ancestors) {
            if (nodesRemaining <= 0) break;

            for (int i = 0; i < 2 && nodesRemaining > 0; ++i) {
                int newNode = currentNode++;
                nodesRemaining--;

                Graph::addBothSidesEdgeToMatrix(matrix, ancestor, newNode);

                // connect the new node to all ancestors except the current one
                for (int parent : ancestors) {
                    // avoid self-connections
                    if (parent != ancestor) {
                        Graph::addBothSidesEdgeToMatrix(matrix, parent, newNode);
                    }
                }
                newAncestors.push_back(newNode);
            }
        }
        ancestors = newAncestors;
    }

    return matrix;
}
