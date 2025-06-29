#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        // the steps increase by unit at a time so no need of priority_queue

        // {steps , {node , dist}}
        queue<pair<int, pair<int, int>>> q;

        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        q.push({0, {src, 0}});

        while (!q.empty()) {
            int step = q.front().first;
            int node = q.front().second.first;
            int d = q.front().second.second;
            q.pop();

            // dont proceed further if the steps are more the k
            if (step > k) {
                continue;
            }

            for (auto n : adj[node]) {
                int adjNode = n.first;
                int adjDist = n.second;

                if (d + adjDist < dist[adjNode] && step <= k) {
                    dist[adjNode] = d + adjDist;
                    q.push({step + 1, {adjNode, dist[adjNode]}});
                }
            }
        }

        if (dist[dst] == INT_MAX) {
            return -1;
        } else {
            return dist[dst];
        }
    }
};

int main() {
    Solution solution;
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{0,2,500}};
    int n = 3;
    int src = 0;
    int dst = 2;
    int k = 1;
    int result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 200" << endl;

    flights = {{0,1,100},{1,2,100},{0,2,500}};
    n = 3;
    src = 0;
    dst = 2;
    k = 0;
    result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 500" << endl;

    flights = {{0,1,1},{0,2,5},{1,2,1},{2,3,1}};
    n = 4;
    src = 0;
    dst = 3;
    k = 1;
    result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 6" << endl;
}