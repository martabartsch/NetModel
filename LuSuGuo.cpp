#include "LuSuGuo.h"

// Function to generate an adjacency list for the Lu Su Guo model
vector<vector<int>> LuSuGuo::adjacencyListLuSuGuo(int numNodes) {
    vector<vector<int>> adjacencyList(numNodes);

    if (numNodes == 1) return {};

    Graph::addBothSidesEdge(adjacencyList, 0, 1);
    Graph::addBothSidesEdge(adjacencyList, 1, 2);
    Graph::addBothSidesEdge(adjacencyList, 0, 2);

    vector<int> index = {1, 2};
    int iteration = 1;
    int currentNode = 3;
    int target = numNodes - 3;

    while (target > 0) {
        int tmp_target = currentNode;
        iteration++;
        int parent;

        int iterator = 0;
        while (iterator < index.size()) {
            int actualIndexNode = index[iterator];

            if (target == 1) {
                int newNode = tmp_target++;
                Graph::addBothSidesEdge(adjacencyList, newNode, actualIndexNode);
                parent = ((newNode - 1) / 2) % (iteration - 1);
                Graph::addBothSidesEdge(adjacencyList, newNode, parent);
                target--;
                break;
            }

            if (target > 1) {
                int node1 = tmp_target++;
                parent = ((node1 - 1) / 2) % (iteration - 1);
                Graph::addBothSidesEdge(adjacencyList, node1, parent);
                Graph::addBothSidesEdge(adjacencyList, node1, actualIndexNode);

                int node2 = tmp_target++;
                parent = ((node2 - 1) / 2) % (iteration - 1);
                Graph::addBothSidesEdge(adjacencyList, node2, parent);
                Graph::addBothSidesEdge(adjacencyList, node2, actualIndexNode);

                Graph::addBothSidesEdge(adjacencyList, node1, node2);

                target -= 2;
            }

            if (target == 0) break;
            iterator++;
        }

        // add new nodes to the parent index list for the next iteration
        vector<int> newIndex;
        for (int i = currentNode; i < tmp_target; i++) {
            newIndex.push_back(i);
        }
        currentNode = tmp_target;
        index = newIndex;

        if (target == 0) break;
    }
    Graph::printAdjacencyList(adjacencyList);
    return adjacencyList;
}

// Function to generate an adjacency matrix for the Lu Su Guo model
vector<vector<int>> LuSuGuo::adjacencyMatrixLuSuGuo(int numNodes){
    vector<vector<int>> vertex(numNodes, vector<int>(numNodes, 0));
    Graph::addBothSidesEdgeToMatrix(vertex, 0, 1);
    Graph::addBothSidesEdgeToMatrix(vertex, 1, 2);
    Graph::addBothSidesEdgeToMatrix(vertex, 0, 2);

    if(numNodes == 1) return Graph::createEmptyMatrix(0);
    vector<int> index = {1, 2};
    int iteration = 1;
    int currentNode = 3;
    int target = numNodes - 3;

    while (target > 0) {
        int tmp_target = currentNode;
        iteration++;
        int parent;

        int iterator = 0;
        while(iterator != index.size())
        {
            int actualIndexNode = index[iterator];

            if (target == 1)
            {
                int newNode = tmp_target++;
                Graph::addBothSidesEdgeToMatrix(vertex, newNode, actualIndexNode);
                parent = ((newNode -1) / 2) % (iteration - 1);
                Graph::addBothSidesEdgeToMatrix(vertex, newNode, parent);
                target--;
                break;
            }

            if (target > 1)
            {
                int node1 = tmp_target++;
                parent = ((node1 -1) / 2) % (iteration - 1);
                Graph::addBothSidesEdgeToMatrix(vertex, node1, parent);
                // add edge to new vertex and k-1 parent vertex
                Graph::addBothSidesEdgeToMatrix(vertex, node1, actualIndexNode);

                int node2 = tmp_target++;
                parent = ((node2 -1) / 2) % (iteration - 1);
                Graph::addBothSidesEdgeToMatrix(vertex, node2, parent);
                // add edge to new vertex and k-1 parent vertex
                Graph::addBothSidesEdgeToMatrix(vertex, node2, actualIndexNode);

                // add edge between two new vertexes
                Graph::addBothSidesEdgeToMatrix(vertex, node1, node2);

                target -= 2;
            }

            if (target == 0) break;
            iterator++;
        }

        // add new nodes to the parent index list for the next iteration
        vector<int> newIndex;
        for (int i = currentNode; i < tmp_target; i++) {
            newIndex.push_back(i);
        }
        currentNode = tmp_target;
        index = newIndex;

        if (target == 0) break;
    }

    return vertex;
}
