// https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/?envType=problem-list-v2&envId=shortest-path

#include<vector>
#include<iostream>
#include<queue>
#include<chrono>
#include<cstring>
using namespace std;
using namespace chrono;

const int mod=1e9+7;
using int2=pair<unsigned long long, int>;
vector<int2> adj[200];
class Solution {
public:
    unsigned long long dijkstra(int start, int n, unsigned long long* dist){
        unsigned long long way[n];
        memset(way, 0, sizeof(way));
        priority_queue<int2, vector<int2>, greater<int2>> pq;
        pq.emplace(0, start);
        dist[start]=0;
        way[start]=1;
        while(!pq.empty()){
            auto [d0, i]=pq.top();
            pq.pop();
            for(auto [d2, j]:adj[i]){
                unsigned long long newD=d0+d2;
                if (newD<dist[j]){// path thru i, j
                    dist[j]=newD;
                    way[j]=way[i];
                    pq.emplace(newD, j);
                }
                else if( newD==dist[j]){
                    way[j]+=way[i]; // paths thru i & not thru i
                    way[j]%=mod;
                }
            }
        }
        return way[n-1];
    }
    int countPaths(int n, vector<vector<int>>& roads) {
        for(int i=0; i<n; i++)
            adj[i].clear();
            
        for (auto& e: roads){
            int u=e[0], v=e[1];
            unsigned long long time=e[2];
            adj[u].emplace_back(time, v);
            adj[v].emplace_back(time, u);
        }
        unsigned long long dist[200];
        fill(dist, dist+n, ULLONG_MAX);
        return dijkstra(0, n, dist);
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