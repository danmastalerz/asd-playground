#include <iostream>
#include <set>

// solv:
// mamy set i po prostu trzymamy licznik takich par spelniajacych to
// (licznik zmieniamy odpowiednio sprawdzajac czy w secie mamy 'v + d' albo 'v - d', gdzie v to wstawiana wartosc)

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, d;
    cin >> n >> d;

    set<int> s;

    int op, v;
    int valid_pairs = 0;
    for (int i = 0; i < n; ++i) {
        cin >> op >> v;
        if (op == 1) {
            if (s.count(v + d) > 0)
                ++valid_pairs;
            if (s.count(v - d) > 0)
                ++valid_pairs;
            s.insert(v);
        }
        else {
            s.erase(v);
            if (s.count(v + d) > 0)
                --valid_pairs;
            if (s.count(v - d) > 0)
                --valid_pairs;
        }

        if (valid_pairs > 0)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }

    return 0;
}

