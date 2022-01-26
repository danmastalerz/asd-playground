#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>

// solv:
// sortujemy sobie te odcinki (na poczatku po x-owej a potem po y1)
// wrzucamy koncowki odcinkow do kolejki priorytetowej MIN.
// jak odwiedzamy nowy odcinek to wywalamy z kolejki te konce ktore sa mniejsze od naszego poczatku.
// zwiekszamy wynik o size kolejki.

// znowu uint64_t xd

using namespace std;

bool cmp (tuple<int, int, int> t1, tuple<int, int, int> t2) {
    if (get<0>(t1) < get<0>(t2))
        return true;
    else if (get<0>(t1) > get<0>(t2))
        return false;
    else
        return get<1>(t1) < get<1>(t2);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    vector<tuple<int, int, int>> v;

    int x, y1, y2;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y1 >> y2;
        v.emplace_back(x, y1, y2);
    }

    sort(v.begin(), v.end(), cmp);

    priority_queue<int, vector<int>, greater<>> q;
    uint64_t res = 0;
    q.push(get<2>(v[0]));

    for (int i = 1; i < n; ++i) {
        auto tpl = v[i];
        x = get<0>(tpl);
        y1 = get<1>(tpl);
        y2 = get<2>(tpl);

        if (get<0>(v[i]) != get<0>(v[i - 1])) {
            while (!q.empty())
                q.pop();
        }
        else {
            while (!q.empty() && q.top() < y1) {
                q.pop();
            }
            res += q.size();
        }
        q.push(y2);
    }

    cout << res << '\n';

    return 0;
}

