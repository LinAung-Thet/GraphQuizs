// https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/?envType=problem-list-v2&envId=shortest-path

#include<vector>
#include<iostream>
#include<queue>
#include<chrono>
using namespace std;
using namespace chrono;
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const int MOD = 1e9 + 7;
        using pii = pair<long long, int>; // (time, node)
        vector<vector<pair<int, int>>> graph(n);
        
        // Build the graph
        for (auto& road : roads) {
            int u = road[0], v = road[1], time = road[2];
            graph[u].emplace_back(v, time);
            graph[v].emplace_back(u, time);
        }

        // Dijkstra initialization
        priority_queue<pii, vector<pii>, greater<>> pq;
        vector<long long> dist(n, LLONG_MAX);
        vector<int> ways(n, 0);
        
        pq.emplace(0, 0); // (time, node)
        dist[0] = 0;
        ways[0] = 1;

        while (!pq.empty()) {
            auto [time, node] = pq.top(); pq.pop();
            
            if (time > dist[node]) continue; // Already found shorter path

            for (auto& [nei, t] : graph[node]) {
                long long newTime = time + t;

                if (newTime < dist[nei]) {
                    dist[nei] = newTime;
                    ways[nei] = ways[node];
                    pq.emplace(newTime, nei);
                } else if (newTime == dist[nei]) {
                    ways[nei] = (ways[nei] + ways[node]) % MOD;
                }
            }
        }

        return ways[n - 1];
    }
};

int main() {
    Solution solution;
    vector<vector<int>> roads;
    int n, result;

    auto startTime = high_resolution_clock::now();

    // Test 1
    n = 7;
    roads = {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};
    result = solution.countPaths(n, roads);
    cout << "Number of ways to arrive at destination: " << result << ", Expected: " << 4 << endl; // Expected output: 4

    // Test 2
    n = 2;
    roads = {{1,0,10}};
    result = solution.countPaths(n, roads);
    cout << "Number of ways to arrive at destination: " << result << ", Expected: " << 1 << endl; // Expected output: 4

    // Test 3
    n = 12;
    roads = {{1,0,2348},{2,1,2852},{2,0,5200},{3,1,12480},{2,3,9628},{4,3,7367},{4,0,22195},
             {5,4,5668},{1,5,25515},{0,5,27863},{6,5,836},{6,0,28699},{2,6,23499},{6,3,13871},
             {1,6,26351},{5,7,6229},{2,7,28892},{1,7,31744},{3,7,19264},{6,7,5393},{2,8,31998},
             {8,7,3106},{3,8,22370},{8,4,15003},{8,6,8499},{8,5,9335},{8,9,5258},{9,2,37256},
             {3,9,27628},{7,9,8364},{1,9,40108},{9,5,14593},{2,10,45922},{5,10,23259},{9,10,8666},
             {10,0,51122},{10,3,36294},{10,4,28927},{11,4,25190},{11,9,4929},{11,8,10187},{11,6,18686},
             {2,11,42185},{11,3,32557},{1,11,45037}};
    result = solution.countPaths(n, roads);
    cout << "Number of ways to arrive at destination: " << result << ", Expected: " << endl; // Expected output: 4
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);

    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    
    return 0;
}