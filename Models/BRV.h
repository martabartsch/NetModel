#ifndef NETMODEL_BRV_H
#define NETMODEL_BRV_H

#include "Graph.h"
#include <vector>

using namespace std;

class BRV {
private:
    vector<int> lastConnectedToRootPoints;
public:
    vector<vector<int>> generateBRVAdjacencyList(int iterations);
    vector<vector<int>> generateBRVAdjacencyMatrix(int iterations);

};

#endif //NETMODEL_BRV_H
