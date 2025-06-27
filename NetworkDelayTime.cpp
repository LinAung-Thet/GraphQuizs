#include <vector>
#include <limits.h> // For INT_MAX
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& edge : times) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
        }

        // Min-heap: (time, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        pq.emplace(0, k);

        while (!pq.empty()) {
            auto [currTime, u] = pq.top();
            pq.pop();

            if (currTime > dist[u]) continue;  // Skip outdated entry

            for (auto& [v, weight] : graph[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        int maxDelay = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1;  // Unreachable node
            maxDelay = max(maxDelay, dist[i]);
        }

        return maxDelay;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4;
    int k = 2;
    int result = solution.networkDelayTime(times, n, k);
    cout << "Network Delay Time: " << result << " Expected output: 2" << endl;

    times = {{1,2,1}};
    n = 2;
    k = 1;
    result = solution.networkDelayTime(times, n, k);
    cout << "Network Delay Time: " << result << " Expected output: 1" << endl;

    times = {{1,2,1}};
    n = 2;
    k = 2;
    result = solution.networkDelayTime(times, n, k);
    cout << "Network Delay Time: " << result << " Expected output: -1" << endl;

    return 0;
}