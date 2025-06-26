#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// BFS to compute tree height rooted at start
int bfsHeight(int start, const vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    int height = -1;

    while (!q.empty()) {
        int size = q.size();
        height++; // Increase depth level
        for (int i = 0; i < size; ++i) {
            int node = q.front(); q.pop();
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    return height;
}

// Returns pair<root, max height>
pair<int, int> findMaxHeightRoot(int n, const vector<vector<int>>& edges) {
    // Build adjacency list
    vector<vector<int>> adj(n);
    for (auto& e : edges) {
        int u = e[0], v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxHeight = -1, root = -1;

    for (int i = 0; i < n; ++i) {
        int h = bfsHeight(i, adj, n);
        if (h > maxHeight) {
            maxHeight = h;
            root = i;
        }
    }

    return {root, maxHeight};
}

// Example usage
int main() {
    int n = 6;
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{3,4},{4,5}};
    
    pair<int, int> result = findMaxHeightRoot(n, edges);
    cout << "Maximum Height Tree Roots " << result.first << " with height " << result.second << endl;

    n = 4;
    edges = {{1,0},{1,2},{1,3}};
    result = findMaxHeightRoot(n, edges);
    cout << "Maximum Height Tree Roots " << result.first << " with height " << result.second << endl;

    n = 6;
    edges = {{3,0},{3,1},{3,2},{3,4},{5,4}};
    result = findMaxHeightRoot(n, edges);
    cout << "Maximum Height Tree Roots " << result.first << " with height " << result.second << endl;
    return 0;
}
