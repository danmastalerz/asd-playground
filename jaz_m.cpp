#include <iostream>
#include <vector>

// solv: sprawdzic czy jest cykl w grafie xd
using namespace std;

bool dfs(int cur, int prev, vector<int> g[], vector<bool> &vis) {
    vis[cur] = true;

    for (auto v : g[cur]) {
        if (vis[v] && v != prev) {
            return true;
        }
        else if (!vis[v]) {
            if (dfs(v, cur, g, vis)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1];
    vector<bool> vis(n + 1, false);

    int v1, v2;
    for (int i = 0; i < m; ++i) {
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            if (dfs(i, 0, g, vis)) {
                cout << "TAK\n";
                return 0;
            }
        }
    }

    cout << "NIE\n";

    return 0;
}
