// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/?envType=problem-list-v2&envId=graph

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:
    void dfs(int city, const vector<vector<int>>& isConnected, vector<bool>& visited) {
        visited[city] = true;
        for (int neighbor = 0; neighbor < isConnected.size(); ++neighbor) {
            if (isConnected[city][neighbor] == 1 && !visited[neighbor]) {
                dfs(neighbor, isConnected, visited);
            }
        }
    }

    int removeStones(vector<vector<int>>& stones) {
        // Construct a connection graph
        int n = stones.size();
        vector<vector<int>> isConnected(n, vector<int>(n, 0));;
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                // If two stones are in the same row or column, they are connected
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
                    isConnected[i][j] = 1;
                    isConnected[j][i] = 1;
                }
            }   
        }

        vector<bool> visited(n, false);
        int groups = 0;

        // Count the number of connected stones
        for (int stone = 0; stone < n; ++stone) {
            if (!visited[stone]) {
                dfs(stone, isConnected, visited);
                groups++;
            }
        }

        // The maximum number of stones that can be removed is total stones minus the number of groups
        // Each group can keep one stone, so we can remove all others in that group
        return n - groups;
    }
};
int main() {
    Solution solution;
    vector<vector<int>> stones;
    int result;

    stones = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    result = solution.removeStones(stones);
    cout << "Number of removed stones: " << result << " Expected output: 5" << endl;

    stones = {{0,0},{0,2},{1,1},{2,0},{2,2}};
    result = solution.removeStones(stones);
    cout << "Number of removed stones: " << result << " Expected output: 3" << endl;

    stones = {{0,0}};
    result = solution.removeStones(stones);
    cout << "Number of removed stones: " << result << " Expected output: 0" << endl;

    return 0;
}