// https://leetcode.com/problems/course-schedule-ii/description/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> order;
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    // Build the graph and compute indegrees
    for (auto& pre : prerequisites) {
        graph[pre[1]].push_back(pre[0]); // graph[i] contains all courses that depend on course i
        indegree[pre[0]]++; // indegree[i] counts how many prerequisites course i has
    }

    queue<int> q;

    // Start with all courses that have no prerequisites
    for (int i = 0; i < numCourses; ++i) {
        if (indegree[i] == 0)
            q.push(i);
    }

    int completed = 0;

    while (!q.empty()) {
        int course = q.front();
        q.pop();
        completed++;
        order.push_back(course); // Add the course to the order

        // For each course that depends on the current course
        // reduce the indegree and check if it can be added to the queue
        for (int next : graph[course]) {
            indegree[next]--;
            if (indegree[next] == 0)
                q.push(next);
        }
    }

    if ( completed == numCourses ) return order;
    else return {}; // Return an empty vector if not all courses can be completed
}

void DisplayOrder(const vector<int>& order) {
    if (order.empty()) {
        cout << "No valid order exists." << endl;
        return;
    }
    cout << "[";
    for (int course : order) {
        cout << course << " ";
    }
    cout << "]";
    cout << endl;
}

int main() {
    // Example 1
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    cout << "Order of courses (Example 1): ";
    DisplayOrder(findOrder(numCourses1, prerequisites1));
    cout << endl;

    // Example 2
    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    cout << "Order of courses (Example 2): ";
    DisplayOrder(findOrder(numCourses2, prerequisites2));
    cout << endl;

    return 0;
}