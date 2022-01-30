#include <iostream>
#include <vector>

// solv:
// Mamy tylko 10 roznych mozliwych wartosci, wiec wyliczamy dla kazdej wartosci dwie tablice:
// count[i][x][0] - ile jest wartosci x na prefiksie tablicy [1, i - 1]
// count[i][x][1] - ile jest wartosci x na sufiksie tablicy [i + 1, n]
// No i potem liniowo mozemy wynik znalezc (przemnazajac tam odpowiednio wyniki z count[i][x][0] i count[i][x + t[i]][1])

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> t(n);
    uint64_t count[n + 1][11][2];

    for (int i = 0; i <= 10; ++i) {
        count[0][i][0] = 0;
        count[0][i][1] = 0;
        count[n][i][0] = 0;
        count[n][i][1] = 0;
    }

    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 10; ++j) {
            count[i][j][0] = count[i - 1][j][0];
            count[i][j][1] = count[i - 1][j][1];
        }

        ++count[i][t[i - 1]][0];
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= 10; ++j) {
            count[i][j][1] = count[i + 1][j][1];
        }

        ++count[i][t[i + 1]][1];
    }

    uint64_t res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= 10 - t[i]; ++j) {
            res += count[i][j][0] * count[i][j + t[i]][1];
        }
    }

    cout << res << '\n';

    return 0;
}

