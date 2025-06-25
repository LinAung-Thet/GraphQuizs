// https://leetcode.com/problems/keys-and-rooms/description/?envType=problem-list-v2&envId=graph

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void dfs(int room, vector<vector<int>>& rooms, vector<bool>& visited) {
    visited[room] = true;
    for (int key : rooms[room]) {
        if (!visited[key]) {
            dfs(key, rooms, visited);
        }
    }
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    int n = rooms.size();
    vector<bool> visited(n, false);
    dfs(0, rooms, visited);

    for (bool wasVisited : visited) {
        if (!wasVisited) return false;
    }
    return true;
}

int main() {
    vector<vector<int>> rooms1 = {{1}, {2}, {3}, {}};
    cout << "Can visit all rooms (Example 1)? " << (canVisitAllRooms(rooms1) ? "Yes" : "No") << endl;

    vector<vector<int>> rooms2 = {{1, 3}, {3, 0, 1}, {2}, {0}};
    cout << "Can visit all rooms (Example 2)? " << (canVisitAllRooms(rooms2) ? "Yes" : "No") << endl;

    return 0;
} 