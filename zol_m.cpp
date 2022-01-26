#include <iostream>
#include <set>

// solv:
// dodajemy na poczatku wszystkich zolnierzy do seta
// wyciagamy z seta i sprawdzamy jego sasiadow (za pomoca lower_bound)

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    set<int> s;

    for (int i = 1; i <= n; ++i) {
        s.insert(i);
    }

    int z, l, r;
    for (int i = 0; i < n; ++i) {
        cin >> z;
        s.erase(z);

        auto it = s.lower_bound(z);
        r = it != s.end() ? *(it) : -1;
        l = it != s.begin() ? *(--it) : -1;

        cout << l << " " << r << '\n';
    }

    return 0;
}

