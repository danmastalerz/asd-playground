#include <iostream>
#include <vector>

// solv:
// Na poczatku lecimy dfsem (np. startujac z wierzcholka 1, to bedzie wtedy korzen)
// i wyliczamy dla kazdego wierzcholka 1) ilosc elementow w poddrzewie i 2) sume sciezek do wierzcholkow z poddrzewa(jakos tak?).

// Zauwazmy, ze przez to w korzeniu bedzie wyliczony wynik do zadania.
// Skoro mamy dobrze wyliczony jeden wierzcholek (korzeń), i kazdy wierzcholek zna wielkosc poddzrzewa to mozemy
// w kolejnym dfsie wyliczyc wartosci dla pozostalych wierzcholkow (korzystamy wtedy z tego ze ojciec jest dobrze wyliczony).
// Czemu? to juz ci wyjdzie pewnie jak bedziesz robil to zadanie a jak nie to na ds wole wytlumaczyc.

// Dodatkowo, wynik znowu uint64_t, bo jeden test sie wywala na intach.

using namespace std;

void dfs1(int v, int p, vector<int> g[], vector<uint64_t> &sums, vector<int> &in_subtree) {
    for (auto i : g[v]) {
        if (i != p) {
            dfs1(i, v, g, sums, in_subtree);
            sums[v] += (sums[i] + in_subtree[i]);
            in_subtree[v] += in_subtree[i];
        }
    }
}

void dfs2(int v, int p, int t_size, vector<int> g[], vector<uint64_t> &sums, vector<int> &in_subtree) {
    if (p != -1) {
        // zakladamy ze ojciec juz jest dobrze wyliczony
        // wzorek byl troszke bardziej skomplikowany ale sie uproscil do tego
        sums[v] = sums[p] + t_size - (2 * in_subtree[v]);
    }

    for (auto i : g[v]) {
        if (i != p) {
            dfs2(i, v, t_size, g, sums, in_subtree);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> g[n + 1];

    int v1, v2;
    for (int i = 1; i < n; ++i) {
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    vector<uint64_t> sums(n + 1, 0);
    vector<int> in_subtree(n + 1, 1);
    vector<bool> vis(n + 1, false);

    dfs1(1, -1, g, sums, in_subtree);

    dfs2(1, -1, n, g, sums, in_subtree);

    for (int i = 1; i <= n; ++i) {
        cout << sums[i] << '\n';
    }

    return 0;
}

