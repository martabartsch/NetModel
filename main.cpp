#include <iostream>
#include<string>
#include "BRV.h"
#include "DCN.h"
#include "IterativeGrowth.h"
#include "LuSuGuo.h"
#include "Kronecker.h"
#include "Graph.h"

using namespace std;


int main() {
    int num_model, value;
    while(cin>>num_model>>value)
    {
        switch(num_model) {
            case 0: {
                BRV brv;
                vector<vector<int>> adjList = brv.generateBRVAdjacencyList(value);
                value = Graph::calculateTotalDistance(adjList);
                cout << value << endl;
                break;
            }
            case 1:{
                LuSuGuo luSuGuo;
                vector<vector<int>> adjList = luSuGuo.adjacencyListLuSuGuo(value);
                value = Graph::calculateTotalDistance(adjList);
                cout << value << endl;
                break;
            }
            case 3: {
                int param;
                long long total_distance;
                cin >> param;

                IterativeGrowth iterativeGrowth;
                total_distance = iterativeGrowth.iterativeGrowthAdjList(value, param);
                cout << total_distance << endl;
                break;
            }
            case 4:{
                DCN dcn;
                vector<vector<int>> adjList = dcn.adjacencyListDCN(value);
                value = Graph::calculateTotalDistance(adjList);
                cout << value << endl;
                break;
            }
            case 6:
                string matrix;
                cin >> matrix;

                Kronecker kronecker;
                kronecker.computeAndDisplayResults(matrix, value);
                break;
        }
    }
    return 0;
}