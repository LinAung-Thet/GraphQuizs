#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> graph(n);
        //Construct a grpah which defines connections for each nodes
        for(const auto& edge : edges) {
            int a = edge[0], b = edge[1];
            graph[a].insert(b);
            graph[b].insert(a);
        }

        vector<int> roots;
        int maxConn = -1;
        for(int i=0; i<n; i++) {
            if(graph[i].size() > i) {
                maxConn = graph[i].size();
                roots.clear();
            }
            if(graph[i].size() == maxConn)
                roots.push_back(i);
        }

        return roots;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}};
    int n = 5;

    edges = {{1,0},{1,2},{1,3}};
    n = 4;
    vector<int> result = sol.findMinHeightTrees(n, edges);
    
    // Display the result
    for (int root : result) {
        cout << root << " ";
    }
    cout << endl;

    return 0;
}