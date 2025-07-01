#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        // Build the graph and outdegree vector
        int n = isConnected.size();
        unordered_map<int, vector<int>> graph;
        unordered_map<int,int> inoutDegree;
        for(int i=0; i<n; i++) {
            int row = i + 1;
            for(int j=0; j<n; j++) {
                int col = j + 1;
                if(i == j) continue; // Skip self-loops
                if(!isConnected[i][j]) continue;
                
                inoutDegree[row]++;
                graph[row].push_back(col);
            }
        }

        // Traverse the outdegree vector and update the visited vector
        vector<bool> visited(n+1, false);
        int numProvince = 0;
        queue<int> connectedNodes;
        int numConnectedNode = inoutDegree.size();
        for (int i=1; i<=numConnectedNode; i++) {
            if (visited[i]) continue;
            if(inoutDegree[i] == 0) {
                // If the outdegree is 0, it is a separate province
                continue;
            }
            numProvince++;

            // If the outdegreee is > 0, find its connections
            connectedNodes.push(i);

            while (!connectedNodes.empty()) {
                int curNode = connectedNodes.front(); connectedNodes.pop();
                if(visited[curNode]) continue;
                visited[curNode] = true;

                for(auto next: graph[curNode]) {
                    if(visited[next]) continue; // Skip if already visited
                    // Add its connected nodes to the queue unless they are visited
                    connectedNodes.push(next);
                }
            }
        }

        return n - numConnectedNode + numProvince;
    }
};
int main() {
    Solution solution;
    vector<vector<int>> isConnected;
    int result;

    isConnected = {{1,1,0},{1,1,0},{0,0,1}};
    result = solution.findCircleNum(isConnected);
    cout << "Number of Provinces: " << result << " Expected output: 2" << endl;

    isConnected = {{1,0,0},{0,1,0},{0,0,1}};
    result = solution.findCircleNum(isConnected);
    cout << "Number of Provinces: " << result << " Expected output: 3" << endl;

    isConnected = {{1,0,0},{0,1,0},{0,0,1}};
    result = solution.findCircleNum(isConnected);
    cout << "Number of Provinces: " << result << " Expected output: 3" << endl;

    isConnected = {{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,1,0,1,0,0,0,0,0,0,0,0,0,1,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,1,0,0,0,1,0,0,0,1,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}};
    result = solution.findCircleNum(isConnected);
    cout << "Number of Provinces: " << result << " Expected output: 8" << endl;
    return 0;
}