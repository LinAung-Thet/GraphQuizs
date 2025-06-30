// https://leetcode.com/problems/cheapest-flights-within-k-stops/submissions/1680974652/?envType=problem-list-v2&envId=graph

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (auto& flight : flights) {
            int u = flight[0], v = flight[1], w = flight[2];
            graph[u].emplace_back(v, w);
        }

        // Priority queue: (cost so far, current node, stops used)
        queue<tuple<int, int, int>> pq;
        pq.emplace(0, src, -1);

        // Visited array to store [city][stops] → cost
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        while (!pq.empty()) {
            auto [cost, node, stops] = pq.front();
            pq.pop();

            // if (node == dst) return cost;
            if (stops >= k) continue;

            for (auto& [neighbor, price] : graph[node]) {
                int nextCost = cost + price;
                if (nextCost < dist[neighbor]) {
                    dist[neighbor] = nextCost;
                    pq.emplace(nextCost, neighbor, stops + 1);
                }
            }
        }

        // return -1;  // Destination unreachable within k stops

        return dist[dst] == INT_MAX ? -1 : dist[dst];
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

    flights = {{0,1,100},{1,2,100},{0,2,500}};
    n = 3;
    src = 0;
    dst = 2;
    k = 1;
    result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 200" << endl;

    flights = {{0,1,1},{0,2,5},{1,2,1},{2,3,1}};
    n = 4;
    src = 0;
    dst = 3;
    k = 1;
    result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 6" << endl;
}