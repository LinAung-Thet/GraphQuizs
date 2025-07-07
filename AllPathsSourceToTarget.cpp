#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm> // for std::find
using namespace std;
class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<int>& path, vector<vector<int>>& result) {
        path.push_back(node);

        if (node == graph.size() - 1) {
            result.push_back(path); // Reached target
        } else {
            for (int next : graph[node]) {
                dfs(next, graph, path, result);
            }
        }

        path.pop_back(); // Backtrack
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> result;
        vector<int> path;
        dfs(0, graph, path, result);
        return result;
    }
};

// Example usage
int main() {
    Solution solution;
    vector<vector<int>> graph;
    vector<vector<int>> result;

    graph = {{1,2},{3},{3},{}};
    result = solution.allPathsSourceTarget(graph);
    // Print the result
    for(const auto& path : result) {
        for(int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    // Expected output:
    cout << "Expected output: [[0,1,3],[0,2,3]] \n";

    graph = {{4,3,1},{3,2,4},{3},{4},{}};
    result = solution.allPathsSourceTarget(graph);
    // Print the result
    for(const auto& path : result) {
        for(int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    return 0;
}