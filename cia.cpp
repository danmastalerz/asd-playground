#include <iostream>
#include <set>
#include <map>
#include <queue>

// solv:
// znowu abusowanie seta, kolejki priorytetowej i mapy/multiseta w skrocie

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    map<int, int> dists;
    priority_queue<int> d;
    set<int> s;
    s.insert(0);
    s.insert(n);
    dists[n] = 1;

    int v;
    int prev, next;
    for (int i = 0; i < m; ++i) {
        cin >> v;
        auto it = s.lower_bound(v);
        next = *it;
        --it;
        prev = *it;

        --dists[next - prev];
        ++dists[v - prev];
        ++dists[next - v];
        s.insert(v);
        d.push(v - prev);
        d.push(next - v);

        while(dists[d.top()] == 0)
            d.pop();

        cout << d.top() << '\n';
    }

    return 0;
}

