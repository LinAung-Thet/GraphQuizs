#include<vector>
#include<queue>
#include<iostream>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        //Build the graph which contains pairs of (dest, probability)
        vector<vector<pair<int,double>>> graph(n);
        for(int i=0; i<edges.size(); i++) {
            auto& e = edges[i];
            graph[e[0]].push_back(pair(e[1], succProb[i]));
            graph[e[1]].push_back(pair(e[0], succProb[i]));
        }

        //Vector which stores the max probability to each node from the source
        vector<double> results(n, 0);

        //Queue which stores the potential nodes to the destination
        queue<pair<int, double>> q;
        
        //Start from start_node
        q.emplace(pair(start_node, 1));

        //Repeat until there is no more potential node found
        while(!q.empty()) {
            auto [cN, cP] = q.front(); q.pop();

            //Traverse every node the current node is directly connected
            for(auto [d,p]: graph[cN]) {
                //If it has the bigger probability, proceed it
                double nP = cP * p;
                if(nP > results[d]) {
                    q.emplace(pair(d, nP));
                    //Update the results
                    results[d] = nP;
                }
            }
        }

        return results[end_node];
    }
};
//Test cases
int main() {
    int n, start, end;
    double result;
    vector<vector<int>> edges;
    vector<double> succProb;
    Solution solution;

    n = 3; start = 0; end = 2;
    edges = {{0,1}, {1,2}, {0,2}};
    succProb = {0.5, 0.5, 0.2};
    result = solution.maxProbability(n, edges, succProb, start, end);
    cout<< "Result: " << result << " , Expected: " << 0.25 << endl;

    n = 3; start = 0; end = 2;
    edges = {{0,1}, {1,2}, {0,2}};
    succProb = {0.5, 0.5, 0.3};
    result = solution.maxProbability(n, edges, succProb, start, end);
    cout<< "Result: " << result << " , Expected: " << 0.3 << endl;

    n = 3; start = 0; end = 2;
    edges = {{0,1}};
    succProb = {0.5};
    result = solution.maxProbability(n, edges, succProb, start, end);
    cout<< "Result: " << result << " , Expected: " << 0 << endl;
}