#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

// solv:
// jest malo rodzajow fabryk(10), wiec wystarczy ze dla kazdego rodzaju puscimy dfsa
// wynik dfsa(fab), gdzie fab to numer fabryki to para:\
// 1) dlugosc najdluzszej sciezki wglab drzewa do wierzcholka v takiego ze f(v) = fab
// 2) dlugosc najdluzszej sciezki w poddrzewie miedzy dwoma wierzcholkami v1, v2 takimi ze f(v1) = f(v2) = fab.
// Majac takie wyniki z dzieci, jestesmy w stanie wyliczyc u siebie, wynik calego dfsa to bedzie druga wartosc w parze wyliczonej w korzeniu
// No i ofc bierzemy maxa z tych dziesieciu dfsow.
// Mozna troche o tym problemie pomyslec jak o szukaniu srednicy drzewa (?).

using namespace std;

pair<int, int> dfs(int v, int p, vector<int> g[], vector<int> &f, int fab) {

    vector<int> dists;
    if (f[v] == fab)
        dists.push_back(0);
    int max_in_subtrees = -1;
    for (int a : g[v]) {
        if (a != p) {
            auto dist_and_max = dfs(a, v, g, f, fab);
            max_in_subtrees = max(max_in_subtrees, dist_and_max.second);
            if (dist_and_max.first != -1)
                dists.push_back(dist_and_max.first + 1);
        }
    }

    if (max_in_subtrees == -1) {
        if (dists.empty()) {
            return {-1, -1};
        }
        else if (dists.size() == 1) {
            return {0, 0};
        }
    }
    else {
        // tak naprawde zbedne to sortowanie, ale juz chuj
        sort(dists.begin(), dists.end());
        if (dists.size() == 1) {
            return {dists[0], max_in_subtrees};
        }
        else {
            int tmp = dists[dists.size() - 1] + dists[dists.size() - 2];
            max_in_subtrees = max(max_in_subtrees, tmp);
            return {dists[dists.size() - 1], max_in_subtrees};
        }
    }
    // useless return, ale zeby clion nie warnowal xd
    return {0, 0};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    stringstream s;

    int n;
    cin >> n;
    vector<int> f(n + 1, -1);
    vector<int> g[n + 1];

    for (int i = 1; i <= n; ++i) {
        cin >> f[i];
    }

    int v1, v2;
    for (int i = 1; i < n; ++i) {
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    int res = -1;
    pair<int, int> p;
    for (int fab = 1; fab <= 10; ++fab) {
        p = dfs(1, -1, g, f, fab);
        res = max(res, p.second);
    }

    cout << res << '\n';

    return 0;
}

