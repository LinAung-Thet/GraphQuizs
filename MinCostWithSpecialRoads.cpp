#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <cmath>
#include <iostream>
#include <map>

using namespace std;
class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        // Step 1: Filter out inefficient special roads
        vector<vector<int>> filteredRoads;
        for (auto& road : specialRoads) {
            int a = road[0], b = road[1], c = road[2], d = road[3], cost = road[4];
            int directCost = abs(a - c) + abs(b - d);
            if (cost < directCost) {
                filteredRoads.push_back({a, b, c, d, cost});
            }
        }

        // Step 2: Distance map & priority queue
        map<pair<int, int>, int> dist;
        dist[{start[0], start[1]}] = 0;

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
        heap.push({0, start[0], start[1]});  // {currentCost, x, y}

        // Step 3: Dijkstra-style exploration
        while (!heap.empty()) {
            auto curr = heap.top();
            heap.pop();
            int currCost = curr[0], x = curr[1], y = curr[2];

            for (auto& road : filteredRoads) {
                int a = road[0], b = road[1], c = road[2], d = road[3], specialCost = road[4];
                int newCost = currCost + abs(x - a) + abs(y - b) + specialCost;

                if (!dist.count({c, d}) || newCost < dist[{c, d}]) {
                    dist[{c, d}] = newCost;
                    heap.push({newCost, c, d});
                }
            }
        }

        // Step 4: Compare normal vs. special paths
        int minCost = abs(target[0] - start[0]) + abs(target[1] - start[1]);
        for (auto& road : filteredRoads) {
            int c = road[2], d = road[3];
            int costToTarget = abs(target[0] - c) + abs(target[1] - d);
            if (dist.count({c, d})) {
                minCost = min(minCost, dist[{c, d}] + costToTarget);
            }
        }

        return minCost;
    }
};
// Test cases
int main() {
    Solution solution;
    vector<int> start = {1, 1};
    vector<int> target = {4, 5};
    vector<vector<int>> specialRoads = {{1,2,3,3,2},{3,4,4,5,1}};

    int result = solution.minimumCost(start, target, specialRoads);
    cout << "Result: " << result << " , Expected: " << 5 << endl;

    return 0;
}