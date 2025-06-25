// https://leetcode.com/problems/keys-and-rooms/description/?envType=problem-list-v2&envId=graph

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> visited(n, 0);
        queue<vector<int>> q;

        q.push(rooms[0]);   //It contains the room keys for next rooms.
        visited[0] = 1;
        while(!q.empty()) {
            auto roomKeys = q.front(); q.pop();
            if(roomKeys.size() == 0) continue;

            for(auto roomKey : roomKeys) {
                if(visited[roomKey]) continue;
                visited[roomKey] = 1;
                q.push(rooms[roomKey]);
            }
        }

        //Return true if all the rooms have been visited.
        return find(visited.begin(), visited.end(), 0) == visited.end();
    }
};

int main() {
    Solution solution;
    vector<vector<int>> rooms1 = {{1}, {2}, {3}, {}};
    cout << "Can visit all rooms (Example 1)? " << (solution.canVisitAllRooms(rooms1) ? "Yes" : "No") << endl;

    vector<vector<int>> rooms2 = {{1, 3}, {3, 0, 1}, {2}, {0}};
    cout << "Can visit all rooms (Example 2)? " << (solution.canVisitAllRooms(rooms2) ? "Yes" : "No") << endl;

    return 0;
} 