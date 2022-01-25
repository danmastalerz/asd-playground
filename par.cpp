/*
rozwiązanie: dfs zaczynając od wierzchołka 1, jeśli wierzchołek jest w tej samej spójnej składowej co 1
i jest to miejsce zajete to dodajemy to do odpowiedzi, którą potem sortujemy.
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int i, vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& blocked, vector<int>& answer) {
    visited[i] = true;

    if (blocked[i]) {
        answer.push_back(i);
        return;
    }
    for (auto v : graph[i]) {
        if (!visited[v]) {
            dfs(v, graph, visited, blocked, answer);
        }
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<bool> blocked(n + 1, false);
    vector<vector<int>>graph(n + 1, vector<int>());
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        blocked[i] = temp;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> ans;
    vector<bool> visited(n + 1, false);

    dfs(1, graph, visited, blocked, ans);
    sort(ans.begin(), ans.end());

    for (auto x : ans) cout << x << endl;


}
