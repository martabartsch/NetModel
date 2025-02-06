#include <iostream>
#include<string>
#include "Models/BRV.h"
#include "Models/DCN.h"
#include "Models/IterativeGrowth.h"
#include "Models/LuSuGuo.h"
#include "Models/Kronecker.h"
#include "Models/Graph.h"

using namespace std;


int main() {
    int num_model, value;
    while(cin>>num_model>>value)
    {
        int choice;
        cout << "Choose the representation: "<<endl;
        if(num_model == 3){
            cout<<"1: Adjacency List"<<endl;
        }
        else{
            cout << "1: Adjacency List, 2: Adjacency Matrix: "<<endl;
        }
        cin >> choice;
        cout<<"-------"<<endl;
        while (true) {
            cin >> choice;
            if ((num_model == 2 && choice == 1) || (num_model != 2 && (choice == 1 || choice == 2))) {
                break;
            }
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

        cout << "-------" << endl;
        switch(num_model) {
            case 0: {
                BRV brv;
                if (choice == 1) {
                    vector<vector<int>> adjList = brv.generateBRVAdjacencyList(value);
                    value = Graph::calculateTotalDistance(adjList);
                }
                else if (choice == 2){
                    vector<vector<int>> adjMatrix = brv.generateBRVAdjacencyMatrix(value);
                    value = Graph::calculateTotalDistanceMatrix(adjMatrix);
                }
                cout << value << endl;
                break;
            }
            case 1:{
                LuSuGuo luSuGuo;
                if (choice == 1) {
                    vector<vector<int>> adjList = luSuGuo.adjacencyListLuSuGuo(value);
                    value = Graph::calculateTotalDistance(adjList);
                }
                else if (choice == 2){
                    vector<vector<int>> adjMatrix = luSuGuo.adjacencyMatrixLuSuGuo(value);
                    value = Graph::calculateTotalDistanceMatrix(adjMatrix);
                }
                cout << value << endl;
                break;
            }
            case 2: {
                int param;
                long long total_distance = 0;
                cin >> param;
                if (choice == 1) {
                    IterativeGrowth iterativeGrowth;
                    total_distance = iterativeGrowth.iterativeGrowthAdjList(value, param);
                }
                cout << total_distance << endl;
                break;
            }
            case 3:{
                DCN dcn;
                if (choice == 1) {
                    vector<vector<int>> adjList = dcn.adjacencyListDCN(value);
                    value = Graph::calculateTotalDistance(adjList);
                }
                else if (choice == 2){
                    vector<vector<int>> adjMatrix = dcn.adjacencyMatrixDCN(value);
                    value = Graph::calculateTotalDistanceMatrix(adjMatrix);
                }
                cout << value << endl;
                break;
            }
            case 4:
                string matrix;
                cin >> matrix;

                Kronecker kronecker;
                if (choice == 1) {
                    vector<vector<pair<int, int>>> adjList = kronecker.adjacencyListKronecker(matrix, value);
                    value = kronecker.calculateTotalDistance(adjList);
                }
                else if (choice == 2){
                    vector<vector<int>> adjMatrix = kronecker.adjacencyMatrixKronecker(matrix, value);
                    value = kronecker.calculateTotalGraphDistance(adjMatrix);
                }
                cout << value << endl;
                break;
        }
    }
    return 0;
}
