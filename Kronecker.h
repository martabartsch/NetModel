//
// Created by Marta Bartsch on 03/02/2025.
//

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
    AdjacencyList createAdjList(string& input);
    int computeKroneckerProductList(AdjacencyList& G, AdjacencyList& H);
    void computeShortestPaths(AdjacencyList& G, AdjacencyList& distG, int start);
    AdjacencyMatrix createAdjacencyMatrix(string& input);
    AdjacencyMatrix computeKroneckerProductMatrix(AdjacencyMatrix &G, AdjacencyMatrix &H, int size);
    AdjacencyMatrix computeDistanceMatrix(AdjacencyMatrix& G, AdjacencyMatrix H, AdjacencyMatrix& distG);
    AdjacencyMatrix computeShortestPaths(AdjacencyMatrix& G);
    int calculateTotalGraphDistance(AdjacencyMatrix& distH);
    AdjacencyMatrix computeGraphPower(AdjacencyMatrix G, string &matrix, int exponent);
    void computeAndDisplayResults(string &matrix, int exponent);



};


#endif //NETMODEL_KRONECKER_H
