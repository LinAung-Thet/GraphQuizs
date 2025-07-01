// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/?envType=problem-list-v2&envId=graph

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;

class UnionFind {
public:
    unordered_map<int, int> parent;

    int find(int x) {
        if (!parent.count(x))
            parent[x] = x;
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        UnionFind uf;
        for (auto& stone : stones) {
            int row = stone[0];
            int col = ~(stone[1]);  // flip column bits to distinguish from rows
            uf.unite(row, col);
        }

        unordered_map<int, int> uniqueRoots;
        for (auto& stone : stones) {
            int root = uf.find(stone[0]);
            uniqueRoots[root]++;
        }

        return stones.size() - uniqueRoots.size();
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