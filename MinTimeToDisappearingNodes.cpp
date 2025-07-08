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
        for(auto& edge: edges) {
            int u = edge[0], v = edge[1], length = edge[2];
            graph[u].emplace_back(length, v);
            graph[v].emplace_back(length, u);
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq; // Queue of pair{time, dest}
        pq.emplace(0,0);   // Start from node 0;
        vector<int> answers(n, INT_MAX);
        answers[0] = 0;

        // Calculate the shortest path to each node using BFS
        while(!pq.empty()) {
            auto [t,d] = pq.top(); 
            pq.pop();

            if(t >= disappear[d]) continue; // When the node d is reached, it already disappeared.
            if(t > answers[d]) continue;    // It's not the shortest path.
            

            // Loop all the neighbours of d
            for(auto& [neiT, neiD]: graph[d]) {
                int nextT = t + neiT;
                if (nextT < answers[neiD] && nextT < disappear[neiD]) {
                    answers[neiD] = nextT;
                    pq.emplace(nextT, neiD); // Proceed to the node
                }
            }
        }

        for(int i=0; i<n; i++) {
            if(answers[i] == INT_MAX)
                answers[i] = -1;
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