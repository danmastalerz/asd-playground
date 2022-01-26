#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// kolorujemy graf na 2 kolory - niebieski i czerwony
// bialy oznacza ze nieodwiedzony
enum class color {
    WHITE = 0, RED = 1, BLUE = 2
};

// dfs, bo graf jest niespojny i trzeba wyznaczyc reprezentantow spojnych skladowych do BFS'a
void dfs(int v, vector<int> g[], vector<bool> &vis) {
    vis[v] = true;
    for (auto i : g[v]) {
        if (!vis[i])
            dfs(i, g, vis);
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1];
    vector<color> c(n + 1, color::WHITE);

    int v1, v2;
    for (size_t i = 0; i < m; ++i) {
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    vector<bool> vis(n + 1, false);
    // vector reprezentantow skladowych
    vector<int> comp_reps;

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            comp_reps.push_back(i);
            dfs(i, g, vis);
        }
    }

    queue<int> q;

    // dla kazdego reprezentanta odpalamy BFS'a
    for (int i = 0; i < comp_reps.size(); ++i) {
        int rep = comp_reps[i];
        q.push(rep);
        vis[rep] = true;
        c[rep] = color::BLUE;

        int cur;
        while (!q.empty()) {
            cur = q.front();
            q.pop();

            for (auto v : g[cur]) {
                // jak nieodwiedzony to odpowiednio kolorujemy
                if (c[v] == color::WHITE) {
                    c[v] = c[cur] == color::BLUE ? color::RED : color::BLUE;
                    q.push(v);
                }
                else {
                    // jak pokolorowany na ten sam co my, to "NIE"
                    if (c[v] == c[cur]) {
                        cout << "NIE\n";
                        return 0;
                    }
                }
            }
        }
    }

    cout << "TAK\n";

    return 0;
}

