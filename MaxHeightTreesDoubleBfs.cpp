#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Helper function: BFS to find farthest node and its distance from start
pair<int, int> bfs(int start, const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    
    int lastNode = start;
    int distance = -1;

    while (!q.empty()) {
        int size = q.size();
        distance++;
        for (int i = 0; i < size; ++i) {
            int node = q.front(); q.pop();
            lastNode = node;
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    return {lastNode, distance}; // (farthest node, distance)
}

// Returns pair<root, max height>
pair<int, int> findMaxHeightRootOptimized(int n, const vector<vector<int>>& edges) {
    if (n == 1) return {0, 0};

    vector<vector<int>> adj(n);
    for (const auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    // Step 1: Find farthest from node 0
    auto [farthest1, _] = bfs(0, adj);

    // Step 2: Find farthest from farthest1 (this gives diameter)
    auto [farthest2, diameter] = bfs(farthest1, adj);

    return {farthest2, diameter}; // or return farthest1
}

// Example usage
int main() {
    int n = 6;
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{3,4},{4,5}};
    
    pair<int, int> result = findMaxHeightRootOptimized(n, edges);
    cout << "Maximum Height Tree Roots " << result.first << " with height " << result.second << endl;

    n = 4;
    edges = {{1,0},{1,2},{1,3}};
    result = findMaxHeightRootOptimized(n, edges);
    cout << "Maximum Height Tree Roots " << result.first << " with height " << result.second << endl;

    n = 6;
    edges = {{3,0},{3,1},{3,2},{3,4},{5,4}};
    result = findMaxHeightRootOptimized(n, edges);
    cout << "Maximum Height Tree Roots " << result.first << " with height " << result.second << endl;
    return 0;
}
