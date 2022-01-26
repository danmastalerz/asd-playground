#include <iostream>
#include <vector>
#include <algorithm>

// solv:
// To w sumie nie jest ani troche zadanie na grafy xdd
// Trzeba zauwazyc ze kazda taka dwukrawedziowa droga jest wyznaczona przez pewien wierzcholek V: x -> V -> y
// Wiec sobie wczytujemy graf, ale tak naprawde nie interesuje nas do jakiego wierzcholka prowadzi ta krawedz
// tylko sama waga krawedzi.
// Teraz iterujemy sie po wierzcholkach, i sortujemy sobie vector ktorzy trzyma wagi tych krawedzi naszych.
// I teraz musimy dla kazdej krawedzi odpowiedziec na pytanie ile jest krawedzi o mniejszej wadze.
// Na posortowanej tablicy mozemy to zrobic liniowo, i po prostu zwiekszamy koncowy wynik.

// Zlozonosc tego to na oko O(n + m * log(m)).

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> vert[n + 1];

    int v1, v2, w;
    for (int i = 0; i < m; ++i) {
        cin >> v1 >> v2 >> w;
        vert[v1].push_back(w);
        vert[v2].push_back(w);
    }

    uint64_t res = 0;
    for (int i = 1; i <= n; ++i) {
        sort(vert[i].begin(), vert[i].end());
        int number_of_smaller = 0;
        for (int j = 1; j < vert[i].size(); ++j) {
            if (vert[i][j] > vert[i][j - 1]) {
                res += j;
                number_of_smaller = j;
            }
            else {
                res += number_of_smaller;
            }
        }
    }

    cout << res << '\n';

    return 0;
}

