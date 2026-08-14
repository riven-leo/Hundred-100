#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

using PII = pair<int, int>;
// {距离, 节点}

vector<int> dijkstra(
    const vector<vector<pair<int, int>>>& graph,
    int start
) {
    int n = graph.size();

    vector<int> dist(n, INT_MAX);

    priority_queue<
        PII,
        vector<PII>,
        greater<PII>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // 这是旧数据，跳过
        if (d != dist[u]) {
            continue;
        }

        // 遍历 u 的所有邻居
        for (auto [v, w] : graph[u]) {
            // 松弛
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;

                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n = 5;

    vector<vector<pair<int, int>>> graph(n);

    // 无向图
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

    vector<int> dist = dijkstra(graph, 0);

    for (int i = 0; i < n; i++) {
        cout << "0 -> " << i << " = "
             << dist[i] << '\n';
    }

    return 0;
}