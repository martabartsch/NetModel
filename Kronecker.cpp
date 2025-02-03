#include "Kronecker.h"


Kronecker::AdjacencyList Kronecker::computeKroneckerProductAdjList(AdjacencyList& G, AdjacencyList& H, int newSize) {
    AdjacencyList newAdjList(newSize);

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            int x = i % G.size();
            int y = i / G.size();
            int x_prim = j % G.size();
            int y_prim = j / G.size();

            int isGEdge = G[x][x_prim].second;
            int isHEdge = H[y][y_prim].second;

            if ((isGEdge && isHEdge) || (y == y_prim && isGEdge) || (x == x_prim && isHEdge)) {
                newAdjList[i].push_back({j, 1});
            } else {
                newAdjList[i].push_back({j, 0});
            }
        }
    }
    return newAdjList;
}

void Kronecker::computeShortestPaths(AdjacencyList& G, AdjacencyList& distG, int start) {
    AdjacencyList distances = AdjacencyList(G.size(), vector<pair<int, int>>(G.size(), {0, INT_MAX}));
    queue<int> q;
    q.push(start);

    distances[start][start].second = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto& neighbor : G[node]) {
            int neighborNode = neighbor.first;

            if (distances[start][neighborNode].second == INT_MAX && distG[node][neighborNode].second == 1) {
                distances[start][neighborNode].second = distances[start][node].second + 1;
                distG[start][neighborNode].second = distances[start][neighborNode].second;
                q.push(neighborNode);
            }
        }
    }
}

Kronecker::AdjacencyList Kronecker::computeDistanceList(AdjacencyList& G, AdjacencyList& H){
    AdjacencyList distG = G;
    for (int start = 0; start < G.size(); start++) {
        computeShortestPaths(G, distG, start);
    }
    for (int i = 0; i < H.size(); i++) {
        for (int j = i+1; j < H.size(); ++j) {
            int x = i % G.size();
            int y = i / G.size();
            int x_prim = j % G.size();
            int y_prim = j / G.size();

            if (H[i][j].second == 0) {
                if (x == x_prim) {
                    //  path to y - y_prim
                    H[i][j].second = H[y][y_prim].second;
                } else if (y == y_prim) {
                    //  path to x - x_prim
                    H[i][j].second = distG[x][x_prim].second;
                } else {
                    //  max between two paths
                    H[i][j].second = std::max(distG[x][x_prim].second, H[y][y_prim].second);
                }
            }
        }
    }
}

int Kronecker::calculateTotalDistance(AdjacencyList& H){
    int totalDistance=0;
    for (int i = 0; i < H.size(); i++) {
        for (int j = i+1; j < H.size(); ++j){
            if (H[i][j].second != 0 && H[i][j].second != INT_MAX) {
                totalDistance += H[i][j].second;
            }
        }
    }

    return totalDistance;
}
Kronecker::AdjacencyList Kronecker::adjacencyListKronecker(string &matrix, int exponent) {
    AdjacencyList G = Graph::createAdjList(matrix);
    AdjacencyList H = G;
    for (int power = 1; power < exponent; power++) {
        H = computeKroneckerProductAdjList(G, H, G.size() * H.size());
    }
    computeDistanceList(G, H);

    return H;
}


Kronecker::AdjacencyMatrix Kronecker::computeKroneckerProductMatrix(Kronecker::AdjacencyMatrix &G, Kronecker::AdjacencyMatrix &H, int size) {
    vector<vector<int>> newMatrix(size, vector<int>(size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int x = i % G.size(); // ( 0, 1, 2)
            int y = i / G.size(); // ( 0, 1, 2)
            int x_prim = j % G.size();
            int y_prim = j / G.size();

            if ((G[x][x_prim] && H[y][y_prim]) || (y == y_prim &&  G[x][x_prim]) || (x == x_prim && H[y][y_prim])) {
                newMatrix[i][j] = 1;
                newMatrix[j][i] = 1;
            }
        }
    }

    return newMatrix;
}

Kronecker::AdjacencyMatrix Kronecker::bfsMatrix(Kronecker::AdjacencyMatrix &G) {
    AdjacencyMatrix distG = G;
    for (int start = 0; start < distG.size(); start++) {
        vector<int> distances(distG.size(), INT_MAX);
        distances[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor = 0; neighbor < distG.size(); ++neighbor) {
                if (distG[node][neighbor] == 1 && distances[neighbor] == INT_MAX) {
                    distances[neighbor] = distances[node] + 1;
                    distG[start][neighbor] = distances[neighbor];
                    q.push(neighbor);
                }
            }
        }
    }
    return distG;
}

Kronecker::AdjacencyMatrix Kronecker::computeDistanceMatrix(AdjacencyMatrix& G, AdjacencyMatrix H, AdjacencyMatrix& distG) {
    for (int i = 0; i < H.size(); i++) {
        for (int j = i + 1; j < H.size(); j++) {
            int x = i % G.size();
            int y = i / G.size();
            int x_prim = j % G.size();
            int y_prim = j / G.size();

            if (H[i][j] == 0) {
                if (distG[x][x_prim] > H[y][y_prim]) {
                    Graph::updateEdgeWeight(H, i, j, distG[x][x_prim]);
                } else {
                    Graph::updateEdgeWeight(H, i, j, H[y][y_prim]);
                }
            }
        }
    }
    return H;
}
int Kronecker::calculateTotalGraphDistance(AdjacencyMatrix& distH) {
    int totalDistance = 0;
    for (int x = 0; x < distH.size(); x++) {
        for (int y = x + 1; y < distH.size(); y++) {
            if (distH[x][y] != 0 && distH[x][y] != INT_MAX) {
                totalDistance += distH[x][y];
            }
        }
    }
    return totalDistance;
}
Kronecker::AdjacencyMatrix Kronecker::adjacencyMatrixKronecker(string &matrix, int exponent) {
    AdjacencyMatrix G = Graph::createAdjacencyMatrix(matrix);
    AdjacencyMatrix H = G;
    for (int power = 1; power < exponent; power++) {
        int newSize = G.size() * H.size();
        H = computeKroneckerProductMatrix(G, H, newSize);
    }
    AdjacencyMatrix distG = bfsMatrix(G);
    H = computeDistanceMatrix(G, H, distG);
    Graph::printAdjacencyMatrix(H);

    return H;
}