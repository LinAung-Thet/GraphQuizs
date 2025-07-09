// https://leetcode.com/problems/minimum-time-to-reach-destination-in-directed-graph/description/?envType=problem-list-v2&envId=shortest-path

#include <vector>
#include <queue>
#include <limits.h>
#include <iostream>
#include <chrono>
#include <utility>
#include <windows.h>

using namespace std;
using namespace std::chrono;

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        if(n == 1) return 0; // If there's only one node, no time is needed to reach it
        if(edges.empty()) return -1; // If there are no edges, it's impossible to reach the destination

        // Build the adjacency matrix, each contains [v,start,end]
        vector<vector<tuple<int,int,int>>> graph(n);
        for(auto& edge: edges) {
            int u = edge[0],v = edge[1],s = edge[2],e = edge[3];
            graph[u].emplace_back(v, s, e);
        }

        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> q; // [curTime, curNode]
        vector<int> minTimes(n, INT_MAX);

        // Starts from node 0 at time 0
        q.emplace(0,0);

        // Find the shortest path
        while(!q.empty()){
            auto [curTime, curNode] = q.top();
            q.pop();

            // If we have already found a better time for this node, skip it
            if(curTime >= minTimes[curNode]) continue;
            minTimes[curNode] = curTime;

            for(auto& [v,s,e]: graph[curNode]) {
                int waitTime = max(curTime, s); // Wait until the start time if necessary

                if(waitTime > e) continue;   // If the waiting time exceeds the end time, don't proceed

                int arrivalTime = waitTime + 1; // add the transition time 1 sec

                // If the arrival time is less than the recorded time for the node, add it to the queue
                if(arrivalTime < minTimes[v]) {
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
    // // Set the current process to high priority
    // if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
    //     std::cerr << "Failed to set priority.\n";
    //     return 1;
    // }

    // std::cout << "Process priority set to HIGH.\n";

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

    // Test case 5
    edges = {{2,1,1,14},{0,2,15,16},{1,4,1,11},{1,4,4,25},
             {0,2,17,21},{3,0,13,22},{3,2,15,18},{2,4,3,23},{1,3,11,12}};
    n = 5;
    result = solution.minTime(n, edges);
    cout << "Minimum time to reach node " << n-1 << ": " << result << ", Expected: 17" << endl; // Expected output: Minimum time to reach node 4: 10

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}