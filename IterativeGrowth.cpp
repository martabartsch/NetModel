#include "IterativeGrowth.h"

// Function to perform iterative growth of an adjacency list and calculate the total distance
long long IterativeGrowth::iterativeGrowthAdjList(int iterations_num, int r) {
    vector<vector<int>> adjacency_list(2);
    Graph::addBothSidesEdge(adjacency_list, 0, 1);

    vector<pair<int, int>> current_edges = {{0, 1}};

    int current_node = 2;
    long long total_distance = 1;

    for (int k = 1; k <= iterations_num; ++k) {
        vector<pair<int, int>> new_edges;

        for (auto& edge : current_edges) {
            int u = edge.first;
            int v = edge.second;

            long long edge_distance = 0;
            bool distance_calculated = false;

            // Add 'r' new nodes for each edge
            for (int i = 0; i < r; ++i) {
                adjacency_list.push_back({u, v});
                Graph::addBothSidesEdge(adjacency_list, u, current_node);
                Graph::addBothSidesEdge(adjacency_list, v, current_node);

                // calculate the distances using BFS
                if (!distance_calculated) {
                    vector<int> distance(current_node + 1, -1);
                    queue<int> q;
                    q.push(current_node);
                    distance[current_node] = 0;

                    while (!q.empty()) {
                        int current = q.front();
                        q.pop();

                        for (int neighbor : adjacency_list[current]) {
                            if (distance[neighbor] == -1) {
                                distance[neighbor] = distance[current] + 1;
                                q.push(neighbor);
                                edge_distance += distance[neighbor];
                            }
                        }
                    }
                    distance_calculated = true;
                    total_distance += edge_distance * r;
                }
                else{
                    // distances are similar to the previous.
                    total_distance += r;
                }
                // expanded in the next iteration
                new_edges.emplace_back(u, current_node);
                new_edges.emplace_back(v, current_node);
                ++current_node;
            }
        }
        // update the current edges for the next iteration
        current_edges = new_edges;
    }
    Graph::printAdjacencyList(adjacency_list);

    return total_distance;
}
