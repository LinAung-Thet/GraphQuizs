#include<vector>
#include<iostream>
#include<queue>
using namespace std;
class Solution {
public:
    void dfs(int& numWays, int& minTime, queue<pair<int, int>>& q, int& n, vector<vector<pair<int, int>>>& graph, vector<bool>& visited) {
        while(!q.empty()){
            auto [curN,curT] = q.front(); 
            if(curN == n-1) {
                if(curT <= minTime) {
                    if(curT < minTime) {
                        minTime = curT;
                        numWays = 0;
                    }
                    numWays++;
                }
                q.pop();
                continue;
            }
            for(auto [d,t]: graph[curN]) {
                q.emplace(pair(d,t+curT));
                dfs(numWays, minTime, q, n, graph);
            }
        }
    }
    int countPaths(int n, vector<vector<int>>& roads) {
        int numWays = 0;
        int minTime = INT_MAX;
        vector<bool> visited(n,false);

        //Build the connected graph: vector of pair(dest, time) at each index for the source 
        vector<vector<pair<int, int>>> graph(n);
        for(auto& road: roads) {
            graph[road[0]].push_back(pair(road[1],road[2]));
        }

        queue<pair<int, int>> q;
        q.emplace(pair(0, 0));
        visited[0] = true;

        dfs(numWays, minTime, q, n, graph, visited);

        return numWays;
    }
};