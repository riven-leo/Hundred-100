#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

struct Node {
    int f;
    int g;
    int u;

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

double heuristic(
    int u,
    int target,
    const vector<pair<int, int>>& pos
) {
    int dx = pos[u].first - pos[target].first;
    int dy = pos[u].second - pos[target].second;

    return sqrt(dx * dx + dy * dy);
}

int astar(
    const vector<vector<pair<int, int>>>& graph,
    const vector<pair<int, int>>& pos,
    int start,
    int target
) {
    int n = graph.size();

    vector<int> g(n, INT_MAX);

    priority_queue<
        Node,
        vector<Node>,
        greater<Node>
    > pq;

    g[start] = 0;

    int startF = g[start] + heuristic(start, target, pos);

    pq.push({
        startF,
        g[start],
        start
    });

    while (!pq.empty()) {
        auto [f, currentG, u] = pq.top();
        pq.pop();

        // 旧数据
        if (currentG != g[u]) {
            continue;
        }

        // A* 只求 start -> target
        if (u == target) {
            return g[u];
        }

        for (auto [v, w] : graph[u]) {
            int newG = g[u] + w;

            // 真正路径是否更优，看的是 g
            if (newG < g[v]) {
                g[v] = newG;

                int newF =
                    g[v] + heuristic(v, target, pos);

                pq.push({
                    newF,
                    g[v],
                    v
                });
            }
        }
    }

    return -1;
}

int main() {
    int n = 5;

    vector<vector<pair<int, int>>> graph(n);

    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    };

    addEdge(0, 1, 2);
    addEdge(0, 2, 5);
    addEdge(1, 2, 1);
    addEdge(1, 3, 3);
    addEdge(2, 3, 1);
    addEdge(3, 4, 2);

    // 每个节点的位置
    vector<pair<int, int>> pos = {
        {0, 0}, // 0
        {1, 0}, // 1
        {2, 1}, // 2
        {3, 1}, // 3
        {4, 1}  // 4
    };

    int start = 0;
    int target = 4;

    int ans = astar(
        graph,
        pos,
        start,
        target
    );

    cout << "shortest distance = "
         << ans << '\n';

    return 0;
}