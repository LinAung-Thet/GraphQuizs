#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};

    // Step 1: Build adjacency list
    vector<unordered_set<int>> adj(n);
    for (auto& edge : edges) {
        adj[edge[0]].insert(edge[1]);
        adj[edge[1]].insert(edge[0]);
    }

    // Step 2: Initialize first layer of leaves
    vector<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (adj[i].size() == 1) {
            leaves.push_back(i);
        }
    }

    // Step 3: Trim the leaves layer by layer
    int remainingNodes = n;
    while (remainingNodes > 2) {
        remainingNodes -= leaves.size();
        vector<int> newLeaves;
        for (int leaf : leaves) {
            int neighbor = *adj[leaf].begin();
            adj[neighbor].erase(leaf);
            if (adj[neighbor].size() == 1) {
                newLeaves.push_back(neighbor);
            }
        }
        leaves = newLeaves;
    }

    return leaves; // remaining 1 or 2 nodes are MHT roots
}

// Example usage
int main() {
    int n = 6;
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{3,4},{4,5}};
    
    vector<int> result = findMinHeightTrees(n, edges);
    cout << "Minimum Height Tree Roots: ";
    for (int root : result) {
        cout << root << " ";
    }
    cout << endl;

    n = 4;
    edges = {{1,0},{1,2},{1,3}};
    result = findMinHeightTrees(n, edges);
    cout << "Minimum Height Tree Roots: ";
    for (int root : result) {
        cout << root << " ";
    }
    cout << endl;

    n = 6;
    edges = {{3,0},{3,1},{3,2},{3,4},{5,4}};
    result = findMinHeightTrees(n, edges);
    cout << "Minimum Height Tree Roots: ";
    for (int root : result) {
        cout << root << " ";
    }
    cout << endl;
    return 0;
}
