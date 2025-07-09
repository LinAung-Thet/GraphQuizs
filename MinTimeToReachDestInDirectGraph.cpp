// https://leetcode.com/problems/minimum-time-to-reach-destination-in-directed-graph/description/?envType=problem-list-v2&envId=shortest-path

#include <vector>
#include <queue>
#include <limits.h>
#include <iostream>
#include <chrono>
#include <utility>


using namespace std;
using namespace std::chrono;

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        if(n == 1) return 0; // If there's only one node, no time is needed to reach it
        if(edges.empty()) return -1; // If there are no edges, it's impossible to reach the destination

        // Build the adjacency matrix, each contains [v,start,end]
        vector<vector<vector<int>>> graph(n);
        for(auto& edge: edges) {
            int u = edge[0],v = edge[1],s = edge[2],e = edge[3];
            graph[u].push_back({v, s, e});
        }

        queue<pair<int, int>> q; // [curTime, curNode]
        vector<int> minTimes(n, INT_MAX);

        // Starts from node 0 at time 0
        q.emplace(0,0);

        // Find the shortest path
        while(!q.empty()){
            auto& [curTime, curNode] = q.front();
            q.pop();

            int arrivalTime;
            
            for(auto& edge: graph[curNode]) {
                int v = edge[0], s = edge[1], e = edge[2];
                if(s <= curTime) arrivalTime = curTime;     // If start <= curr time, arrival time = curr time
                else arrivalTime = curTime + (s-curTime);   // Otherwise, arrival time = curr time + (start - curr time)

                if(arrivalTime > e) continue;   // If the arrival time exceeds the end time, don't proceed

                arrivalTime++; // add the transition time 1 sec

                // If the arrival time is less than the recorded time for the node, add it to the queue
                if(arrivalTime < minTimes[v]) {
                    minTimes[v] = arrivalTime;
                    q.emplace(arrivalTime, v);
                }
            }
        }

        // If the last node's time is still INT_MAX, it means it's unreachable
        return minTimes[n-1] == INT_MAX ? -1 : minTimes[n-1];
    }
};

// Test cases
int main() {
    Solution solution;

    vector<vector<int>> edges;
    int n;
    int result;

    auto startTime = high_resolution_clock::now();

    // Test case 1
    edges = {
        {0, 1, 0, 1},
        {1, 2, 2, 5}
    };
    n = 3; // Number of nodes
    result = solution.minTime(n, edges);
    cout << "Minimum time to reach node " << n-1 << ": " << result << ", Expected: 3" << endl; // Expected output: Minimum time to reach node 4: 10

    // Test case 2
    edges = {
        {0, 1, 0, 3},
        {1, 3, 7, 8},
        {0, 2, 1, 5},
        {2, 3, 4, 7}
    };
    n = 4; // Number of nodes
    result = solution.minTime(n, edges);
    cout << "Minimum time to reach node " << n-1 << ": " << result << ", Expected: 5" << endl; // Expected output: Minimum time to reach node 4: 10

    // Test case 3
    edges = {
        {1, 0, 1, 3},
        {1, 2, 3, 5}
    };
    n = 3; // Number of nodes
    result = solution.minTime(n, edges);
    cout << "Minimum time to reach node " << n-1 << ": " << result << ", Expected: -1" << endl; // Expected output: Minimum time to reach node 4: 10

    // Test case 4
    edges = {};
    n = 1;
    result = solution.minTime(n, edges);
    cout << "Minimum time to reach node " << n-1 << ": " << result << ", Expected: 0" << endl; // Expected output: Minimum time to reach node 4: 10

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}