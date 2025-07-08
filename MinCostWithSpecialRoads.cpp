#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <chrono>

using namespace std;
class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoadsRaw) {
        // Lambda to calculate Manhattan distance
        auto dist = [](pair<int, int> a, pair<int, int> b) {
            return abs(a.first - b.first) + abs(a.second - b.second);
        };

        using pii = pair<int, int>;
        using p3i = tuple<pii, pii, int>;

        // Filter special roads where using them is cheaper than direct travel
        vector<p3i> specialRoads;
        for (auto& road : specialRoadsRaw) {
            pii p1 = {road[0], road[1]}, p2 = {road[2], road[3]};
            int cost = road[4];
            if (dist(p1, p2) > cost) {
                specialRoads.emplace_back(p1, p2, cost);
            }
        }

        // Priority queue for Dijkstra-style traversal
        priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<>> heap;
        set<pii> seen;
        int mn = dist({start[0], start[1]}, {target[0], target[1]});

        heap.emplace(0, pii(start[0], start[1]));

        while (!heap.empty()) {
            auto [cost, pos] = heap.top(); heap.pop();
            if (seen.count(pos) || cost > mn) continue;    

            mn = min(mn, cost + dist(pos, {target[0], target[1]}));
            seen.insert(pos);

            for (auto& [rdBeg, rdEnd, roadCost] : specialRoads) {
                int nextCost = cost + roadCost + dist(pos, rdBeg);
                heap.emplace(nextCost, rdEnd);
                nextCost = nextCost;
            }
        }

        return mn;
    }
};
// Test cases
int main() {
    Solution solution;

    vector<int> start;
    vector<int> target;
    vector<vector<int>> specialRoads;
    int result;

    auto startTime = chrono::high_resolution_clock::now();

    // // Test 1
    // start = {1, 1};
    // target = {4, 5};
    // specialRoads = {{1,2,3,3,2},{3,4,4,5,1}};

    // result = solution.minimumCost(start, target, specialRoads);
    // cout << "Result: " << result << " , Expected: " << 5 << endl;

    // Test 2
    specialRoads = {{1,1,6,6,9}, {0,0,12,12,22}, {0,0,7,7,13}};
    start = {0, 0};
    target = {13, 13};
    result = solution.minimumCost(start, target, specialRoads);
    cout << "Result: " << result << " , Expected: " << 24 << endl;

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}