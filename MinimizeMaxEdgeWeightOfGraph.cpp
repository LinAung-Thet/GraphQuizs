// https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/description/?envType=problem-list-v2&envId=shortest-path

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumMaxWeight(int n, int threshold, vector<vector<int>>& edges) {
        int left = 0, right = 0;
        for (auto& e : edges) right = max(right, e[2]);

        int answer = -1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (isValid(n, threshold, edges, mid)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return answer;
    }

private:
    bool isValid(int n, int threshold, vector<vector<int>>& edges, int maxWeight) {
        vector<vector<int>> graph(n);       // forward graph
        vector<vector<int>> reverseGraph(n); // for reachability to node 0
        vector<int> outdegree(n, 0);

        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (w <= maxWeight) {
                graph[u].push_back(v);
                reverseGraph[v].push_back(u);
                outdegree[u]++;
            }
        }

        // Check outdegree constraint
        for (int i = 0; i < n; ++i) {
            if (outdegree[i] > threshold) return false;
        }

        // Check if all nodes can reach node 0 (i.e., node 0 is reachable from all nodes)
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : reverseGraph[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) return false;
        }

        return true;
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
    edges = {{2,0,39},{2,1,72},{2,3,67},{1,2,78},{3,0,10},{0,2,81}};
    n = 4;
    outDegreeThreshold = 2;
    result = solution.minimumMaxWeight(n,outDegreeThreshold, edges);
    cout << "Minimum max edge weight: " << result << ", Expected: 78" << endl;
}