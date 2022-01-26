#include <iostream>
#include <set>
#include <sstream>

// solv:
// No tutaj to widac od razu drzewa wyszukiwan binarnych, ale nie chcialo mi sie klepac to z seta skorzystalem i tyle xd.
// Znowu trzeba pamietac o uint64_t bo na intach sie dziwne rzeczy dzieja (sprawdzone).

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    uint64_t res = 0;
    set<uint64_t> s;
    uint64_t val, prev, next;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (i == 0) {
            s.insert(val);
        }
        else {
            prev = -1;
            next = -1;
            auto it = s.lower_bound(val);
            next = it != s.end() ? *it : -1;
            prev = it != s.begin() ? *(--it) : -1;
            if (prev != -1 && next != -1) {
                res -= ((next - prev) * (next - prev));
            }
            if (prev != -1) {
                res += ((val - prev) * (val - prev));
            }
            if (next != -1) {
                res += ((val - next) * (val - next));
            }
            s.insert(val);
            cout << res << '\n';
        }
    }

    return 0;
}

