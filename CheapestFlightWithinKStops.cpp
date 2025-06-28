#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Dest {
    public: 
    int price;
    int numStops;
    Dest(int p, int n) : price(p), numStops(n) {}
};
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto& flight : flights) {
            int fm = flight[0], to = flight[1], w = flight[2];
            graph[fm].emplace_back(to, w);
        }

        // Min-heap: (Dest, node)
        auto cmp = [](pair<Dest, int> a, pair<Dest, int> b) {return (a.first.price > b.first.price);};
        priority_queue<pair<Dest, int>, vector<pair<Dest, int>>, decltype(cmp)> pq(cmp);
        vector<Dest> dest(n + 1, Dest(INT_MAX, -1));
        dest[src] = Dest(0, -1);
        pq.emplace(Dest(0, -1), src);

        while (!pq.empty()) {
            auto [currDest, fm] = pq.top();
            pq.pop();

            if (currDest.price > dest[fm].price || dest[fm].numStops >= k) {
                n = n;
                continue;  // Skip outdated entry
            }

            for (auto& [to, price] : graph[fm]) {
                if (dest[fm].price + price < dest[to].price) {
                    dest[to].price = dest[fm].price + price;
                    dest[to].numStops = dest[fm].numStops + 1;
                    pq.emplace(dest[to], to);
                }
            }
        }

        if (dest[dst].price == INT_MAX || dest[dst].numStops > k) return -1;  // Unreachable node
        return dest[dst].price;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{0,2,500}};
    int n = 3;
    int src = 0;
    int dst = 2;
    int k = 1;
    int result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 200" << endl;

    flights = {{0,1,100},{1,2,100},{0,2,500}};
    n = 3;
    src = 0;
    dst = 2;
    k = 0;
    result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 500" << endl;

    flights = {{0,1,1},{0,2,5},{1,2,1},{2,3,1}};
    n = 4;
    src = 0;
    dst = 3;
    k = 1;
    result = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest Price: " << result << " Expected output: 6" << endl;

    return 0;
}