// https://leetcode.com/problems/number-of-provinces/description/

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

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int city = 0; city < n; ++city) {
            if (!visited[city]) {
                dfs(city, isConnected, visited);
                provinces++;
            }
        }

        return provinces;
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