#include <vector>
#include <limits.h> // For INT_MAX
#include <iostream>
using namespace std;

class Edge {
    public:
    int source;
    int dest;
    int time;
    Edge(int s, int d, int t) : source(s), dest(d), time(t) {}
};
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        
        //Initialize a n x n grid which contain infinity values for the time among each other
        vector<vector<int>> grid(n, vector<int>(n, INT_MAX));

        int edgeCount = times.size();
        //Insert each time into the grid by calling a recursive function
        for(int i=0; i<edgeCount; i++) {
            auto time = times[i];
            insertEdge(Edge(time[0]-1, time[1]-1, time[2]), grid);  //0-based indexing is used
        }

        //Return -1 for those cells which contain INT_MAX, except the cells at [i][i]
        int minTotalTime = -1;
        k--; //We use 0-based
        for (int i=0; i<n; i++) {
            if (i==k) continue;
            if (grid[k][i] == INT_MAX) return -1;

            if (grid[k][i] > minTotalTime) minTotalTime = grid[k][i];
        }

        return minTotalTime;
    }

    //Recursive function
    void insertEdge (Edge e, vector<vector<int>>& grid) {
        //If the new time is not shorter than the current one, don't proceed
        if (e.time >= grid[e.source][e.dest]) return;

        //Replace the recorded time with e.time
        grid[e.source][e.dest] = e.time;

        //Traverse all the valid incoming edges inEdges to e.source and form a new edge prevEdge {inEdges[i].source, e.source, inEdges[i].time + e.time}
        for (int i=0; i<grid.size(); i++) {
            if (grid[i][e.source] == INT_MAX) continue;

            Edge prevEdge(i, e.dest, grid[i][e.source] + e.time);
            insertEdge(prevEdge, grid);
        }

        //Traverse all the valid outgoing edges outEdges from e.dest and form a new edge nextEdge {e.source, outEdges[i].dest, e.time + outEdges[i].time}
        for (int i=0; i<grid.size(); i++) {
            if (grid[e.dest][i] == INT_MAX) continue;

            Edge nextEdge(e.source, i, e.time + grid[e.dest][i]);
            insertEdge(nextEdge, grid);
        }
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