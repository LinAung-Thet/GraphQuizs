// https://leetcode.com/problems/path-with-maximum-probability/description/

#include<vector>
#include<queue>
#include<iostream>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<vector<pair<int, double>>> graph(n);
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            double prob = succProb[i];
            graph[u].emplace_back(v, prob);
            graph[v].emplace_back(u, prob);
        }

        vector<double> probTo(n, 0.0);
        probTo[start_node] = 1.0;

        // Max heap: (probability, node)
        priority_queue<pair<double, int>> pq;
        pq.emplace(1.0, start_node);

        while (!pq.empty()) {
            auto [currProb, node] = pq.top();
            pq.pop();

            if (node == end_node) return currProb;

            for (auto& [neighbor, edgeProb] : graph[node]) {
                double newProb = currProb * edgeProb;
                if (newProb > probTo[neighbor]) {
                    probTo[neighbor] = newProb;
                    pq.emplace(newProb, neighbor);
                }
            }
        }

        return 0.0;
    }
};
//Test cases
int main() {
    int n, start, end;
    double result;
    vector<vector<int>> edges;
    vector<double> succProb;
    Solution solution;

    n = 3; start = 0; end = 2;
    edges = {{0,1}, {1,2}, {0,2}};
    succProb = {0.5, 0.5, 0.2};
    result = solution.maxProbability(n, edges, succProb, start, end);
    cout<< "Result: " << result << " , Expected: " << 0.25 << endl;

    n = 3; start = 0; end = 2;
    edges = {{0,1}, {1,2}, {0,2}};
    succProb = {0.5, 0.5, 0.3};
    result = solution.maxProbability(n, edges, succProb, start, end);
    cout<< "Result: " << result << " , Expected: " << 0.3 << endl;

    n = 3; start = 0; end = 2;
    edges = {{0,1}};
    succProb = {0.5};
    result = solution.maxProbability(n, edges, succProb, start, end);
    cout<< "Result: " << result << " , Expected: " << 0 << endl;
}