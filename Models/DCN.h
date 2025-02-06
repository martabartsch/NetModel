#ifndef NETMODEL_DCN_H
#define NETMODEL_DCN_H

#include "Graph.h"
#include <vector>

using namespace std;


class DCN {
public:
    vector<vector<int>> adjacencyListDCN(int numNodes);
    vector<vector<int>> adjacencyMatrixDCN(int numNodes);

};


#endif //NETMODEL_DCN_H
