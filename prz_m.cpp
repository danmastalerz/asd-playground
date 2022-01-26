#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// solv:
// no po prostu sortujemy po pierwszej pozycji, i porownujemy konce (poczatek aktualnego z koncem poprzedniego)

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, int>> v;

    int a, b;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        v.emplace_back(a, b);
    }

    sort(v.begin(), v.end());

    int m = 1000000001;
    for (int i = 1; i < n; ++i) {
        if (v[i].first <= v[i - 1].second) {
            cout << 0 << '\n';
            return 0;
        }

        m = min(m, v[i].first - v[i - 1].second);
    }

    cout << m << '\n';

    return 0;
}