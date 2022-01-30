#include <iostream>
#include <vector>
#include <utility>

// solv:
// Dynamik, dla każdego poddrzewa liczymy:
// 1) Skojarzenie z poddrzewa o najwiekszej sumie wag
// 2) Skojarzenie z poddrzewa o najwiekszej sumie wag, ALE takiego ze nasz korzeń do niego nie należy

using namespace std;

void dfs(int v, int p, vector<pair<int, int>> g[], vector<int> &max_matching, vector<int> &max_matching_wout_root) {

    for (auto &pr : g[v]) {
        if (pr.first != p) {
            dfs(pr.first, v, g, max_matching, max_matching_wout_root);
            max_matching_wout_root[v] += max_matching[pr.first];
        }
    }

    max_matching[v] = max_matching_wout_root[v];

    for (auto &pr : g[v]) {
        if (pr.first != p) {
            int tmp = pr.second + max_matching_wout_root[pr.first] - max_matching[pr.first];
            if (tmp > 0)
                max_matching[v] = max(max_matching[v], max_matching_wout_root[v] + tmp);
        }
    }

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, int>> g[n + 1];
    vector<int> max_matching(n + 1, 0);
    vector<int> max_matching_wout_root(n + 1, 0);

    int v1, v2, w;
    for (int i = 1; i < n; ++i) {
        cin >> v1 >> v2 >> w;
        g[v1].emplace_back(v2, w);
        g[v2].emplace_back(v1, w);
    }

    dfs(1, -1, g, max_matching, max_matching_wout_root);

    cout << max_matching[1] << '\n';
    return 0;
}

