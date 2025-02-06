#ifndef NETMODEL_LUSUGUO_H
#define NETMODEL_LUSUGUO_H

#include "Graph.h"
#include<vector>

using namespace std;

class LuSuGuo {
public:
    vector<vector<int>> adjacencyListLuSuGuo(int numNodes);
    vector<vector<int>> adjacencyMatrixLuSuGuo(int numNodes);
};


#endif //NETMODEL_LUSUGUO_H
