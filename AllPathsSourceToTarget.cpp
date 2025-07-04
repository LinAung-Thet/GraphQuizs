#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    void dfs(vector<vector<int>>& graph, vector<vector<vector<int>>>& paths, int node) {
        // int n = graph.size();
        if(node == graph.size() - 1) {
            // If we reach the last node, we have found a valid path
            return;
        }   
        // vector<vector<int>> buffer;
        for(int i=0; i<paths[node].size(); i++) {
            for(auto next : graph[node]) {
                // Duplicate the current path according to the number of outgoing edges from the current node
                paths[next].push_back(paths[node][i]);
                // Append the next node to the current path
                paths[next][paths[next].size() - 1].push_back(next);

                dfs(graph, paths, next);
            }
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<vector<int>>> paths(n, vector<vector<int>>());
        paths[0].push_back({0}); // Start with the source node
        dfs(graph, paths, 0);

        return paths[n-1];
    }
};
// Example usage
int main() {
    Solution solution;
    vector<vector<int>> graph = {{1,2},{3},{3},{}};
    vector<vector<int>> result = solution.allPathsSourceTarget(graph);
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