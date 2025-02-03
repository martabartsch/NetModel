#ifndef NETMODEL_KRONECKER_H
#define NETMODEL_KRONECKER_H

#include "Graph.h"
#include <vector>

using namespace std;

class Kronecker {
public:
    typedef vector<vector<int>> AdjacencyMatrix;
    typedef vector<vector<pair<int, int>>> AdjacencyList;
    AdjacencyList computeKroneckerProductAdjList(AdjacencyList& G, AdjacencyList& H, int size);
    AdjacencyList computeDistanceList(AdjacencyList& G, AdjacencyList& H);
    AdjacencyList adjacencyListKronecker(string &matrix, int exponent);
    int calculateTotalDistance(AdjacencyList& H);
    void computeShortestPaths(AdjacencyList& G, AdjacencyList& distG, int start);
    AdjacencyMatrix computeKroneckerProductMatrix(AdjacencyMatrix &G, AdjacencyMatrix &H, int size);
    AdjacencyMatrix computeDistanceMatrix(AdjacencyMatrix& G, AdjacencyMatrix H, AdjacencyMatrix& distG);
    AdjacencyMatrix bfsMatrix(AdjacencyMatrix &G);
    int calculateTotalGraphDistance(AdjacencyMatrix& distH);
    AdjacencyMatrix adjacencyMatrixKronecker(string &matrix, int exponent);


};

#endif //NETMODEL_KRONECKER_H
