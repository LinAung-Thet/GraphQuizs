// https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/description/?envType=problem-list-v2&envId=shortest-path

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int dfs(int i, int m, vector<vector<pair<int, int>>> &ral, vector<bool> &vis) {
        int res = 1; vis[i] = true;
        for (auto [j, w] : ral[i])
            if (w <= m && !vis[j])
                res += dfs(j, m, ral, vis);
        return res;
    }
    int minimumMaxWeight(int n, int threshold, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> ral(n);
        for (auto &e : edges)
            ral[e[1]].push_back({e[0], e[2]});
        
        int l = 1, r = 1000001;
        
        while (l < r) {
            int m = (l + r) / 2;
            
            vector<bool> vis(n, false);
            
            if (dfs(0, m, ral, vis) == n)
                r = m;
            else
                l = m + 1;
        }
        
        return l == 1000001 ? -1 : l;
    }
};

// Test cases
int main() {
    Solution solution;

    vector<vector<int>> edges;
    int n;
    int outDegreeThreshold;
    int result;

    // Test case 1
    edges = {{1,0,1},{2,0,2},{3,0,1},{4,3,1},{2,1,1}};
    n = 5;
    outDegreeThreshold = 2;
    result = solution.minimumMaxWeight(n, outDegreeThreshold, edges);
    cout << "Minimum max edge weight: " << result << ", Expected: 1" << endl; 

    // Test case 2
    edges = {{0,1,1},{0,2,2},{0,3,1},{0,4,1},{1,2,1},{1,4,1}};
    n = 5;
    outDegreeThreshold = 1;
    result = solution.minimumMaxWeight(n, outDegreeThreshold, edges);
    cout << "Minimum max edge weight: " << result << ", Expected: -1" << endl; 

    // Test case 3
    edges = {{1,2,1},{1,3,3},{1,4,5},{2,3,2},{3,4,2},{4,0,1}};
    n = 5;
    outDegreeThreshold = 1;
    result = solution.minimumMaxWeight(n,outDegreeThreshold, edges);
    cout << "Minimum max edge weight: " << result << ", Expected: 2" << endl; 

    // Test case 4
    edges = {{1,2,1},{1,3,3},{1,4,5},{2,3,2},{4,0,1}};
    n = 5;
    outDegreeThreshold = 1;
    result = solution.minimumMaxWeight(n,outDegreeThreshold, edges);
    cout << "Minimum max edge weight: " << result << ", Expected: -1" << endl; 

    // Test case 5
    edges = {{2,0,39},{2,1,72},{2,3,67},{1,2,78},{3,0,10},{0,2,81},{1,0,78},{1,3,78}};
    n = 4;
    outDegreeThreshold = 2;
    result = solution.minimumMaxWeight(n,outDegreeThreshold, edges);
    cout << "Minimum max edge weight: " << result << ", Expected: 78" << endl;
}