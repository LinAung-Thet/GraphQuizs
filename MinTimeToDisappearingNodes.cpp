// https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/?envType=problem-list-v2&envId=shortest-path

#include <vector>
#include <iostream>
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        // Build the adjacency matrix which contains pairs of dest and time
        vector<vector<pair<int,int>>> graph(n);
        for(vector edge: edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }

        queue<pair<int,int>> q; // Queue of pair{dest,time}
        q.emplace(0,0);   // Start from node 0;
        vector<int> answers(n, -1);

        // Calculate the shortest path to each node using BFS
        while(!q.empty()) {
            auto [d,t] = q.front(); q.pop();

            if(t >= disappear[d]) continue; // When the node d is reached, it already disappeared.
            if(t > answers[d] && answers[d] >= 0) continue; // It's not the shortest path.
            answers[d] = t;

            // Loop all the neighbours of d
            for(auto [neiD, neiT]: graph[d]) {
                int nextT = t + neiT;
                if (nextT < answers[neiD] || answers[neiD] < 0) {
                    q.emplace(neiD, nextT); // Proceed to the node
                }
            }
        }

        // Return the answer vector
        return answers;
    }
};

// Test cases
int main() {
    Solution solution;
    int n;
    vector<vector<int>> edges;
    vector<int> disappear;
    vector<int> answers;

    auto startTime = high_resolution_clock::now();

    // Test 1
    n = 3;
    edges = {{0,1,2}, {1,2,1}, {0,2,4}};
    disappear = {1,1,5};

    answers = solution.minimumTime(n, edges, disappear);
    cout << "Output vs Expected:" << endl;
    for(int ans: answers) { 
        cout << ans << " ";
    }
    cout << endl << "0 -1 4" << endl;

    // Test 2
    n = 3;
    edges = {{0,1,2}, {1,2,1}, {0,2,4}};
    disappear = {1,3,5};

    answers = solution.minimumTime(n, edges, disappear);
    cout << "Output vs Expected:" << endl;
    for(int ans: answers) { 
        cout << ans << " ";
    }
    cout << endl << "0 2 3" << endl;

    // Test 3
    n = 2;
    edges = {{0,1,1}};
    disappear = {1,1};

    answers = solution.minimumTime(n, edges, disappear);
    cout << "Output vs Expected:" << endl;
    for(int ans: answers) { 
        cout << ans << " ";
    }
    cout << endl << "0 -1" << endl;

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);

    // Test 4

    n = 8;
    edges = {{4,0,5},{3,7,3},{0,2,3},{3,5,3},{7,0,1},{2,0,3},{7,7,10}};
    disappear = {15,8,4,3,9,18,9,13};

    answers = solution.minimumTime(n, edges, disappear);
    cout << "Output vs Expected:" << endl;
    for(int ans: answers) { 
        cout << ans << " ";
    }
    cout << endl << "0 -1 3 -1 5 -1 -1 1" << endl;

    cout << "Execution time: " << duration.count() << " microseconds" << endl;
}