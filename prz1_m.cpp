#include <iostream>
#include <set>

// solv:
// jako ze mamy zalozenie l = 1 v r = n to trzymamy 2 sety
// jeden dla koncowek przedzialow postaci [1, x] a drugi dla poczatkow przedzialow [x, n].
// w czasie stalym mozemy z tego od koncowek wziac maxa (set::rbegin()), a z drugiegon mina (set::begin())

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    char op;
    int l, r, res;
    set<int> ends;
    ends.insert(0);
    set<int> begins;
    begins.insert(n + 1);
    for (int i = 0; i < m; ++i) {
        cin >> op >> l >> r;
        if (op == '+') {
            if (l == 1) {
                ends.insert(r);
            }
            else {
                begins.insert(l);
            }
        }
        else {
            if (l == 1) {
                ends.erase(r);
            }
            else {
                begins.erase(l);
            }
        }

        auto e_it = ends.rbegin();
        auto b_it = begins.begin();

        res = *b_it > *e_it ? *b_it - *e_it - 1 : 0;
        cout << res << '\n';
    }

    return 0;
}

