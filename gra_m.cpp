#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <tuple>

// solv: puszczamy BFS'a z 1, z tym ze kazdy wierzcholek mozemy odwiedzic na co najwyzej dwa sposoby:
// raz dochodzac krawedzia czerwona, a raz zielona.
// w kolejce trzymamy trojke (wierzcholek, dist od 1, kolor krawedzi ktora przyszlismy)

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> g[n + 1];
    bool vis[n + 1][2];

    for (int i = 1; i <= n; ++i) {
        vis[i][0] = false;
        vis[i][1] = false;
    }

    int v1, v2, c;
    for (int i = 0; i < m; ++i) {
        cin >> v1 >> v2 >> c;
        g[v1].emplace_back(v2, c);
        g[v2].emplace_back(v1, c);
    }

    queue<tuple<int, int, int>> q;
    vis[1][0] = true;
    vis[1][1] = true;
    q.emplace(1, 0, 2);

    vector<int> dist(n + 1, -1);

    int v, d;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        v = get<0>(p);
        d = get<1>(p);
        c = get<2>(p);

        if (dist[v] == -1) {
            dist[v] = d;
        }

        for (auto vertices : g[v]) {
            int next = vertices.first;
            int color = vertices.second;

            if (c != color && !vis[next][color]) {
                vis[next][color] = true;
                q.emplace(next, d + 1, color);
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        cout << dist[i] << '\n';
    }

    return 0;
}
