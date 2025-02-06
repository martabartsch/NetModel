//
// Created by Marta Bartsch on 03/02/2025.
//

#ifndef NETMODEL_GRAPH_H
#define NETMODEL_GRAPH_H

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Graph {
    public:
    static vector<vector<int>> createEmptyAdjacencyList(int size);
    static vector<vector<int>> createEmptyMatrix(int size);
    static vector<vector<pair<int, int>>>createAdjList(string& input);
    static vector<vector<int>> createAdjacencyMatrix(string& input);
    static void addBothSidesEdge(vector<vector<int>>& adjacencyList, int u, int v);
    static void addBothSidesEdgeToMatrix(vector<vector<int>>& graph, int x, int y);
    static void updateEdgeWeight(vector<vector<int>>& matrix, int a, int b, int value);
    static int calculateTotalDistance(const vector<vector<int>>& graph);
    static int calculateTotalDistanceMatrix(const vector<vector<int>>& graph);
    static void printAdjacencyMatrix(const vector<vector<int>>& matrix);
    static void printAdjacencyList(const vector<vector<int>>& adjacencyList);
};


#endif //NETMODEL_GRAPH_H
