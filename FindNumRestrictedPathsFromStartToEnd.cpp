// https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/description/?envType=problem-list-v2&envId=shortest-path

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int MOD = 1e9 + 7;

class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        // Step 1: Build the graph
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        // Step 2: Dijkstra from node n to compute distanceToLastNode
        vector<int> dist(n + 1, INT_MAX);
        dist[n] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, n);

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto& [v, w] : graph[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        // Step 3: DFS with memoization to count restricted paths
        vector<int> memo(n + 1, -1);
        return dfs(1, n, graph, dist, memo);
    }

private:
    int dfs(int u, int n, vector<vector<pair<int, int>>>& graph, vector<int>& dist, vector<int>& memo) {
        if (u == n) return 1;
        if (memo[u] != -1) return memo[u];

        long long total = 0;
        for (auto& [v, _] : graph[u]) {
            if (dist[u] > dist[v]) {
                total += dfs(v, n, graph, dist, memo);
                total %= MOD;
            }
        }

        return memo[u] = total;
    }
};

// Test cases
int main() {
    Solution solution;
    vector<vector<int>> edges;
    int n;

    // Test case 1
    edges = {{1, 2, 3}, {1, 3, 3}, {2, 3, 1}, {1, 4, 2}, {5, 2, 2}, {3, 5 , 1}, {5, 4, 10}};
    n = 5;
    cout << "Restricted paths count: " << solution.countRestrictedPaths(n, edges) 
         << ", Expected Output: 3" << endl; 

    // Test case 2
    edges = {{1, 3, 1}, {4, 1, 2}, {7, 3, 4}, {2, 5, 3}, {5, 6, 1}, {6, 7, 2}, {7, 5, 3}, {2, 6, 4}};
    n = 7;
    cout << "Restricted paths count: " << solution.countRestrictedPaths(n, edges) 
         << ", Expected Output: 1" << endl; 

    return 0;
}